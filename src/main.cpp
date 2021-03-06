#include <ACROBOTIC_SSD1306.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP_Google_Sheet_Client.h>
#include <EasyButton.h>
#include <arduino-timer.h>
#include <string.h>

#include "configs.h"
#include "firmware.h"
#include "googleSheets.h"
#include "oledDisplay.h"
#include "utility.h"
#include "wifiMan.h"

EasyButton btnReset(0);
EasyButton btnDoor_01(DOOR_BTN_PIN_01);
hw_timer_t* watchdogTimer = NULL;
auto timer = timer_create_default();  // create a timer with default settings
int openTimeCounter = 0;
bool taskComplete = false;

void tokenStatusCallback(TokenInfo info) {
    oled.putString(".");
    if (info.status == esp_signer_token_status_error) {
        Serial.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
        Serial.printf("Token error: %s\n", GSheet.getTokenError(info).c_str());
    } else {
        Serial.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
    }
}

void onPressed() {
    Serial.println("Reset Wifi Manager");
    wifiReset();
}

void door_01_onPressed() {
    openTimeCounter++;
    Serial.println("--------------------------------------");
    Serial.println("Door Opener - 01 Switch Activating => " + String(openTimeCounter));
    if (WiFi.status() == WL_CONNECTED) {
        bool ready = GSheet.ready();
        if (ready && !taskComplete) {
            oled.setTextXY(5, 1);
            oled.putString("Counter : " + String(openTimeCounter) + " times  ");

            UpdateSheets();
            oled.setTextXY(7, 1);
            oled.putString(NowString());
        }
    }
}

void buttonISR() {
    btnDoor_01.read();
}

void setup() {
    Serial.begin(DEFAULT_BAUD_RATE);

    // OLED Display
    InitialOLED();

    delay(100);

    pinMode(LED_BUILTIN, OUTPUT);

    btnReset.begin();
    btnReset.onPressed(onPressed);

    btnDoor_01.begin();
    btnDoor_01.onPressed(door_01_onPressed);

    setup_Wifi();
    setupTimeZone();

    // resetDisplay();

    delay(100);
    if (WiFi.status() == WL_CONNECTED) {
        // Set the callback for Google API access token generation status (for debug only)
        GSheet.setTokenCallback(tokenStatusCallback);

        // Begin the access token generation for Google API authentication
        GSheet.begin(GOOGLE_CLIENT_EMAIL, GOOGLE_PROJECT_ID, PRIVATE_KEY);

        timer.every(2000, ledActiveStatus);
        if (ENABLE_FIRMWARE_AUTOUPDATE)
            timer.every(CHECK_FIRMWARE_INTERVAL, updateFirmware);
    }
    delay(2000);

    oled.setTextXY(0, 1);
    oled.putString(" -- HOME DATA LOGGER --   ");
    oled.setTextXY(1, 1);
    oled.putString("Version : " + String(FIRMWARE_VERSION));
    oled.setTextXY(2, 1);
    oled.putString("IP : " + WiFi.localIP().toString());
    oled.setTextXY(3, 1);
    oled.putString("Device : " + String(DEVICE_NAME));

    oled.setTextXY(4, 1);
    oled.putString("     ");

    oled.setTextXY(5, 1);
    oled.putString("Counter : " + String(openTimeCounter) + " times ");

    oled.setTextXY(6, 1);
    oled.putString("     ");

    oled.setTextXY(7, 1);
    oled.putString(NowString());

    digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
    btnReset.read();
    btnDoor_01.read();
    timer.tick();
}
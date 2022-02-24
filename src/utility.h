#ifndef UTILITY_H
#define UTILITY_H

#include <ACROBOTIC_SSD1306.h>
#include <Arduino.h>

char ntp_server1[20] = "pool.ntp.org";
char ntp_server2[20] = "time.nist.gov";
char ntp_server3[20] = "time.uni.net.th";

int timezone = 7 * 3600;  // timezone for Thailand is +7
int dst = 0;

void printMessage(int X, int Y, String message, bool isPrintLn) {
    oled.setTextXY(X, Y);
    oled.putString(message);
    if (isPrintLn)
        Serial.println(message);
    else
        Serial.print(message);
}

String NowString() {
    time_t now = time(nullptr);
    struct tm* newtime = localtime(&now);
    // Serial.println(ctime(&now));
    String tmpNow = "";
    tmpNow += String(newtime->tm_mday);
    tmpNow += "/";
    tmpNow += String(newtime->tm_mon + 1);
    tmpNow += "/";
    tmpNow += String(newtime->tm_year + 1900);
    tmpNow += " ";
    tmpNow += String(newtime->tm_hour);
    tmpNow += ":";
    tmpNow += String(newtime->tm_min);
    tmpNow += ":";
    tmpNow += String(newtime->tm_sec);
    return tmpNow;
}

void setupTimeZone() {
    Serial.println();
    printMessage(0, 1, "Synchronization timezone", true);
    oled.setTextXY(1, 1);
    for (int i = 0; i <= 10; i++) {
        configTime(timezone, dst, ntp_server1, ntp_server2, ntp_server3);
        Serial.println("Waiting for synchronization timezone => " + String(i));
        oled.putString(".");

        while (!time(nullptr)) {
            Serial.print(".");
            oled.putString(".");
            delay(1000);
        }
        time_t now = time(nullptr);
        if (i == 10) {
            Serial.println();
            Serial.println(ctime(&now));
        }
        delay(1000);
    }
}

bool ledActiveStatus(void*) {
    if (WiFi.status() == WL_CONNECTED) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
    return true;
}

String getSplitValue(String data, char separator, int index) {
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }

    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

String getChipId() {
    String ChipIdHex = String((uint32_t)(ESP.getEfuseMac() >> 32), HEX);
    ChipIdHex += String((uint32_t)ESP.getEfuseMac(), HEX);
    return ChipIdHex;
}

#endif
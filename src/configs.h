#ifndef CONFIGS_H
#define CONFIGS_H

// Configuration
#define DEVICE_NAME "GUARDHOUSE-01"
#define WIFI_SSID "MY_SSID"
#define WIFI_PASSWORD "MyPassword"

#define GOOGLE_PROJECT_ID "your-project_id"      // Taken from "project_id" key in JSON file.
#define GOOGLE_CLIENT_EMAIL "your_client_email"  // Taken from "client_email" key in JSON file.
#define GOOGLE_SPREADSHEET_ID "sheets_id"
// Line config
#define LINE_TOKEN "__YOUR_LINE_TOKEN___"

#define FIRMWARE_VERSION "1.0.1"
#define FIRMWARE_LASTUPDATE "2022-02-24"
#define FIRMWARE_SERVER "https://www.mysite.com/firmware/firmware.json"

#define ENABLE_TEST_MODE false  // ###############
#define ENABLE_DEBUG_MODE true
#define DEFAULT_BAUD_RATE 115200
#define DEFAULT_INTERVAL 2000
#define CHECK_FIRMWARE_INTERVAL 120000  // 2 min re-check for update new version
#define ENABLE_LINE_NOTIFY true
#define ENABLE_FIRMWARE_AUTOUPDATE true

const char PRIVATE_KEY[] PROGMEM = "-----BEGIN PRIVATE KEY-----xxxxxxxxxxxxx\n-----END PRIVATE KEY-----\n";

#define DOOR_BTN_PIN_01 15
#endif
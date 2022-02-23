
#ifndef GOOGLE_SHEETS_H
#define GOOGLE_SHEETS_H

#include <Arduino.h>
#include <ESP_Google_Sheet_Client.h>

#include "configs.h"
#include "utility.h"

String START_ROWS = "Datalogger!D3";

void GetSheets(String range) {
    Serial.println("Get spreadsheet values from range...");
    Serial.println("---------------------------------------------------------------");
    FirebaseJson response;
    GSheet.values.get(&response, GOOGLE_SPREADSHEET_ID, range);
    response.toString(Serial, true);
}

void UpdateSheets() {
    FirebaseJson response;
    FirebaseJson valueRange;

    String currentDate = NowString();
    Serial.println("Last updated :" + currentDate);

    String _date = getSplitValue(currentDate, ' ', 0);
    String _time = getSplitValue(currentDate, ' ', 1);

    valueRange.add("majorDimension", "COLUMNS");
    valueRange.set("values/[0]/[0]", _date);
    valueRange.set("values/[1]/[0]", _time);
    valueRange.set("values/[2]/[0]", "OPEN");
    valueRange.set("values/[3]/[0]", DEVICE_NAME);
    valueRange.set("values/[4]/[0]", WiFi.localIP().toString());
    valueRange.set("values/[5]/[0]", "-");

    // For Google Sheet API ref doc, go to https://developers.google.com/sheets/api/reference/rest/v4/spreadsheets.values/append
    bool success = GSheet.values.append(&response, GOOGLE_SPREADSHEET_ID, START_ROWS, &valueRange);
    // response.toString(Serial, true);
    if (success)
        Serial.println("Update spreadsheet successfully!");

    FirebaseJsonArray dataFilterValueRangeArr;
    FirebaseJson dataFilterValueRange1;
    dataFilterValueRange1.set("dataFilter/a1Range", "Datalogger!A10:B10");
    dataFilterValueRange1.set("majorDimension", "COLUMNS");
    dataFilterValueRange1.set("values/[0]/[0]", currentDate);
    dataFilterValueRangeArr.add(dataFilterValueRange1);

    // feedbackDateTimeRenderOption

    // Timestampt last update
    GSheet.values.batchUpdateByDataFilter(&response, GOOGLE_SPREADSHEET_ID, &dataFilterValueRangeArr);
    // response.toString(Serial, true);
}

#endif
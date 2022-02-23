function doGet(e) {
  Logger.log('--- doGet ---');

  var device = '',
    stage = '',
    ip = '',
    imageUrl = '-',
    curr = new Date(),
    version = '2.7';

  try {
    // this helps during debuggin
    if (e == null) {
      e = {};
      e.parameters = { device: 'test', stage: '-1' };
    }

    device = e.parameters.device;
    stage = e.parameters.stage;
    ip = e.parameters.ip;

    var _date = curr.toLocaleDateString('th-TH');
    var _time = curr.toLocaleTimeString('th-TH');
    var dateTime = _date + ' ' + _time;

    // save the data to spreadsheet
    save_data(device, stage, dateTime, ip, imageUrl);

    return ContentService.createTextOutput(
      'Wrote:\n  device: ' +
        device +
        '\n  stage: ' +
        stage +
        '\n  ip address: ' +
        ip +
        '\n  Image Url: ' +
        imageUrl +
        '\n  date: ' +
        dateTime +
        '\n  verion: ' +
        version
    );
  } catch (error) {
    Logger.log(error);
    return ContentService.createTextOutput('oops....' + error.message + '\n' + dateTime + 'device: ' + device + +'stage: ' + stage);
  }
}

// Method to save given data to a sheet
function save_data(device, stage, dateTime, ip, imageUrl) {
  Logger.log('--- save_data ---');

  try {
    // Paste the URL of the Google Sheets starting from https thru /edit
    // For e.g.: https://docs.google.com/..../edit
    var ss = SpreadsheetApp.openByUrl('https://docs.google.com/spreadsheets/d/17gWAoK7FCbC1V0Er-PmLjn-cvRw0JSEWdtUcOEw4T0c/edit');
    var dataLoggerSheet = ss.getSheetByName('Datalogger');

    // Get last edited row from DataLogger sheet
    var row = dataLoggerSheet.getLastRow() + 1;

    // Start Populating the data
    dataLoggerSheet.getRange('A' + row).setValue(dateTime);
    dataLoggerSheet.getRange('B' + row).setValue(stage == 'ON' ? 'เปิด' : 'ปิด');
    dataLoggerSheet.getRange('C' + row).setValue(device);
    dataLoggerSheet.getRange('D' + row).setValue(ip);
    dataLoggerSheet.getRange('E' + row).setValue(imageUrl);

    // Update summary sheet
    // summarySheet.getRange("D1").setValue(dateTime); // Last modified date
    // summarySheet.getRange("B2").setValue(row - 1); // Count
  } catch (error) {
    Logger.log(JSON.stringify(error));
  }

  Logger.log('--- save_data end---');
}

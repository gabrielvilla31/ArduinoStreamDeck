start "Arduino" /min cmd.exe /c Release\StreamDeckServer.exe ArduinoConfig.xml

@start SendMessageToApp.exe -window "Arduino" -msg hide > NUL
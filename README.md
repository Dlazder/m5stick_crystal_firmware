# Simple firmware for M5StickCPlus2 with web interface

Process ids:

0. mainMenu  
1. clock  
2. battery info  
3. settingsMenu  
4. Wi-Fi AP  
5. brightness  
6. rotation

You can use the extension **arduino community edition** for build and upload firmware in vs code.

Here is example of configuration files which I'm using:

.vscode/arduino.json
```
{
    "sketch": "m5stick_power_firmware.ino",
    "port": "/dev/ttyACM0",
    "board": "m5stack:esp32:m5stack_stickc_plus2",
    "output": "./build",
    "programmer": "esptool",
    "configuration": "PSRAM=enabled,PartitionScheme=default_8MB,CPUFreq=240,FlashMode=qio,FlashFreq=80,FlashSize=8M,UploadSpeed=1500000,LoopCore=1,EventsCore=1,DebugLevel=none,EraseFlash=none"
}
```


*.vscode/settings.json*
```
{
    "C_Cpp.intelliSenseEngine": "Tag Parser",
    "C_Cpp.default.includePath": [
        "${workspaceRoot}",
        "~/Arduino/libraries"
    ],
    "arduino.enableUSBDetection": true,
    "arduino.additionalUrls": ["https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/arduino/package_m5stack_index.json"],
    "arduino.disableIntelliSenseAutoGen": true
}
```
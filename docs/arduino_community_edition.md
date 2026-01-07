## Building in vs code

You can use the vs code extension [arduino community edition](https://marketplace.visualstudio.com/items?itemName=vscode-arduino.vscode-arduino-community) for build and upload firmware in **VS Code** without arduino-ide or arduino-cli directly.

Here is example of configuration files for this extension which I'm using:

*.vscode/arduino.json*

```json
{
	"sketch": "m5stick_crystal_firmware.ino",
	"port": "/dev/ttyACM0",
	"board": "m5stack:esp32:m5stack_stickc_plus2",
	"output": "./build",
	"programmer": "esptool",
	"configuration": "PSRAM=enabled,PartitionScheme=default_8MB,CPUFreq=240,FlashMode=qio,FlashFreq=80,FlashSize=8M,UploadSpeed=1500000,LoopCore=1,EventsCore=1,DebugLevel=none,EraseFlash=none"
}
```

*.vscode/settings.json*

```json
{
		// --------------------------
		// Arduino extension settings
		"arduino.enableUSBDetection": true,
		"arduino.additionalUrls": ["https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/arduino/package_m5stack_index.json"],
		"arduino.disableIntelliSenseAutoGen": true,
}
```

Open main file `m5stick_crystal_firmware.ino` and press upload button at the top. This will build and flash your firmware.

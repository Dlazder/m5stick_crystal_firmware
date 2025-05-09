# M5Stick-crystal
<img src="./images/preview.jpg" width="500" alt="Menu demonstration"/>

## Simple, stable, customizible, and extensible.

You can easily add a new function using the short [guide](#how-to-add-a-new-feature).

## Install from M5Burner

You can use the M5Burner for simple firmware installation. Select m5stick in left side menu and start writing in the search line "Crystal".

## How to build?

### Arduino CLI
Libraries:
```
arduino-cli lib install --git-url https://github.com/T-vK/ESP32-BLE-Keyboard
```
Compile:
```
arduino-cli compile --fqbn m5stack:esp32:m5stack_stickc_plus2 --build-path ./build -e --build-property build.partitions=huge_app --build-property upload.maximum_size=3145728 ./m5stick_crystal_firmware.ino
```
Merge binaries:
```
esptool --chip esp32s3 merge_bin --output build/firmware.bin 0x1000 build/m5stick_crystal_firmware.ino.bootloader.bin 0x8000 build/m5stick_crystal_firmware.ino.partitions.bin 0x10000 build/m5stick_crystal_firmware.ino.bin
```
Flash firmware:
```
esptool write_flash 0 build/firmware.bin
```
### Arduino community edition
You can also use the extension **arduino community edition** for build and upload firmware in **VS code**.

Here is example of configuration files for this extension which I'm using:

*.vscode/arduino.json*
```
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


## How to add a new feature?

Add a menu item wherever you want. 
You must specify the name and number of the process that will be launched. You can take the first one available. Check the [process id list](#list-of-process-ids).

*functions/mainMenuLoop.h*
```
MENU mainMenu[] = {
	// other items ...
	{40, "Hello world!"},
};
```
<img src="./images/example-1.png" width="500" alt="Menu demonstration"/>

After that, create a function for the process, let's create a new file for this in the *functions* directory

*functions/helloWorldLoop.h*

```
void helloWorldLoop() {
	if (isSetup()) {
		centeredPrint("Hello world!", SMALL_TEXT);
	}
	checkExit(0);
}
```

In this code, we used functions, one of the “utilities”, necessary to make the code easier and cleaner. They are all located inside files in the utils directory.
Some utilities are already described in the [utilities documentation](#description-of-utilities).

<br>

Add an include of this function next to the others.

*globals/functions.h*

```
// other includes...
#include "../functions/helloWorldLoop.h"
```

Finally, add your process to the processEntries array.

*globals/switcher.h*
```
const ProcessEntry processEntries[] = {
	// ...
	{40, helloWorldLoop},
}
```
## ✨ Result:
<img src="./images/example-2.png" width="500" alt="Program demonstration"/>



### List of process IDs

0. mainMenu
1. clock
2. battery info
3. settingsMenu
4. Wi-Fi AP
5. brightness
6. rotation
7. colors
8. Wi-Fi scan
9. Wi-Fi network menu
10. settings statusBar
11. Wi-Fi deauth
12. Wi-Fi info
13. Wi-Fi Menu
14. Bluetooth Menu
15. Bluetooth camera shutter

### Description of utilities
*Only a small part of the utilities is described here*

<table>
	<tr>
		<th>Utility name and description</th>
		<th>Code example</th>
	</tr>
	<tr>
		<td><code>isBtnBWasPressed</code><br><code>isBtnAWasPressed</code><br>Checks physical clicks and clicks from the web interface. </td>
		<td><code>if (isBtnAWasPressed()) {Serial.print("btn A pressed!")}</code></td>
	</tr>
	<tr>
		<td><code>pressBtnB</code><br><code>pressBtnA</code><br>Emulates a button press. You can try it with utility isBtn..WasPressed)</td>
		<td><code>pressBtnA();<br>if (isBtnAWasPressed()) {Serial.print("btn A pressed!")}</code></td>
	</tr>
	<tr>
		<td><code>isSetup</code><br>Ensures that code within a condition is executed once when the program starts.</td>
		<td><code>if (isSetup()) {Serial.print("run only ones!")}</code></td>
	</tr>
	<tr>
		<td><code>checkExit</code><br>If the user exits the program (presses button B) the process will be switched to the previous one (or pass the ID manually). </td>
		<td><code>checkExit(3)</code></td>
	</tr>
	<tr>
		<td><code>changeProcess</code><br>Switches the process to the one passed in parameters</td>
		<td><code>changeProcess(0)</code></td>
	</tr>
	<tr>
		<td><code>setData</code><br>Writes data to internal memory. Pass the key and value.</td>
		<td><code>setData("brightness", 10);</code></td>
	</tr>
	<tr>
		<td><code>getData</code><br>Get data from internal memory. Pass a key, and a default value that will be returned if the data does not exist.</td>
		<td><code>int brightness = 1;<br>brightness = getData("brightness", brightness)</code></td>
	</tr>
	<tr>
		<td><code>isWebDataRequested</code><br>Checks whether a new line should be generated describing the current state of the interface. You will most likely need to pass the string "function" as the first argument. The second argument is a string that describes the contents of the interface.</td>
		<td><code>if (isWebDataRequested()) {webData = generateWebData("function", generateFunctionElement("text", SMALL_TEXT, "center"));}</code></td>
	</tr>
	<tr>
		<td><code>generateFunctionElement</code><br>Creates and returns a string that describes the text parameters to be displayed inside the web interface. The first parameter is a line with text, the second is size, the third is centering.
		The resulting strings can be combined.</td>
		<td><code>generateFunctionElement("text", SMALL_TEXT, "center")<br> // return  "text,2,center;"</code></td>
	</tr>
</table>


### Web interface screenshot:
<img src="./images/web-interface.png" width="350" alt="web interface"/>

## ❤️ Support my project with a star if you liked it. Contributing is welcome.

I need your support and experience in contributing. Any form of assistance is welcome. Ask any questions through Issues or Disscusions.
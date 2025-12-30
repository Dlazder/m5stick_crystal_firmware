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
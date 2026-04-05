struct ProcessEntry {
    int processId;
    void (*loopFunction)();
};

// Add new processes here
const ProcessEntry processEntries[] = {
    {0, mainMenuLoop},
    {1, clockLoop},
    {2, batteryLoop},
    {3, settingsLoop},
    {4, wifiApLoop},
    {5, brightnessLoop},
    {6, rotationLoop},
    {7, colorsLoop},
    {8, wifiScanLoop},
    {9, selectedWifiMenuLoop},
    {10, settingsStatusBarLoop},
    {11, wifiDeauthLoop},
    {12, wifiInfoLoop},
    {13, wifiMenuLoop},
    {14, bluetoothMenuLoop},
    {15, bluetoothShutterLoop},
    {16, toggleStatusBarLoop},
    {17, toggleStatusBarPidLoop},
    {18, toggleStatusBarBatteryLoop},
    {19, fontsLoop},
    {20, levelToolLoop},
    {21, nfcMenuLoop},
    {22, nfcReadLoop},
    {23, nfcWriteLoop},
    {24, flashLightMenuLoop},
    {25, flashLightLoop},
    {26, flickerLoop}

};

void switcher() {
    for (const ProcessEntry& entry : processEntries) {
        if (entry.processId == process) {
            entry.loopFunction();
            return;
        }
    }
    defaultLoop();
}
struct ProcessEntry {
    int processId;
    void (*loopFunction)();
};

// Add new processes here
const ProcessEntry processEntries[] = {
    {0, mainMenuLoop},
    {1, clockLoop},
    {2, batteryLoop},
    {3, settingsMenuLoop},
    {4, wifiApLoop},
    {5, brightnessLoop},
    {6, rotationLoop},
    {7, colorsLoop},
    {8, wifiScanLoop},
    {9, selectedWifiMenuLoop},
    {10, settingsStatusBarMenuLoop},
    {11, wifiDeauthLoop},
    {12, wifiInfoLoop},
    {13, wifiMenuLoop},
    {14, bluetoothMenuLoop},
    {15, bluetoothShutterLoop},
    {16, toggleStatusBarLoop},
    {17, toggleStatusBarPidLoop},
    {19, fontsLoop},
    {20, levelToolLoop},
    {21, nfcMenuLoop},
    {22, nfcReadLoop},
    {23, nfcWriteLoop},
    {24, flashLightMenuLoop},
    {25, flashLightLoop},
    {26, flickerLoop},
    {27, soundLevelLoop},
    {28, toggleStartupSound},
    {29, otherMenuLoop},
    {30, systemInfoLoop},
    {31, bluetoothMouseLoop},
    {32, bluetoothPresenterLoop},
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
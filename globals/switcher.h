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
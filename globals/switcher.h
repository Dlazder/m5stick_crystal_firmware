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
    {9, wifiMenuLoop},
    {10, settingsStatusBarLoop},
    {11, wifiDeauthLoop},
    {12, wifiInfoLoop}
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
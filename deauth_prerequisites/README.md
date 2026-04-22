**If you don't need to build the firmware yourself, ignore these files.**

This is necessary for the deauthentication function to work.
These scripts modify the platform.txt file to compile the firmware correctly via Arduino CLI.

The file only needs to be run once, choose the correct one depending on your OS.

These files were taken from the m5stick-nemo repository (from [here](https://github.com/n0xa/m5stick-nemo/tree/main/deauth_prerequisites))

For **platofrmio** compilation you need to patch the `ieee80211.0` file using the ar utility and the `ieee80211_output.o` file

```powershell
C:\Users\${env:USERPROFILE}\.platformio\packages\toolchain-xtensa-esp32s3\xtensa-esp32s3-elf\bin\ar.exe rcs C:\Users\${env:USERPROFILE}\.platformio\packages\framework-arduinoespressif32\tools\sdk\esp32\lib\libnet80211.a .\deauth_prerequisites\ieee80211_output.o
```

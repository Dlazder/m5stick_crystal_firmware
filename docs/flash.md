## How to flash firmware once you get binary file?

### Install esptool if you don't have it

```bash
pip install esptool
```

### Flash the binary file

```bash
esptool write_flash 0 firmware.bin
```

Replace firmware.bin with your correct file name.

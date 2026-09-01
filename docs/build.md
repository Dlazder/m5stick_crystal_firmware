# How to build and flash firmware

The easiest way to install firmware on your device is to use m5 burner. But if you want to modify the firmware, you need to build it yourself. This file describes possible build methods. If something doesn’t work out, ask questions via issues.

- [platformio in vs code (recommended)](#building-using-platformio-in-vs-code)
- [platformio in terminal](#building-using-platformio-in-terminal)
- [using binary file from github](#how-to-flash-firmware-once-you-get-binary-file)

## Building using PlatformIO in VS Code

Install platfromio extension, select device and port in bottom panel, then press upload through PlatformIO panel, or use command "PlatformIO: Upload" in command pallete, or use Ctrl + Alt + U hotkey

## Building using PlatformIO in terminal

#### Install PlatformIO

```bash
pip install platformio
```

#### Compile

```bash
# M5StickC Plus2
pio run -e m5stick-c-plus2

# Cardputer-ADV
pio run -e cardputer-adv
```

#### Flash firmware

```bash
# M5StickC Plus2
pio run -e m5stick-c-plus2 --target upload --upload-port COM3

# Cardputer
pio run -e cardputer-adv --target upload --upload-port COM4
```

#### Merge binaries

```bash
# M5StickC Plus2 (ESP32)
esptool.py --chip esp32 merge_bin \
  --output firmware_m5stick-c-plus2.bin \
  0x1000 .pio/build/m5stick-c-plus2/bootloader.bin \
  0x8000 .pio/build/m5stick-c-plus2/partitions.bin \
  0xe000 ~/.platformio/packages/framework-arduinoespressif32/tools/partitions/boot_app0.bin \
  0x10000 .pio/build/m5stick-c-plus2/firmware.bin

# Cardputer/M5StickS3 (ESP32-S3)
esptool.py --chip esp32s3 merge_bin \
  --output firmware_cardputer-adv.bin \
  0x0000 .pio/build/cardputer-adv/bootloader.bin \
  0x8000 .pio/build/cardputer-adv/partitions.bin \
  0xe000 ~/.platformio/packages/framework-arduinoespressif32/tools/partitions/boot_app0.bin \
  0x10000 .pio/build/cardputer-adv/firmware.bin
```

#### Flash firmware

```bash
esptool write_flash 0 build/firmware.bin
```


## How to flash firmware once you get binary file?

#### Install esptool if you don't have it

```bash
pip install esptool
```

#### Flash the binary file

```bash
esptool write_flash 0 firmware.bin
```

Replace firmware.bin with your correct file name.

#### Arduino-CLI

Arduino-CLI has been completely removed from the firmware build methods. PlatformIO provides a faster and more convenient build experience.

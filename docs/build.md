## Building using arduino cli

### Install libraries

```bash
arduino-cli config set library.enable_unsafe_install true
arduino-cli lib install --git-url https://github.com/T-vK/ESP32-BLE-Keyboard

arduino-cli config add board_manager.additional_urls https://static-cdn.m5stack.com/resource/arduino/package_m5stack_index.json
arduino-cli core update-index
arduino-cli core install m5stack:esp32@2.1.2
arduino-cli lib install "M5StickCPlus2"
```

### Deauth prerequisites

Run correct script from `deauth_prerequisites` folder once.

### Compile (This may take a few minutes)

```bash
arduino-cli compile --fqbn m5stack:esp32:m5stack_stickc_plus2 --build-path ./build -e --build-property build.partitions=huge_app --build-property upload.maximum_size=3145728 ./m5stick_crystal_firmware.ino
```

### Merge binaries

```bash
esptool --chip esp32s3 merge_bin --output build/firmware.bin 0x1000 build/m5stick_crystal_firmware.ino.bootloader.bin 0x8000 build/m5stick_crystal_firmware.ino.partitions.bin 0x10000 build/m5stick_crystal_firmware.ino.bin
```

### Flash firmware

```bash
esptool write_flash 0 build/firmware.bin
```

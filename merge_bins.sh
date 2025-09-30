esptool --chip esp32s3 merge_bin --output build/firmware.bin 0x1000 build/m5stick_crystal_firmware.ino.bootloader.bin 0x8000 build/m5stick_crystal_firmware.ino.partitions.bin 0x10000 build/m5stick_crystal_firmware.ino.bin

echo done
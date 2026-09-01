void infoCommand(Print& out) {
	out.printf("Crystal firmware v%d\n", FIRMWARE_VERSION);
	out.printf("Detected board id: %d\n", (int)DEVICE.getBoard());
	out.printf("SDA=%d SCL=%d\n", SDA, SCL);
	out.printf("Battery: %d%% %dV\n", DEVICE.Power.getBatteryLevel(), DEVICE.Power.getBatteryVoltage());
}
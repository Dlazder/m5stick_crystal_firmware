void infoCommand(Print& out) {
	out.printf("Detected board id: %d\n", (int)DEVICE.getBoard());
	out.printf("SDA=%d  SCL=%d\n", SDA, SCL);
}
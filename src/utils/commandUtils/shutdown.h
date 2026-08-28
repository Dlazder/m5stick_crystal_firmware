void shutdownCommand(Print& out) {
	const char* farewells[] = {
		"See you!",
		"Goodbye!",
		"Farewell!",
		"Take care!",
		"Bye bye!",
		"Peace!",
		"Adios!"
	};
	int farewellCount = sizeof(farewells) / sizeof(farewells[0]);
	int randomIndex = random(0, farewellCount);

	out.println(farewells[randomIndex]);

	delay(500);
	DEVICE.Power.powerOff();
}
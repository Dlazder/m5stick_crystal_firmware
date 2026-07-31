#include <WiFiUdp.h>
#include <NTPClient.h>

// Lightweight NTP sync — call after WiFi connects.
// Tries a few quick attempts, returns silently.
static void autoNtpSync() {
	if (!WiFi.isConnected()) return;

	WiFiUDP udp;
	NTPClient client(udp, "pool.ntp.org");
	client.begin();
	client.setTimeOffset(timezoneOffset);

	for (int i = 0; i < 5; i++) {
		if (client.forceUpdate()) {
			unsigned long epoch = client.getEpochTime();
			struct timeval tv = { (time_t)epoch, 0 };
			settimeofday(&tv, nullptr);
			Serial.println("NTP auto-sync OK");
			break;
		}
		delay(500);
	}
	client.end();
}

// PID::SETTINGS_TIMEZONE

static const char* timezoneCities[] = {
	"Baker Island",
	"Pago Pago",
	"Hawaii",
	"Alaska",
	"Los Angeles",
	"Denver",
	"Chicago",
	"New York",
	"Santiago",
	"Buenos Aires",
	"Mid-Atlantic",
	"Azores",
	"London",
	"Berlin",
	"Kyiv",
	"Moscow",
	"Dubai",
	"Karachi",
	"Mumbai",
	"Dhaka",
	"Bangkok",
	"Beijing",
	"Tokyo",
	"Sydney",
	"Solomon Is.",
	"Auckland",
	"Tonga",
};
static const int timezoneOffsets[] = {
	-43200,  // UTC-12
	-39600,  // UTC-11
	-36000,  // UTC-10
	-32400,  // UTC-09
	-28800,  // UTC-08
	-25200,  // UTC-07
	-21600,  // UTC-06
	-18000,  // UTC-05
	-14400,  // UTC-04
	-10800,  // UTC-03
	 -7200,  // UTC-02
	 -3600,  // UTC-01
	      0,  // UTC+00
	   3600,  // UTC+01
	   7200,  // UTC+02
	  10800,  // UTC+03
	  14400,  // UTC+04
	  18000,  // UTC+05
	  19800,  // UTC+05:30
	  21600,  // UTC+06
	  25200,  // UTC+07
	  28800,  // UTC+08
	  32400,  // UTC+09
	  36000,  // UTC+10
	  39600,  // UTC+11
	  43200,  // UTC+12
	  46800,  // UTC+13
};
static const int timezoneCount = sizeof(timezoneOffsets) / sizeof(timezoneOffsets[0]);

static int getTimezoneIndex() {
	for (int i = 0; i < timezoneCount; i++) {
		if (timezoneOffsets[i] == timezoneOffset) return i;
	}
	return 13; // default to UTC+0 (London)
}

static String formatUtcOffset(int offsetSeconds) {
	int totalMin = offsetSeconds / 60;
	int h = totalMin / 60;
	int m = abs(totalMin) % 60;
	char buf[12];
	if (m == 0) {
		snprintf(buf, sizeof(buf), "UTC%+d:00", h);
	} else {
		snprintf(buf, sizeof(buf), "UTC%+d:%02d", h, m);
	}
	return String(buf);
}

void settingsTimezoneLoop() {
	static int tzIndex = 0;
	if (isSetup()) {
		tzIndex = getTimezoneIndex();
		String lines[] = {
			String(L->TXT_SETTINGS_TIMEZONE),
			formatUtcOffset(timezoneOffsets[tzIndex]),
			"(" + String(timezoneCities[tzIndex]) + ")",
		};
		centeredPrintRows(lines, 3, MEDIUM_TEXT, true);
		drawHintSwitch();
		updateTimer();
	}

	if ((isBtnAWasPressed() || isKbEnterPressed()) && checkTimer(100)) {
		tzIndex++;
		if (tzIndex >= timezoneCount) tzIndex = 0;

		timezoneOffset = timezoneOffsets[tzIndex];
		setData("timezone", timezoneOffset);

		String lines[] = {
			String(L->TXT_SETTINGS_TIMEZONE),
			formatUtcOffset(timezoneOffsets[tzIndex]),
			"(" + String(timezoneCities[tzIndex]) + ")",
		};
		centeredPrintRows(lines, 3, MEDIUM_TEXT, true);
		drawHintSwitch();
	}

	checkExit(PID::SETTINGS);
}

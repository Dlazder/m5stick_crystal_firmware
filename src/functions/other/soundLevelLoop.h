static constexpr int SAMPLE_RATE = 44000;
static constexpr size_t SAMPLES = 4096;
static int16_t DATA[SAMPLES];

// Linear interpolation through device-specific calibration table
static float calibrateSoundLevel(float m5_raw) {
	if (m5_raw <= DEVICE_CALIB_TABLE[0][1])
		return DEVICE_CALIB_TABLE[0][0];
	if (m5_raw >= DEVICE_CALIB_TABLE[DEVICE_CALIB_TABLE_SIZE - 1][1])
		return DEVICE_CALIB_TABLE[DEVICE_CALIB_TABLE_SIZE - 1][0];

	for (int i = 0; i < DEVICE_CALIB_TABLE_SIZE - 1; i++) {
		if (m5_raw >= DEVICE_CALIB_TABLE[i][1] && m5_raw <= DEVICE_CALIB_TABLE[i + 1][1]) {
			float x1 = DEVICE_CALIB_TABLE[i][1],     y1 = DEVICE_CALIB_TABLE[i][0];
			float x2 = DEVICE_CALIB_TABLE[i + 1][1], y2 = DEVICE_CALIB_TABLE[i + 1][0];
			return y1 + (m5_raw - x1) * (y2 - y1) / (x2 - x1);
		}
	}
	return m5_raw;
}

float getSoundLevel() {
	DEVICE.Mic.record(DATA, SAMPLES, SAMPLE_RATE, false);

	// RMS calc
	double sum = 0;
	for (size_t i = 0; i < SAMPLES; i++) {
		float s = DATA[i] / 32768.0f;
		sum += s * s;
	}
	float rms = sqrt(sum / SAMPLES);

	// dB into SPL with per-device calibration
	float dbFS = 20 * log10(rms + 1e-12);
	float m5_raw = dbFS + 94.0f;
	float dbSPL = calibrateSoundLevel(m5_raw);

	return dbSPL;
}

void soundLevelLoop() {
	static int barX = 0;
	static int barY;
	static int barW = DISP.width();
	static int barH = 20;

	// Graph
	static const int GRAPH_POINTS = 80;
	static float soundHistory[GRAPH_POINTS];
	static int historyIndex = 0;
	static int historySize = 0;
	static int graphH = 50;
	static int graphY = 0;
	static int frameCount = 0;

	if (isSetup()) {
		DEVICE.Mic.begin();
		canvas.setTextColor(FGCOLOR);
		canvas.setTextSize(MEDIUM_TEXT);

		graphY = canvas.height() - graphH;
		barY = graphY - barH;

		// Clear graph data
		memset(soundHistory, 0, sizeof(soundHistory));
		historyIndex = 0;
		historySize = 0;
	}

	if (checkTimer(50)) {
		updateTimer();
		float soundLevel = getSoundLevel();
		int fillWidth = map(constrain(soundLevel, 0.0f, 100.0f), 0, 100, 0, barW);
		

		soundHistory[historyIndex] = soundLevel;
		historyIndex = (historyIndex + 1) % GRAPH_POINTS;
		if (historySize < GRAPH_POINTS) historySize++;

		// Bar
		canvas.clear();
		int halfWidth = barW / 2;
		canvas.fillGradientRect(barX, barY, halfWidth, barH, TFT_GREEN, TFT_YELLOW, lgfx::gradient_fill_styles::HLINEAR);
		canvas.fillGradientRect(barX + halfWidth, barY, halfWidth, barH, TFT_YELLOW, TFT_RED, lgfx::gradient_fill_styles::HLINEAR);
		if (fillWidth < barW) {
			canvas.fillRect(barX + fillWidth, barY, barW - fillWidth, barH, TFT_BLACK);
		}
		canvas.drawLine(barX, barY, barW, barY, FGCOLOR);

		// Graph
		canvas.drawLine(0, graphY, canvas.width(), graphY, FGCOLOR);
		if (historySize > 1) {
			int startIndex = historyIndex - historySize;
			if (startIndex < 0) startIndex += GRAPH_POINTS;
			for (int i = 0; i < historySize - 1; i++) {
				int idx1 = (startIndex + i) % GRAPH_POINTS;
				int idx2 = (startIndex + i + 1) % GRAPH_POINTS;
				int x1 = i * 3;
				int y1 = graphY + graphH - map(soundHistory[idx1], 0, 100, 0, graphH);
				int x2 = (i + 1) * 3;
				int y2 = graphY + graphH - map(soundHistory[idx2], 0, 100, 0, graphH);
				canvas.drawLine(x1, y1, x2, y2, FGCOLOR);
			}
		}

		// Average and max values under the graph
		float avgLevel = 0.0f;
		float maxLevel = 0.0f;
		if (historySize > 0) {
			maxLevel = soundHistory[0];
			float sumLevel = 0.0f;
			for (int i = 0; i < historySize; i++) {
				float value = soundHistory[i];
				sumLevel += value;
				if (value > maxLevel) maxLevel = value;
			}
			avgLevel = sumLevel / historySize;
		}
		
		char stats[32];
		snprintf(stats, sizeof(stats), "%d  AVG:%d MAX:%d", int(soundLevel), int(avgLevel), int(maxLevel));
		canvas.drawCenterString(stats, canvas.width() / 2, barY - 16 - 10);

		canvas.pushSprite(0, getStatusBarHeight());
	}

	if (isBtnAWasPressed()) {
		memset(soundHistory, 0, sizeof(soundHistory));
		historyIndex = 0;
		historySize = 0;
	}

	if (checkExit()) {
		DEVICE.Mic.end();
		// Mic.end() leaves GPIO pins floating, causing speaker noise
		DEVICE.Speaker.begin();
		DEVICE.Speaker.end();
	}
}
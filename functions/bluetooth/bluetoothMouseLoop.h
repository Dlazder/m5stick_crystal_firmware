// pid 31

// Sensitivity settings
#define GYRO_SENSITIVITY 1.5f
#define DEADZONE 0.05f
#define SMOOTHING_FACTOR 0.3f

#define SPEED_LEVEL1_THRESHOLD 0.15f
#define SPEED_LEVEL2_THRESHOLD 0.35f
#define SPEED_LEVEL3_THRESHOLD 0.55f

#define SPEED_LEVEL1 1
#define SPEED_LEVEL2 5
#define SPEED_LEVEL3 10

auto getSpeed = [](float value) -> int {
	float absVal = abs(value);
	if (absVal < SPEED_LEVEL1_THRESHOLD) {
		return 0;
	} else if (absVal < SPEED_LEVEL2_THRESHOLD) {
		return SPEED_LEVEL1;
	} else if (absVal < SPEED_LEVEL3_THRESHOLD * 1.5f) {
		return SPEED_LEVEL2;
	} else {
		return SPEED_LEVEL3;
	}
};

void bluetoothMouseLoop() {
	static float smoothedX = 0;
	static float smoothedY = 0;
	static bool isBleConnected = false;
	
	float accX, accY, accZ;
	
	if (isSetup()) {
		bleMouse.begin();
		centeredPrint("Waiting connection", SMALL_TEXT);
		updateTimer();
	}
	
	if (bleMouse.isConnected()) {
			if (!isBleConnected) {
				centeredPrint("Connected", SMALL_TEXT);
				isBleConnected = true;
			}
			
			DEVICE.Imu.getAccelData(&accX, &accY, &accZ);
			
			float rawMoveX = accY;
			float rawMoveY = accX;
			
			if (abs(rawMoveX) < DEADZONE) rawMoveX = 0;
			if (abs(rawMoveY) < DEADZONE) rawMoveY = 0;
			
			smoothedX = (smoothedX * (1.0f - SMOOTHING_FACTOR)) + (rawMoveX * SMOOTHING_FACTOR);
			smoothedY = (smoothedY * (1.0f - SMOOTHING_FACTOR)) + (rawMoveY * SMOOTHING_FACTOR);
			
			float absX = abs(smoothedX);
			float absY = abs(smoothedY);
			
			int speedX = getSpeed(smoothedX);
			int speedY = getSpeed(smoothedY);
			
			int deltaX = (smoothedX > 0) ? speedX : -speedX;
			int deltaY = (smoothedY > 0) ? speedY : -speedY;
			
			if (deltaX != 0 || deltaY != 0) {
				bleMouse.move(deltaX, deltaY);
				
				Serial.print("Raw: X=");
				Serial.print(smoothedX, 3);
				Serial.print(", Y=");
				Serial.print(smoothedY, 3);
				Serial.print(" | Move: X=");
				Serial.print(deltaX);
				Serial.print(", Y=");
				Serial.println(deltaY);
			}
			
	} else {
		if (isBleConnected) {
			isBleConnected = false;
			clearScreenWithSymbols();
			centeredPrint("Not connected", SMALL_TEXT);
			smoothedX = 0;
			smoothedY = 0;
		}
	}
		
	if (isBtnAWasPressed() && checkTimer(100, true)) {
			Serial.println("Button A pressed");
			bleMouse.click();
	}
		
	if (checkExit()) {
			bleMouse.end();
			isBleConnected = false;
			centeredPrint("Disconnecting...", SMALL_TEXT);
	}
}
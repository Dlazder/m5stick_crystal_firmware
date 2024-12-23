void writeData(const char* key, int data) {
	preferences.putUInt(key, data);
}

int getData(const char* key, int defaultValue) {
	return preferences.getUInt(key, defaultValue);
}
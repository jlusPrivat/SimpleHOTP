#include "Key.h"


Key::Key (uint8_t *importVal, uint8_t importSize) {
	size = importSize;
	for (uint8_t i = 0; (i < importSize) && (i < 64); i++) {
		key[i] = importVal[i];
	}
}


Key::Key (uint8_t generationSize) {
	size = generationSize;
	for (uint8_t i = 0; (i < generationSize) && (i < 64); i++) {
		key[i] = (uint8_t) random(0xFF);
	}
}


Key::Key (): Key(64) {}


size_t Key::getSize () {
	return size;
}


void Key::exportToArray (uint8_t *expArray) {
	for (uint8_t i = 0; i < size; i++) {
		expArray[i] = key[i];
	}
}
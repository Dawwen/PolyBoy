/**
 * Bibliothèque de l'Arduino.
 */
#include <Arduino.h>

/**
 * Bibliothèque de la carte SD.
 */
#include "PolySD.h"

/**
 * Le pin de sélection de la carte SD.
 */
#define SD_CS 4

/**
 * Initialisation de la carte SD.
 */
void PolySD::begin() {
	Serial.begin(115200);
	Serial.print(F("Initializing SD card..."));

	// Initialisation de la carte SD à 40 MHz.
	if (sd.begin(SD_CS, SD_SCK_MHZ(40))) {
		Serial.println(F("OK !"));
	} else {
		Serial.println(F("Failed !"));
	}

	Serial.end();
}

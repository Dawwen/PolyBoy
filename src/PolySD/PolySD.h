#ifndef PolySD_h
#define PolySD_h

/**
 * Bibliothèque de l'Arduino.
 */
#include <Arduino.h>

/**
 * Bibliothèque de la carte SD.
 */
#include <SdFat.h>

/**
 * Carte SD.
 */
class PolySD {
	public:
		/**
		 * Initialisation de la carte SD.
		 */
		void begin();
	private:
		/**
		 * Carte SD.
		 */
		SdFat sd;
};

#endif

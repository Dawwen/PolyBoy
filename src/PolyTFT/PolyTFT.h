#ifndef PolyTFT_h
#define PolyTFT_h

/**
 * Bibliothèque de l'Arduino.
 */
#include <Arduino.h>

/**
 * Bibliothèque de l'écran TFT.
 */
#include <ILI9341_due_config.h>
#include <ILI9341_due.h>

/**
 * Bibliothèque de la carte SD.
 */
#include <PolySD.h>

/**
 * Bibliothèque d'une image.
 */
#include <Image.h>

/**
 * Bibliothèque d'un sprite.
 */
#include <Sprite.h>

/**
 * Ecran TFT.
 */
class PolyTFT : public ILI9341_due {
	public:
		/**
		 * Constructeur de l'écran TFT.
		 */
		PolyTFT();

		/**
		 * Affiche une image.
		 * @param filename Le chemin d'accès à l'image.
		 * @param x La coordonnée x de l'image.
		 * @param y La coordonnée y de l'image.
		 */
		void drawBitmap(char* filename, int16_t x, int16_t y);

		/**
		 * Affiche une image.
		 * @param image L'image à afficher.
		 */
		void drawBitmap(Image& image);

		/**
		 * Affiche un sprite avec un fond.
		 * @param filename Le chemin d'accès à l'image.
		 * @param x La coordonnée x du sprite.
		 * @param y La coordonnée y du sprite.
		 * @param n La trame d'animation actuelle.
		 * @param total Le nombre de trames d'animation.
		 * @param color La couleur de transparence.
		 * @param background La couleur de fond.
		 */
		void drawSprite(char* filename, int16_t x, int16_t y, uint16_t n, uint16_t total, uint16_t color, uint16_t background);

		/**
		 * Affiche un sprite avec un fond.
		 * @param sprite Le sprite à afficher.
		 * @param background La couleur de fond.
		 */
		void drawSprite(Sprite& sprite, uint16_t background);

		/**
		 * Affiche un sprite sans fond.
		 * @param sprite Le sprite à afficher.
		 */
		void drawSprite(Sprite& sprite);
	protected:
		/**
		 * Récupère deux octets d'un fichier.
		 * @param file Le fichier à récupérer.
		 * @return Deux octets du fichier.
		 */
		uint16_t read16(SdFile& file);

		/**
		 * Récupère quatre octets d'un fichier.
		 * @param file Le fichier à récupérer.
		 * @return Quatre octets du fichier.
		 */
		uint32_t read32(SdFile& file);
};

#endif

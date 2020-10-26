#ifndef Image_h
#define Image_h

/**
 * Bibliothèque de l'Arduino.
 */
#include <Arduino.h>

/**
 * Image.
 */
class Image {
	public:
		/**
		 * Constructeur d'une image.
		 * @param filename Le chemin d'accès à l'image.
		 * @param x La coordonnée x de l'image.
		 * @param y La coordonnée y de l'image.
		 */
		Image(char* filename, int16_t x, int16_t y);

		/**
		 * Récupère le chemin d'accès à l'image.
		 * @return Le chemin d'accès à l'image.
		 */
		char* getFilename();

		/**
		 * Récupère la coordonnée x de l'image.
		 * @return La coordonnée x de l'image.
		 */
		int16_t getX();

		/**
		 * Récupère la coordonnée y de l'image.
		 * @return La coordonnée y de l'image.
		 */
		int16_t getY();

		/**
		 * Définit la coordonnée x de l'image.
		 * @param x La coordonnée x de l'image.
		 */
		void setX(int16_t x);

		/**
		 * Définit la coordonnée y de l'image.
		 * @param y La coordonnée y de l'image.
		 */
		void setY(int16_t y);

		/**
		 * Définit la position de l'image.
		 * @param x La coordonnée x de l'image.
		 * @param y La coordonnée y de l'image.
		 */
		void setPos(int16_t x, int16_t y);
	protected:
		/**
		 * Le chemin d'accès à l'image.
		 */
		char* filename;

		/**
		 * La coordonnée x de l'image.
		 */
		int16_t x;

		/**
		 * La coordonnée y de l'image.
		 */
		int16_t y;
};

#endif

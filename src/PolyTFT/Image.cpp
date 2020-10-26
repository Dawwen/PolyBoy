/**
 * Bibliothèque de l'Arduino.
 */
#include <Arduino.h>

/**
 * Bibliothèque d'une image.
 */
#include <Image.h>

/**
 * Constructeur d'une image.
 * @param filename Le chemin d'accès à l'image.
 * @param x La coordonnée x de l'image.
 * @param y La coordonnée y de l'image.
 */
Image::Image(char* filename, int16_t x, int16_t y)
: filename(filename), x(x), y(y) {}

/**
 * Récupère le chemin d'accès à l'image.
 * @return Le chemin d'accès à l'image.
 */
char* Image::getFilename() {
	return this->filename;
}

/**
 * Récupère la coordonnée x de l'image.
 * @return La coordonnée x de l'image.
 */
int16_t Image::getX() {
	return this->x;
}

/**
 * Récupère la coordonnée y de l'image.
 * @return La coordonnée y de l'image.
 */
int16_t Image::getY() {
	return this->y;
}

/**
 * Définit la coordonnée x de l'image.
 * @param x La coordonnée x de l'image.
 */
void Image::setX(int16_t x) {
	this->x = x;
}

/**
 * Définit la coordonnée y de l'image.
 * @param y La coordonnée y de l'image.
 */
void Image::setY(int16_t y) {
	this->y = y;
}

/**
 * Définit la position de l'image.
 * @param x La coordonnée x de l'image.
 * @param y La coordonnée y de l'image.
 */
void Image::setPos(int16_t x, int16_t y) {
	this->x = x;
	this->y = y;
}

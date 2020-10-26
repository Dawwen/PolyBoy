/**
 * Bibliothèque de l'Arduino.
 */
#include <Arduino.h>

/**
 * Bibliothèque d'une image.
 */
#include <Image.h>

/**
 * Bibliothèque d'un sprite.
 */
#include <Sprite.h>

/**
 * Constructeur d'un sprite.
 * @param filename Le chemin d'accès à l'image.
 * @param x La coordonnée x du sprite.
 * @param y La coordonnée y du sprite.
 * @param n La trame d'animation actuelle.
 * @param total Le nombre de trames d'animation.
 * @param duration La durée d'une trame d'animation.
 * @param animation L'animation est-elle activée ?
 * @param color La couleur de transparence.
 */
Sprite::Sprite(char* filename, int16_t x, int16_t y, uint16_t n, uint16_t total, uint32_t duration, boolean animation, uint16_t color)
: Image(filename, x, y), n(n), total(total), duration(duration), animation(animation), color(color), lastFrame(millis()) {}

/**
 * Constructeur d'un sprite.
 * @param filename Le chemin d'accès à l'image.
 * @param x La coordonnée x du sprite.
 * @param y La coordonnée y du sprite.
 * @param n La trame d'animation actuelle.
 * @param total Le nombre de trames d'animation.
 * @param duration La durée d'une trame d'animation.
 * @param animation L'animation est-elle activée ?
 */
Sprite::Sprite(char* filename, int16_t x, int16_t y, uint16_t n, uint16_t total, uint32_t duration, boolean animation)
: Sprite(filename, x, y, n, total, duration, animation, 0xF81F) {}

/**
 * Constructeur d'un sprite.
 * @param filename Le chemin d'accès à l'image.
 * @param x La coordonnée x du sprite.
 * @param y La coordonnée y du sprite.
 * @param n La trame d'animation actuelle.
 * @param total Le nombre de trames d'animation.
 * @param color La couleur de transparence.
 */
Sprite::Sprite(char* filename, int16_t x, int16_t y, uint16_t n, uint16_t total, uint16_t color)
: Sprite(filename, x, y, n, total, 0, false, color) {}

/**
 * Constructeur d'un sprite.
 * @param filename Le chemin d'accès à l'image.
 * @param x La coordonnée x du sprite.
 * @param y La coordonnée y du sprite.
 * @param n La trame d'animation actuelle.
 * @param total Le nombre de trames d'animation.
 */
Sprite::Sprite(char* filename, int16_t x, int16_t y, uint16_t n, uint16_t total)
: Sprite(filename, x, y, n, total, 0, false, 0xF81F) {}

/**
 * Constructeur d'un sprite.
 * @param filename Le chemin d'accès à l'image.
 * @param x La coordonnée x du sprite.
 * @param y La coordonnée y du sprite.
 * @param color La couleur de transparence.
 */
Sprite::Sprite(char* filename, int16_t x, int16_t y, uint16_t color)
: Sprite(filename, x, y, 1, 1, 0, false, color) {}

/**
 * Constructeur d'un sprite.
 * @param filename Le chemin d'accès à l'image.
 * @param x La coordonnée x du sprite.
 * @param y La coordonnée y du sprite.
 */
Sprite::Sprite(char* filename, int16_t x, int16_t y)
: Sprite(filename, x, y, 1, 1, 0, false, 0xF81F) {}

/**
 * Récupère la trame d'animation actuelle.
 * @return La trame d'animation actuelle.
 */
uint16_t Sprite::getFrame() {
	return this->n;
}

/**
 * Récupère le nombre de trames d'animation.
 * @return Le nombre de trames d'animation.
 */
uint16_t Sprite::getTotal() {
	return this->total;
}

/**
 * Récupère la durée d'une trame d'animation.
 * @return La durée d'une trame d'animation.
 */
uint32_t Sprite::getDuration() {
	return this->duration;
}

/**
 * Récupère la dernière mise à jour d'une trame d'animation.
 * @return La dernière mise à jour d'une trame d'animation.
 */
uint32_t Sprite::getLastFrame() {
	return this->lastFrame;
}

/**
 * Vérifie si l'animation est activée.
 * @return L'animation est-elle activée ?
 */
boolean Sprite::getAnimation() {
	return this->animation;
}

/**
 * Récupère la couleur de transparence.
 * @return La couleur de transparence.
 */
uint16_t Sprite::getColor() {
	return this->color;
}

/**
 * Définit la trame d'animation actuelle.
 * @param n La trame d'animation.
 */
void Sprite::setFrame(uint16_t n) {
	// Définition de la trame.
	this->n = n;

	// Récupération de la dernière mise à jour de la trame.
	this->lastFrame = millis();
}

/**
 * Définit la durée d'une trame d'animation.
 * @param duration La durée d'une trame d'animation.
 */
void Sprite::setDuration(uint32_t duration) {
	this->duration = duration;
}

/**
 * Définit si l'animation est activée.
 * @param animation L'animation est-elle activée ?
 */
void Sprite::setAnimation(boolean animation) {
	this->animation = animation;
}

/**
 * Mise à jour de l'animation.
 */
void Sprite::update() {
	// Si l'animation est activée et que la durée de la trame est dépassée.
	if (animation && millis() - lastFrame >= duration) {
		// Passage de trame.
		n++;

		// Retour à la première trame.
		if (n > total) {
			n = 1;
		}

		// Récupération de la dernière mise à jour de la trame.
		lastFrame = millis();
	}
}

#ifndef Sprite_h
#define Sprite_h

/**
 * Bibliothèque de l'Arduino.
 */
#include <Arduino.h>

/**
 * Bibliothèque d'une image.
 */
#include <Image.h>

/**
 * Sprite.
 */
class Sprite : public Image {
	public:
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
		Sprite(char* filename, int16_t x, int16_t y, uint16_t n, uint16_t total, uint32_t duration, boolean animation, uint16_t color);

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
		Sprite(char* filename, int16_t x, int16_t y, uint16_t n, uint16_t total, uint32_t duration, boolean animation);

		/**
		 * Constructeur d'un sprite.
		 * @param filename Le chemin d'accès à l'image.
		 * @param x La coordonnée x du sprite.
		 * @param y La coordonnée y du sprite.
		 * @param n La trame d'animation actuelle.
		 * @param total Le nombre de trames d'animation.
		 * @param color La couleur de transparence.
		 */
		Sprite(char* filename, int16_t x, int16_t y, uint16_t n, uint16_t total, uint16_t color);

		/**
		 * Constructeur d'un sprite.
		 * @param filename Le chemin d'accès à l'image.
		 * @param x La coordonnée x du sprite.
		 * @param y La coordonnée y du sprite.
		 * @param n La trame d'animation actuelle.
		 * @param total Le nombre de trames d'animation.
		 */
		Sprite(char* filename, int16_t x, int16_t y, uint16_t n, uint16_t total);

		/**
		 * Constructeur d'un sprite.
		 * @param filename Le chemin d'accès à l'image.
		 * @param x La coordonnée x du sprite.
		 * @param y La coordonnée y du sprite.
		 * @param color La couleur de transparence.
		 */
		Sprite(char* filename, int16_t x, int16_t y, uint16_t color);

		/**
		 * Constructeur d'un sprite.
		 * @param filename Le chemin d'accès à l'image.
		 * @param x La coordonnée x du sprite.
		 * @param y La coordonnée y du sprite.
		 */
		Sprite(char* filename, int16_t x, int16_t y);

		/**
		 * Récupère la trame d'animation actuelle.
		 * @return La trame d'animation actuelle.
		 */
		uint16_t getFrame();

		/**
		 * Récupère le nombre de trames d'animation.
		 * @return Le nombre de trames d'animation.
		 */
		uint16_t getTotal();

		/**
		 * Récupère la couleur de transparence.
		 * @return La couleur de transparence.
		 */
		uint16_t getColor();

		/**
		 * Récupère la durée d'une trame d'animation.
		 * @return La durée d'une trame d'animation.
		 */
		uint32_t getDuration();

		/**
		 * Vérifie si l'animation est activée.
		 * @return L'animation est-elle activée ?
		 */
		boolean getAnimation();

		/**
		 * Récupère la dernière mise à jour d'une trame d'animation.
		 * @return La dernière mise à jour d'une trame d'animation.
		 */
		uint32_t getLastFrame();

		/**
		 * Définit la trame d'animation actuelle.
		 * @param n La trame d'animation.
		 */
		void setFrame(uint16_t n);

		/**
		 * Définit la durée d'une trame d'animation.
		 * @param duration La durée d'une trame d'animation.
		 */
		void setDuration(uint32_t duration);

		/**
		 * Définit si l'animation est activée.
		 * @param animation L'animation est-elle activée ?
		 */
		void setAnimation(boolean animation);

		/**
		 * Mise à jour de l'animation.
		 */
		void update();
	protected:
		/**
		 * La trame d'animation actuelle.
		 */
		uint16_t n;

		/**
		 * Le nombre de trames d'animation.
		 */
		const uint16_t total;

		/**
		 * La durée d'une trame d'animation.
		 */
		uint32_t duration;

		/**
		 * La dernière mise à jour de la trame d'animation.
		 */
		uint32_t lastFrame;

		/**
		 * L'animation est-elle activée ?
		 */
		boolean animation;

		/**
		 * La couleur de transparence.
		 */
		const uint16_t color;
};

#endif

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
 * Bibliothèque de l'écran TFT.
 */
#include <PolyTFT.h>

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
 * Le pin de sélection de l'écran TFT.
 */
#define TFT_CS 10

/**
 * Le pin de commande et de donnée de l'écran TFT.
 */
#define TFT_DC 9

/**
 * Le pin de réinitialisation de l'écran TFT.
 */
#define TFT_RST 8

/**
 * La taille du tampon de pixels.
 */
#define BUFFPIXELCOUNT 160

/**
 * Constructeur de l'écran TFT.
 */
PolyTFT::PolyTFT() : ILI9341_due(TFT_CS, TFT_DC, TFT_RST) {}

/**
 * Affiche une image.
 * @param filename Le chemin d'accès à l'image.
 * @param x La coordonnée x de l'image.
 * @param y La coordonnée y de l'image.
 */
void PolyTFT::drawBitmap(char* filename, int16_t x, int16_t y) {
	// Si l'image ne dépasse pas la droite ou le bas de l'écran.
	if (x < width() && y < height()) {
		// Initialisation du fichier de l'image.
		SdFile file;

		// Ouverture du fichier en lecture.
		if (file.open(filename, O_READ)) {
			// S'il s'agit d'une image au format Bitmap.
			if (read16(file) == 0x4D42) {
				// Passage d'informations de l'en-tête.
				file.seekSet(18);

				// Récupération de la largeur de l'image.
				const uint16_t imageWidth = read32(file);

				// Récupération de la hauteur de l'image.
				const uint16_t imageHeight = read32(file);

				// Si l'image est compatible :
				// - Un seul plan.
				// - Une profondeur de 16 bits (format 565).
				// - Pas de compression.
				if (read16(file) == 1 && read16(file) == 16 && read32(file) == 0) {
					// Passage de l'en-tête de l'image.
					file.seekSet(54);

					// Initialisation du tampon.
					uint16_t buffer[BUFFPIXELCOUNT];

					// Initialisation de la largeur d'affichage.
					uint16_t displayWidth = imageWidth;

					// Initialisation de la hauteur d'affichage.
					uint16_t displayHeight = imageHeight;

					// Si la largeur de l'écran est dépassée.
					if ((x + displayWidth - 1) >= width()) {
						// Rognage de la largeur.
						displayWidth = width() - x;
					}

					// Si la hauteur de l'écran est dépassée.
					if ((y + displayHeight - 1) >= height()) {
						// Rognage de la hauteur.
						displayHeight = height() - y;
					}

					// Définition de la fenêtre d'affichage.
					setAddrWindowRect(x, y, displayWidth, displayHeight);

					// Récupération de la définition de l'image.
					const uint32_t totalPixels = (uint32_t)imageWidth * (uint32_t)imageHeight;

					// Récupération du nombre de passages tampon.
					const uint32_t steps = totalPixels / BUFFPIXELCOUNT;

					// Pour chaque passage de tampon.
					for (uint32_t i = 0; i < steps; i++) {
						// Récupération des pixels dans le tampon.
						file.read(buffer, 2 * BUFFPIXELCOUNT);

						// Envoi du tampon vers l'écran.
						pushColors(buffer, 0, BUFFPIXELCOUNT);
					}

					// Récupération des pixels restants.
					const uint32_t remainingPixels = totalPixels % BUFFPIXELCOUNT;

					// S'il reste des pixels après les passages tampon.
					if (remainingPixels > 0) {
						// Récupération des pixels dans le tampon.
						file.read(buffer, 2 * remainingPixels);

						// Envoi du tampon vers l'écran.
						pushColors(buffer, 0, remainingPixels);
					}
				}
			}
		}
		// Fermeture du fichier.
		file.close();
	}
}

/**
 * Affiche une image.
 * @param image L'image à afficher.
 */
void PolyTFT::drawBitmap(Image& image) {
	// Affichage de l'image.
	drawBitmap(
		image.getFilename(),
		image.getX(),
		image.getY()
	);
}

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
void PolyTFT::drawSprite(char* filename, int16_t x, int16_t y, uint16_t n, uint16_t total, uint16_t color, uint16_t background) {
	// Si le sprite ne dépasse pas la droite ou le bas de l'écran.
	if (x < width() && y < height()) {
		// Initialisation du fichier de l'image.
		SdFile file;

		// Ouverture du fichier en lecture.
		if (file.open(filename, O_READ)) {
			// S'il s'agit d'une image au format Bitmap.
			if (read16(file) == 0x4D42) {
				// Passage d'informations de l'en-tête.
				file.seekSet(18);

				// Récupération de la largeur de l'image.
				const uint16_t imageWidth = read32(file);

				// Récupération de la hauteur de l'image.
				const uint16_t imageHeight = read32(file);

				// Récupération de la largeur du sprite.
				const uint16_t spriteWidth = imageWidth / total;

				// Si le sprite ne dépasse pas la gauche ou le haut de l'écran.
				if (x + spriteWidth > 0 && y + imageHeight > 0) {
					// Si l'image est compatible :
					// - Un seul plan.
					// - Une profondeur de 16 bits (format 565).
					// - Pas de compression.
					if (read16(file) == 1 && read16(file) == 16 && read32(file) == 0) {
						// Passage de l'en-tête de l'image.
						file.seekSet(54);

						// Initialisation de la couleur.
						uint16_t pixel = 0;

						// Initialisation de la largeur d'affichage.
						uint16_t displayWidth = spriteWidth;

						// Initialisation de la hauteur d'affichage.
						uint16_t displayHeight = imageHeight;

						// Initialisation des sauts de pixels.
						uint16_t jumpBefore = (n - 1) * spriteWidth;
						uint16_t jumpAfter = (total - n) * spriteWidth;

						// Si le sprite est rogné à gauche de l'écran.
						if (x < 0) {
							// Rognage de la largeur.
							displayWidth = spriteWidth + x;

							// Ajout des pixels rognés au saut de pixels.
							jumpBefore += -x;

							// Remise à zéro de la coordonnée x.
							x = 0;
						}

						// Si le sprite est rogné à droite de l'écran.
						else if ((x + displayWidth - 1) >= width()) {
							// Rognage de la largeur.
							displayWidth = width() - x;

							// Ajout des pixels rognés au saut de pixels.
							jumpAfter += spriteWidth - displayWidth;
						}

						// Si le sprite est rogné en haut de l'écran.
						if (y < 0) {
							// Rognage de la hauteur.
							displayHeight = imageHeight + y;

							// Passage des pixels rognés.
							file.seekCur(2 * (-y * imageWidth));

							// Remise à zéro de la coordonnée y.
							y = 0;
						}

						// Si le sprite est rogné en bas de l'écran.
						else if ((y + displayHeight - 1) >= height()) {
							// Rognage de la hauteur.
							displayHeight = height() - y;
						}

						// Pour chaque ligne.
						for (uint16_t j = y; j < y + displayHeight; j++) {
							// Saut des pixels avant le sprite.
							file.seekCur(2 * jumpBefore);

							// Pour chaque colonne.
							for (uint16_t i = x; i < x + displayWidth; i++) {
								// Récupération d'un pixel.
								pixel = read16(file);

								// S'il ne s'agit pas d'un pixel transparent.
								if (pixel != color) {
									// Envoi du pixel à l'écran.
									drawPixel(i, j, pixel);
								}

								// Si la couleur de fond est bien définie.
								else if (background != color) {
									// Envoi du pixel à l'écran.
									drawPixel(i, j, background);
								}
							}

							// Saut des pixels après le sprite.
							file.seekCur(2 * jumpAfter);
						}
					}
				}
			}
		}

		// Fermeture du fichier.
		file.close();
	}
}

/**
 * Affiche un sprite avec un fond.
 * @param sprite Le sprite à afficher.
 * @param background La couleur de fond.
 */
void PolyTFT::drawSprite(Sprite& sprite, uint16_t background) {
	// Mise à jour du sprite.
	sprite.update();

	// Affichage du sprite.
	drawSprite(
		sprite.getFilename(),
		sprite.getX(),
		sprite.getY(),
		sprite.getFrame(),
		sprite.getTotal(),
		sprite.getColor(),
		background
	);
}

/**
 * Affiche un sprite sans fond.
 * @param sprite Le sprite à afficher.
 */
void PolyTFT::drawSprite(Sprite& sprite) {
	// Récupération de la couleur de transparence.
	uint16_t color = sprite.getColor();

	// Affichage du sprite.
	drawSprite(sprite, color);
}

/**
 * Récupère deux octets d'un fichier.
 * @param file Le fichier à récupérer.
 * @return Deux octets du fichier.
 */
uint16_t PolyTFT::read16(SdFile& file) {
	uint16_t result;
	((uint8_t *)&result)[0] = file.read(); // LSB
	((uint8_t *)&result)[1] = file.read(); // MSB
	return result;
}

/**
 * Récupère quatre octets d'un fichier.
 * @param file Le fichier à récupérer.
 * @return Quatre octets du fichier.
 */
uint32_t PolyTFT::read32(SdFile& file) {
	uint32_t result;
	((uint8_t *)&result)[0] = file.read(); // LSB
	((uint8_t *)&result)[1] = file.read();
	((uint8_t *)&result)[2] = file.read();
	((uint8_t *)&result)[3] = file.read(); // MSB
	return result;
}

/**
 * Bibliothèque de la carte SD.
 */
#include <PolySD.h>

/**
 * Bibliothèque de l'écran TFT.
 */
#include <PolyTFT.h>


/**
 * Initialisation de la carte SD.
 */
PolySD sd;

/**
 * Initialisation de l'écran TFT.
 */
PolyTFT tft;

/**
 * Initialisation de sprites.
 */
Sprite pacman("pacman.565", 0, 0, 1, 16, 1000, true);
Sprite pacman2("pacman.565", 32, 0, 1, 16, 200, true);
Sprite pacman3("pacman.565", 64, 0, 1, 16, 50, true);

/**
 * Initialisation d'une image.
 */
Image background("pacman_background.565", 74, 22);

void setup() {
  // Initialisation de l'écran TFT.
	tft.begin();

  // Initialisation de la carte SD.
  sd.begin();

  // Rotation de l'écran TFT.
  tft.setRotation(iliRotation270);

  // Affichage d'un fond noir.
  tft.fillScreen(0x0000);

  // Affichage du fond.
  tft.drawBitmap(background);
}

uint32_t lastFrame = micros();
void loop() {
  // Affichage du premier sprite (fond rouge).
  tft.drawSprite(pacman, 0xF800);

  // Limitation des trames.
  if (micros() - lastFrame >= 66666) {
    // Affichage d'un fond bleu.
    tft.fillRect(pacman2.getX(), pacman2.getY(), 16, 16, 0x001F);
  
    // Affichage du deuxième sprite (sans fond).
    tft.drawSprite(pacman2);

    // Récupération de la dernière mise à jour de la trame.
    lastFrame = micros();
  }

  // Affichage du troisième sprite (fond noir)
  tft.drawSprite(pacman3, 0x0000);
}

/**
 * Bibliothèque de la manette.
 */
#include <PolyGamepad.h>

/**
 * Initialisation de la manette.
 */
PolyGamepad gamepad;

void setup() {
  // Initialisation de la communication série.
  Serial.begin(115200);

  // Initialisation de la manette.
	gamepad.begin();
}

void loop() {
  // Mise à jour de la manette.
  gamepad.update();

  // Le bouton A est-il pressé ?
  Serial.print("A : ");
  Serial.print(gamepad.isPressed("A"));

  // Le bouton B est-il pressé depuis 1 seconde ?
  Serial.print(" B : ");
  Serial.print(gamepad.isPressedFor("B", 1000));

  // Le bouton X vient-il d'être relaché ?
  Serial.print(" X : ");
  Serial.print(gamepad.wasReleased("X"));

  // Le bouton X vient-il d'être pressé ?
  Serial.print(" Y : ");
  Serial.println(gamepad.wasPressed("Y"));
}

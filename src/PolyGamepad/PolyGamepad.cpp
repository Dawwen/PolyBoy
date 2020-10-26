/**
 * Bibliothèque de l'Arduino.
 */
#include <Arduino.h>

/**
 * Structure d'un bouton.
 */
#include "Button.h"

/**
 * Bibliothèque de la manette.
 */
#include "PolyGamepad.h"

/**
 * Initialisation de la manette.
 */
void PolyGamepad::begin() {
	// Récupération du temps actuel.
	uint32_t ms = millis();

	// Initialisation du tableau de boutons.
	buttons[0] = {"A", 22, 25, false, false, false, ms, ms};
	buttons[1] = {"B", 23, 25, false, false, false, ms, ms};
	buttons[2] = {"X", 24, 25, false, false, false, ms, ms};
	buttons[3] = {"Y", 25, 25, false, false, false, ms, ms};
	buttons[4] = {"UP", 26, 25, false, false, false, ms, ms};
	buttons[5] = {"RIGHT", 27, 25, false, false, false, ms, ms};
	buttons[6] = {"DOWN", 28, 25, false, false, false, ms, ms};
	buttons[7] = {"LEFT", 29, 25, false, false, false, ms, ms};
	buttons[8] = {"START", 30, 25, false, false, false, ms, ms};
	buttons[9] = {"SELECT", 31, 25, false, false, false, ms, ms};
	buttons[10] = {"R", 32, 25, false, false, false, ms, ms};
	buttons[11] = {"L", 33, 25, false, false, false, ms, ms};

	// Pour chaque bouton.
	for (int i = 0; i < 12; i++) {
		// Récupération du bouton.
		Button button = buttons[i];

		// Initialisation du pin du bouton.
		pinMode(button.pin, INPUT_PULLUP);
	}
}

/**
 * Mise à jour de la manette.
 */
void PolyGamepad::update() {
	// Récupération du temps actuel.
	uint32_t ms = millis();

	// Pour chaque bouton.
	for (int i = 0; i < 12; i++) {
		// Récupération de la valeur du pin.
		bool value = !digitalRead(buttons[i].pin);

		// Si le bouton n'a pas eut le temps d'être relâché.
		if (ms - buttons[i].lastChange < buttons[i].debounceTime) {
			// Aucun changement d'état.
			buttons[i].changed = false;
		} else {
			// Récupération de l'état précédent.
			buttons[i].lastState = buttons[i].state;

			// Récupération de l'état actuel.
			buttons[i].state = value;

			// Récupération du changement d'état.
			buttons[i].changed = (buttons[i].state != buttons[i].lastState);

			// Si l'état a changé.
			if (buttons[i].changed) {
				// Récupération du temps de changement d'état.
				buttons[i].lastChange = ms;
			}
		}

		// Récupération du temps de la dernière mise à jour de l'état actuel.
		buttons[i].time = ms;
	}
}

/**
 * Récupère un bouton.
 * @param name Le nom du bouton.
 * @return Le bouton de nom donné.
 */
Button PolyGamepad::getButton(String name) {
	// Initialisation du bouton.
	Button output = {"NOT FOUND", 0, 0, false, false, false, 0, 0};

	// Pour chaque bouton.
	for (int i = 0; i < 12; i++) {
		// Récupération du bouton.
		Button button = buttons[i];

		// Si le bouton est de nom donné.
		if (button.name == name) {
			// Récupération du bouton.
			output = button;
		}
	}

	// On retourne le bouton.
	return output;
}

/**
 * Vérifie si un bouton est pressé.
 * @param name Le nom du bouton.
 * @return <code>true</code> si le bouton est pressé.
 */
bool PolyGamepad::isPressed(String name) {
	// Initialisation de l'état du bouton.
	bool output = false;

	// Récupération du bouton.
	Button button = getButton(name);

	// Si le bouton n'est pas nul.
	if (button.name != "NOT FOUND") {
		// Récupération de l'état du bouton.
		output = button.state;
	}

	// On retourne l'état du bouton.
	return output;
}

/**
 * Vérifie si un bouton est relâché.
 * @param name Le nom du bouton.
 * @return <code>true</code> si le bouton est relâché.
 */
bool PolyGamepad::isReleased(String name) {
	// Initialisation de l'état du bouton.
	bool output = false;

	// Récupération du bouton.
	Button button = getButton(name);

	// Si le bouton n'est pas nul.
	if (button.name != "NOT FOUND") {
		// Récupération de l'état du bouton.
		output = button.state;
	}

	// On retourne l'inverse de l'état du bouton.
	return output;
}

/**
 * Vérifie si un bouton vient d'être pressé.
 * @param name Le nom du bouton.
 * @return <code>true</code> si le bouton vient d'être pressé.
 */
bool PolyGamepad::wasPressed(String name) {
	// Initialisation du résultat.
	bool output = false;

	// Récupération du bouton.
	Button button = getButton(name);

	// Si le bouton n'est pas nul.
	if (button.name != "NOT FOUND") {
		// Récupération du résultat.
		output = button.state && button.changed;
	}

	// On retourne le résultat.
	return output;
}

/**
 * Vérifie si un bouton vient d'être relâché.
 * @param name Le nom du bouton.
 * @return <code>true</code> si le bouton vient d'être relâché.
 */
bool PolyGamepad::wasReleased(String name) {
	// Initialisation du résultat.
	bool output = false;

	// Récupération du bouton.
	Button button = getButton(name);

	// Si le bouton n'est pas nul.
	if (button.name != "NOT FOUND") {
		// Récupération du résultat.
		output = !button.state && button.changed;
	}

	// On retourne le résultat.
	return output;
}

/**
 * Vérifie si un bouton est pressé depuis une certaine durée.
 * @param name Le nom du bouton.
 * @param duration La durée de la pression.
 * @return <code>true</code> si le bouton est pressé depuis au moins la durée donnée.
 */
bool PolyGamepad::isPressedFor(String name, uint32_t duration) {
	// Initialisation du résultat.
	bool output = false;

	// Récupération du bouton.
	Button button = getButton(name);

	// Si le bouton n'est pas nul.
	if (button.name != "NOT FOUND") {
		// Récupération du résultat.
		output = button.state && button.time - button.lastChange >= duration;
	}

	// On retourne le résultat.
	return output;
}

/**
 * Vérifie si un bouton est relâché depuis une certaine durée.
 * @param name Le nom du bouton.
 * @param duration La durée de la relachement.
 * @return <code>true</code> si le bouton est relâché depuis au moins la durée donnée.
 */
bool PolyGamepad::isReleasedFor(String name, uint32_t duration) {
	// Initialisation du résultat.
	bool output = false;

	// Récupération du bouton.
	Button button = getButton(name);

	// Si le bouton n'est pas nul.
	if (button.name != "NOT FOUND") {
		// Récupération du résultat.
		output = !button.state && button.time - button.lastChange >= duration;
	}

	// On retourne le résultat.
	return output;
}

/**
 * Récupère le temps du dernier changement d'état d'un bouton.
 * @param name Le nom du bouton.
 * @return Le temps du dernier changement d'état du bouton.
 */
uint32_t PolyGamepad::getLastChange(String name) {
	// Initialisation du temps du dernier changement d'état du bouton.
	bool output = false;

	// Récupération du bouton.
	Button button = getButton(name);

	// Si le bouton n'est pas nul.
	if (button.name != "NOT FOUND") {
		// Récupération du résultat.
		output = button.lastChange;
	}

	// On retourne le temps du dernier changement d'état du bouton.
	return output;
}

#ifndef PolyController_h
#define PolyController_h

/**
 * Bibliothèque de l'Arduino.
 */
#include <Arduino.h>

/**
 * Structure d'un bouton.
 */
#include "Button.h"

/**
 * Manette.
 */
class PolyGamepad {
	public:
		/**
		 * Initialisation de la manette.
		 */
		void begin();

		/**
		 * Mise à jour de la manette.
		 */
		void update();

		/**
		 * Vérifie si un bouton est pressé.
		 * @param name Le nom du bouton.
		 * @return <code>true</code> si le bouton est pressé.
		 */
		bool isPressed(String name);

		/**
		 * Vérifie si un bouton est relâché.
		 * @param name Le nom du bouton.
		 * @return <code>true</code> si le bouton est relâché.
		 */
		bool isReleased(String name);

		/**
		 * Vérifie si un bouton vient d'être pressé.
		 * @param name Le nom du bouton.
		 * @return <code>true</code> si le bouton vient d'être pressé.
		 */
		bool wasPressed(String name);

		/**
		 * Vérifie si un bouton vient d'être relâché.
		 * @param name Le nom du bouton.
		 * @return <code>true</code> si le bouton vient d'être relâché.
		 */
		bool wasReleased(String name);

		/**
		 * Vérifie si un bouton est pressé depuis une certaine durée.
		 * @param name Le nom du bouton.
		 * @param duration La durée de la pression.
		 * @return <code>true</code> si le bouton est pressé depuis au moins la durée donnée.
		 */
		bool isPressedFor(String name, uint32_t duration);

		/**
		 * Vérifie si un bouton est relâché depuis une certaine durée.
		 * @param name Le nom du bouton.
		 * @param duration La durée de la relachement.
		 * @return <code>true</code> si le bouton est relâché depuis au moins la durée donnée.
		 */
		bool isReleasedFor(String name, uint32_t duration);

		/**
		 * Récupère le temps du dernier changement d'état d'un bouton.
		 * @param name Le nom du bouton.
		 * @return Le temps du dernier changement d'état du bouton.
		 */
		uint32_t getLastChange(String name);
	private:
		/**
		 * Le tableau des boutons.
		 */
		Button buttons[12];

		/**
		 * Récupère un bouton.
		 * @param name Le nom du bouton à récupérer.
		 * @return Le bouton de nom donné.
		 */
		Button getButton(String name);
};

#endif

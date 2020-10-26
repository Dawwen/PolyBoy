#ifndef Button_h
#define Button_h

/**
 * Structure d'un bouton.
 */
struct Button {
	/**
	 * Le nom du bouton.
	 */
	String name;

	/**
	 * Le pin du bouton.
	 */
	uint8_t pin;

	/**
	 * La durée de relachement du bouton.
	 */
	uint32_t debounceTime;

	/**
	 * L'état actuel du bouton.
	 */
	bool state;

	/**
	 * L'état précédent du bouton.
	 */
	bool lastState;

	/**
	 * L'état du bouton a changé ?
	 */
	bool changed;

	/**
	 * Le temps de la dernière mise à jour de l'état actuel du bouton.
	 */
	uint32_t time;

	/**
	 * Le temps du dernier changement d'état du bouton.
	 */
	uint32_t lastChange;
};

/**
 * Type d'un bouton.
 */
typedef struct Button Button;

#endif

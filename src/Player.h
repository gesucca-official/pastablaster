#include "interface.h"
#include "Persona.h"

class Player : public Persona {
public:
	Player(char img[], ControlSet ctrl);
	void handleControls(sf::Event event);

private:
	ControlSet controls;
	//abilities
	void sparks(sf::RenderWindow &window);

};
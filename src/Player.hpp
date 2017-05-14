#include "Persona.hpp"

class Player : public Persona {
public:
	Player(char img[]);
	void handleControls(sf::Event event);

private:
	sf::Keyboard::Key goRight;
};
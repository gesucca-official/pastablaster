#include <SFML/Window.hpp>

typedef struct {
	sf::Keyboard::Key goRight;
	sf::Keyboard::Key goLeft;
	sf::Keyboard::Key goUp;
	sf::Keyboard::Key goDown;

	sf::Keyboard::Key teleport;

	sf::Keyboard::Key ability1;
	sf::Keyboard::Key ability2;
	sf::Keyboard::Key ability3;
	sf::Keyboard::Key ability4;
} ControlSet;

typedef enum {
	N,
	S,
	E,
	W
} Direction;
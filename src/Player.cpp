#include "Player.h"

Player::Player(char img[], ControlSet ctrl) : Persona(img) {
	controls = ctrl;
}

void Player::handleControls(sf::Event event) {

	if (event.type == sf::Event::KeyPressed) {
		//basic movement
		if (event.key.code == controls.goRight)
			run(E);
		if (event.key.code == controls.goLeft) 
			run(W);
		if (event.key.code == controls.goUp) 
			run(N);
		if (event.key.code == controls.goDown) 
			run(S);

		// teleport
		if (event.key.code == controls.teleport) 
			teleport();
	}

	if(event.type == sf::Event::KeyReleased) {
		//basic movement
		if (event.key.code == controls.goRight)
			stop();
		if (event.key.code == controls.goLeft)
			stop();
		if (event.key.code == controls.goUp)
			stop();
		if (event.key.code == controls.goDown)
			stop();
	}
}

void Player::sparks(sf::RenderWindow &window) {


}
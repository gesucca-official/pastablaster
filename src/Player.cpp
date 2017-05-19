#include "headers/characters.h"

#include <iostream> //debug

Player::Player(char img[], Stats s, ControlSet ctrl) : Persona(img, 0, 0, s) {
	controls = ctrl;
}

void Player::handleControls(sf::Event event, std::vector<DrawableObj*> &toBeDrawn) {

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

		// teleport
		if (event.key.code == controls.ability1) 
			ability1(toBeDrawn);
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

// just to try
void Player::ability1(std::vector<DrawableObj*> &toBeDrawn) {

	char bulletImg[] = "./img/Mario_Nintendo.png";
	Bullet *bullet = new Bullet(bulletImg, 100, 100);
	toBeDrawn.push_back(bullet);

}
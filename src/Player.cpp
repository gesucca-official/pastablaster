#include "Player.hpp"

Player::Player(char img[]) : Persona(img) {
	goRight = sf::Keyboard::D;
}

void Player::handleControls(sf::Event event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == goRight) 
			sprite->move(runSpeed, 0);
	}
}

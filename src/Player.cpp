#include "headers/characters.h"

using namespace std;

Player::Player(char img[], Stats s, ControlSet ctrl) : Persona(img, 100, 100, s) {
	controls = ctrl;
	DrawableObj::sprite->setScale(0.6f, 0.6f); //just cause texture is too large...
}

void Player::handleControls(sf::Event event, vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide) {

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

		// shot
		if (event.key.code == controls.ability1) 
			ability1(toBeDrawn, toBeUpd, playerSide);
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
void Player::ability1(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide) {

	char bulletImg[] = "./img/Mario_Nintendo.png";
	sf::Vector2f position = DrawableObj::sprite->getPosition();

	Bullet *bullet = new Bullet(bulletImg, position.x, position.y, Persona::dir);
	bullet->setSpriteScale(0.3f);

	toBeDrawn.push_back(bullet);
	toBeUpd.push_back(bullet);
	playerSide.push_back(bullet);
	
}
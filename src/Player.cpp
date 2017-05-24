#include "headers/characters.h"

using namespace std;

Player::Player(char img[], Stats s, ControlSet ctrl, AbilitySet a) : Persona(img, 100, 100, s) {
	controls = ctrl;
	abilities = a;

	DrawableObj::sprite->setScale(0.6f, 0.6f); //just cause texture is too large...
}

void Player::update(sf::FloatRect fieldBounds) {
	Persona::update(fieldBounds);

	//mana regen
	if (stats.mp < stats.maxMp)
		stats.mp += (float) stats.manaRegen;
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

		// abilities
		if (event.key.code == controls.ability1) 
			bigShotAhead(toBeDrawn, toBeUpd, playerSide);
		if (event.key.code == controls.ability2) 
			smallShotAround(toBeDrawn, toBeUpd, playerSide);
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

void Player::bigShotAhead(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide) {

	if (stats.mp < abilities.a1.manaCost)
		return;

	stats.mp -= abilities.a1.manaCost;

	sf::Vector2f position = DrawableObj::sprite->getPosition();

	Bullet *bullet = new Bullet(abilities.a1.bulletImg, abilities.a1.bulletExplImg, position.x, position.y, dir, abilities.a1);
	bullet->setSpriteScale(0.3f);

	toBeDrawn.push_back(bullet);
	toBeUpd.push_back(bullet);
	playerSide.push_back(bullet);
}

// PIOGGIADIMARIOH to be done
void Player::smallShotAround(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide) {

/*
	char bulletImg[] = "./img/Mario_Nintendo.png";
	sf::Vector2f position = DrawableObj::sprite->getPosition();

	Bullet *bullet1 = new Bullet(bulletImg, position.x, position.y, N, abilities.a1);
	bullet1->setSpriteScale(0.2f);
	Bullet *bullet2 = new Bullet(bulletImg, position.x, position.y, S, abilities.a1);
	bullet2->setSpriteScale(0.2f);
	Bullet *bullet3 = new Bullet(bulletImg, position.x, position.y, E, abilities.a1);
	bullet3->setSpriteScale(0.2f);
	Bullet *bullet4 = new Bullet(bulletImg, position.x, position.y, W, abilities.a1);
	bullet4->setSpriteScale(0.2f);

	toBeDrawn.push_back(bullet1);
	toBeUpd.push_back(bullet1);
	playerSide.push_back(bullet1);

	toBeDrawn.push_back(bullet2);
	toBeUpd.push_back(bullet2);
	playerSide.push_back(bullet2);

	toBeDrawn.push_back(bullet3);
	toBeUpd.push_back(bullet3);
	playerSide.push_back(bullet3);

	toBeDrawn.push_back(bullet4);
	toBeUpd.push_back(bullet4);
	playerSide.push_back(bullet4);
	*/
}
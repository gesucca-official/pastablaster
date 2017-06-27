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
		if (event.key.code == controls.ability3)
			crazyBullet(toBeDrawn, toBeUpd, playerSide);
		if (event.key.code == controls.ability4)
			crazyBulletsBarrage(toBeDrawn, toBeUpd, playerSide);

	}

	if (event.type == sf::Event::KeyReleased) {
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

// first ability in set
void Player::bigShotAhead(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide) {

	if (stats.mp < abilities.a1.manaCost)
		return;

	stats.mp -= abilities.a1.manaCost;

	sf::Vector2f position = DrawableObj::sprite->getPosition();

	Bullet *bullet = new Bullet(abilities.a1.bulletImg, abilities.a1.bulletExplImg, abilities.a1.bulletSoundFx, position.x, position.y, dir, abilities.a1);
	bullet->setSpriteScale(0.3f);
	bullet->setExplScale(0.6f);

	toBeDrawn.push_back(bullet);
	toBeUpd.push_back(bullet);
	playerSide.push_back(bullet);
}

// second ability in set
void Player::smallShotAround(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide) {

	if (stats.mp < abilities.a2.manaCost)
		return;

	stats.mp -= abilities.a2.manaCost;

	sf::Vector2f position = DrawableObj::sprite->getPosition();

	vector<Bullet*> shots;
	shots.push_back(new Bullet(abilities.a2.bulletImg, abilities.a2.bulletExplImg, abilities.a2.bulletSoundFx, position.x, position.y, N, abilities.a2));
	shots.push_back(new Bullet(abilities.a2.bulletImg, abilities.a2.bulletExplImg, abilities.a2.bulletSoundFx, position.x, position.y, S, abilities.a2));
	shots.push_back(new Bullet(abilities.a2.bulletImg, abilities.a2.bulletExplImg, abilities.a2.bulletSoundFx, position.x, position.y, E, abilities.a2));
	shots.push_back(new Bullet(abilities.a2.bulletImg, abilities.a2.bulletExplImg, abilities.a2.bulletSoundFx, position.x, position.y, W, abilities.a2));

	for (int i = 0; i < shots.size(); i++) {
		shots[i]->setSpriteScale(0.2f);
		shots[i]->setExplScale(0.4f);
		toBeDrawn.push_back(shots[i]);
		toBeUpd.push_back(shots[i]);
		playerSide.push_back(shots[i]);
	}
}

// third ability in set
void Player::crazyBullet(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide) {

	if (stats.mp < abilities.a3.manaCost)
		return;

	stats.mp -= abilities.a3.manaCost;

	sf::Vector2f position = DrawableObj::sprite->getPosition();

	Bullet *bullet = new CrazyBullet(abilities.a3.bulletImg, abilities.a3.bulletExplImg, abilities.a3.bulletSoundFx, position.x, position.y, dir, abilities.a3, abilities.a3.crazyness);
	bullet->setSpriteScale(0.3f);
	bullet->setExplScale(0.6f);

	toBeDrawn.push_back(bullet);
	toBeUpd.push_back(bullet);
	playerSide.push_back(bullet);
}

// fourth ability in set
void Player::crazyBulletsBarrage(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide) {

	if (stats.mp < abilities.a4.manaCost)
		return;

	stats.mp -= abilities.a4.manaCost;

	sf::Vector2f position = DrawableObj::sprite->getPosition();

	vector<Bullet*> shots;
	shots.push_back(new CrazyBullet(abilities.a4.bulletImg, abilities.a4.bulletExplImg, abilities.a4.bulletSoundFx, position.x, position.y, N, abilities.a4, abilities.a4.crazyness));
	shots.push_back(new CrazyBullet(abilities.a4.bulletImg, abilities.a4.bulletExplImg, abilities.a4.bulletSoundFx, position.x, position.y, S, abilities.a4, abilities.a4.crazyness));
	shots.push_back(new CrazyBullet(abilities.a4.bulletImg, abilities.a4.bulletExplImg, abilities.a4.bulletSoundFx, position.x, position.y, E, abilities.a4, abilities.a4.crazyness));
	shots.push_back(new CrazyBullet(abilities.a4.bulletImg, abilities.a4.bulletExplImg, abilities.a4.bulletSoundFx, position.x, position.y, W, abilities.a4, abilities.a4.crazyness));

	for (int i = 0; i < shots.size(); i++) {
		shots[i]->setSpriteScale(0.2f);
		shots[i]->setExplScale(0.4f);
		toBeDrawn.push_back(shots[i]);
		toBeUpd.push_back(shots[i]);
		playerSide.push_back(shots[i]);
	}
}
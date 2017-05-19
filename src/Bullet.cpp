#include "headers/objects.h"

Bullet::Bullet(char img[], int posX, int posY) : GameObj(), DrawableObj(img), ModeledObj() {
	//default position
	sprite->move(posX, posY);
}

sf::FloatRect Bullet::getBound() {
	return sprite->getGlobalBounds();
}

void Bullet::update() {}

void Bullet::collide(ModeledObj &collided) {}

bool Bullet::exist() {return true;}

float Bullet::getCollisionDmg() {return 0.0;}

float Bullet::getWeight() {return 1.0;}

#include "headers/objects.h"

Bullet::Bullet(char img[], int posX, int posY, Direction dir) : GameObj(), DrawableObj(img), ModeledObj() {
	//default position
	sprite->move(posX, posY);

	d = dir;

	//load this info from struct Weapon passed by Player
	w.dmg = 50.0;
	w.bullets = 10;
	w.bulletSpeed = 7.5;
	w.shootSpeed = 5.0;

}

sf::FloatRect Bullet::getBound() {
	return sprite->getGlobalBounds();
}

void Bullet::update() {
	if (d==E)
		sprite->move(w.bulletSpeed, 0);
	if (d==W) 
		sprite->move(-w.bulletSpeed, 0);
	if (d==N) 
		sprite->move(0, -w.bulletSpeed);
	if (d==S) 
		sprite->move(0, w.bulletSpeed);
}

void Bullet::collide(ModeledObj &collided) {
	GameObj::exist = false;
}

bool Bullet::exist() {return GameObj::exist;}

float Bullet::getCollisionDmg() {return w.dmg;}

float Bullet::getWeight() {return w.weight;}

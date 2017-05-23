#include "headers/objects.h"

Bullet::Bullet(char img[], int posX, int posY, Direction dir, Ability a) : GameObj(), DrawableObj(img), ModeledObj() {
	//default position
	sprite->move(posX, posY);

	sprite->setOrigin(sprite->getTexture()->getSize().x/2, sprite->getTexture()->getSize().y/2);

	d = dir;
	w = a;

	// texture is drawn UP, so...
	if (d==E)
		sprite->rotate(90);
	if (d==W) 
		sprite->rotate(-90);
	if (d==S) 
		sprite->rotate(180);
}

void Bullet::setSpriteScale(float f) {
	DrawableObj::sprite->setScale(f, f); 
}

sf::FloatRect Bullet::getBound() {
	return sprite->getGlobalBounds();
}

void Bullet::update(sf::FloatRect fieldBounds) {
	if (d==E)
		sprite->move(w.bulletSpeed, 0);
	if (d==W) 
		sprite->move(-w.bulletSpeed, 0);
	if (d==N) 
		sprite->move(0, -w.bulletSpeed);
	if (d==S) 
		sprite->move(0, w.bulletSpeed);

	if (!fieldBounds.intersects(getBound()))
		GameObj::exist = false;
}

void Bullet::collide(ModeledObj &collided) {
	GameObj::exist = false;
}

bool Bullet::exist() {return GameObj::exist;}

float Bullet::getCollisionDmg() {return w.dmg;}

float Bullet::getWeight() {return w.bulletWeight;}

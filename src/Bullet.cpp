#include "headers/objects.h"

Bullet::Bullet(char img[], char explImg[], int posX, int posY, Direction dir, Ability a) : GameObj(), DrawableObj(img), ModeledObj() {
	exploding = false;
	explTime = 0;

	//default position
	sprite->move(posX, posY);
	sprite->setOrigin(sprite->getTexture()->getSize().x/2, sprite->getTexture()->getSize().y/2);

	explTexture.loadFromFile(explImg);
	explTexture.setSmooth(true);

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

	if (exploding) {
		w.dmg = w.dmg/2; // if you remain or return on the explosion. you lose life!
		explTime++;
		if (explTime==w.explFrames)
			GameObj::exist = false;
		return;
	}

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
	exploding = true;

	sprite->setTexture(explTexture, true);
}

inline bool Bullet::exist() {return GameObj::exist;}

inline float Bullet::getCollisionDmg() {return w.dmg;}

inline float Bullet::getWeight() {return w.bulletWeight;}

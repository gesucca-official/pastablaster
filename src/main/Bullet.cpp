#include "headers/objects.h"

Bullet::Bullet(char img[], char explImg[], char soundfx[], int posX, int posY, Direction dir, Ability a) : ModeledObj(img) {
	exploding = false;
	explTime = 0;

	sfxb = new SoundBuffer();
	sfxb->loadFromFile(soundfx);
	sfx = new Sound();
	sfx->setBuffer(*sfxb);

	//default position
	sprite->move(posX, posY);
	sprite->setOrigin(sprite->getTexture()->getSize().x / 2, sprite->getTexture()->getSize().y / 2);

	explTexture.loadFromFile(explImg);
	explTexture.setSmooth(true);

	d = dir;
	w = a;

	// texture is drawn UP, so...
	if (d == E)
		sprite->rotate(90);
	if (d == W)
		sprite->rotate(-90);
	if (d == S)
		sprite->rotate(180);
}

void Bullet::update(sf::FloatRect fieldBounds) {

	if (exploding) {
		w.dmg = w.dmg / w.explDecay; // if you remain or return on the explosion, you lose life!
		explTime++;
		if (explTime == w.explFrames)
			removeFromGame();
		return;
	}

	// movement
	if (d == E)
		sprite->move(w.bulletSpeed, 0);
	if (d == W)
		sprite->move(-w.bulletSpeed, 0);
	if (d == N)
		sprite->move(0, -w.bulletSpeed);
	if (d == S)
		sprite->move(0, w.bulletSpeed);

	if (!fieldBounds.intersects(DrawableObj::getBound()))
		removeFromGame();
}

void CrazyBullet::update(sf::FloatRect fieldBounds) {
	int luck = (rand() % static_cast<int> (256));
	int whereToGo = luck % 3;

	if (crazyness > luck)
		switch (whereToGo) {
			case 0:
				d = N;
				break;
			case 1:
				d = E;
				break;
			case 2:
				d = W;
				break;
			case 3:
				d = S;
				break;
			default:
				break;
		}

	//spinning effect
	if (d == E)
		sprite->rotate(45);
	if (d == W)
		sprite->rotate(-45);
	if (d == S)
		sprite->rotate(135);
	if (d == N)
		sprite->rotate(-135);

	//hue effect
	// ok i'm too tired to think tonight
	// those magic numbers should not exist
	if (hueUp) {
		r += 2;
		g += 4;
		b += 3;
		if (g > 150) {
			g = 150;
			hueUp = false;
		}
	} else {
		b -= 4;
		r -= 1;
		g -= 2;

		if (g < 0) {
			g = 0;
			hueUp = true;
		}

	}
	sprite->setColor(sf::Color(r, g, b, 255));

	Bullet::update(fieldBounds);
}

void Bullet::collide(ModeledObj &collided) {
	exploding = true;
	sfx->play();

	sprite->setTexture(explTexture, true);
	sprite->setScale(explScale, explScale);
}

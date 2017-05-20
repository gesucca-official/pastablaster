#include "headers/objects.h"

Persona::Persona(char img[], int posX, int posY, Stats s) : GameObj(), DrawableObj(img){
	stats = s;
	
	running = false;
	teleporting = false;
	bouncing = false;

	//default position
	sprite->move(posX, posY);
}

void Persona::update(sf::FloatRect fieldBounds) {
	if (currentSpeed<stats.weigth)
		bouncing = false;

	if (bouncing) {
		if (dir==E)
			sprite->move(-currentSpeed, 0);
		if (dir==W) 
			sprite->move(currentSpeed, 0);
		if (dir==N) 
			sprite->move(0, currentSpeed);
		if (dir==S) 
			sprite->move(0, -currentSpeed);
		currentSpeed-= (stats.decel + stats.weigth/9);
		return;
	}

	if (dir==E)
		sprite->move(currentSpeed, 0);
	if (dir==W) 
		sprite->move(-currentSpeed, 0);
	if (dir==N) 
		sprite->move(0, -currentSpeed);
	if (dir==S) 
		sprite->move(0, currentSpeed);

	if (!fieldBounds.intersects(getBound()))
		bouncing = true;

	if (running) {
		currentSpeed+=stats.accel;
		// speed cap
		if (currentSpeed>=stats.maxSpeed) 
			currentSpeed = stats.maxSpeed;
	}
	else if (teleporting)	{
		currentSpeed = 0;
		teleporting = false;
	}
	else
		currentSpeed-= stats.decel;

	if (currentSpeed<0)
		currentSpeed = 0;
}

void Persona::collide(ModeledObj &collided) {

	stats.hp-=collided.getCollisionDmg();

	//why here?
	if (stats.hp<=0.0)
		GameObj::exist = false;

	//bounce!
	running = false;
	teleporting = false;
	bouncing = true;
	currentSpeed += collided.getWeight()/3;
}

float Persona::getCollisionDmg() {
	return stats.collisionDmg;
}

float Persona::getWeight() {
	return stats.weigth;
}

sf::FloatRect Persona::getBound() {
	return sprite->getGlobalBounds();
}

bool Persona::exist() {
	return GameObj::exist;
}

void Persona::run(Direction d) {
	running = true;
	dir = d;
}

void Persona::stop() {
	running = false;
}

//I made this, but... why?
void Persona::turnBack() {
	if (dir==E)
		dir=W;
	if (dir==W) 
		dir=E;
	if (dir==N) 
		dir = S;
	if (dir==S) 
		dir = N;
}

void Persona::teleport() {
	//this should be improved...
	teleporting = true;
	currentSpeed = stats.teleportDist;
}


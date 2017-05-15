#include "Persona.h"

#include <iostream>

Persona::Persona(char img[]) : DrawableObj(img){ //just for now I init here
	currentSpeed = 0.0;
	maxSpeed = 4.5;
	accel = 0.02;
	decel = 0.04;
	running = false;
	teleportDist = 100.0;
	teleporting = false;
}

void Persona::update() {
	if (dir==E)
		sprite->move(currentSpeed, 0);
	if (dir==W) 
		sprite->move(-currentSpeed, 0);
	if (dir==N) 
		sprite->move(0, -currentSpeed);
	if (dir==S) 
		sprite->move(0, currentSpeed);

	if (running) {
		currentSpeed+=accel;
		// speed cap
		if (currentSpeed>=maxSpeed) 
			currentSpeed = maxSpeed;
	}
	else if (teleporting)	{
		currentSpeed = 0;
		teleporting = false;
	}
	else
		currentSpeed-= decel;

	if (currentSpeed<0)
		currentSpeed = 0;
}


void Persona::run(Direction d) {
	running = true;
	dir = d;
}

void Persona::stop() {
	running = false;
}

void Persona::teleport() {
	teleporting = true;
	currentSpeed = teleportDist;
}


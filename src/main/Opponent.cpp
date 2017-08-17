#include "headers/characters.h"

#include <iostream>

Opponent::Opponent(char img[], Stats s, AbilitySet a) : Persona(img, 1150, 400, s) {
	baseDP = (int) s.decisionPace;
	decisionPace = (int) s.decisionPace;
}

void Opponent::update(sf::FloatRect fieldBounds) {
	Persona::update(fieldBounds);
}

// ok, this is a total, fucking mess
void Opponent::handleAI(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &oppoSide) {
	
	// counter this if too close to borders!!
	// magic numberssss, magic constants, I love magic!
	if (sprite->getPosition().x > 1200)
		run(W);
	else if (sprite->getPosition().x < 350)
		run(E);
	else if (sprite->getPosition().y < 400)
		run(S);
	else if (sprite->getPosition().y > 700)
		run(N);
	
	else if (decisionPace == baseDP) {
		//movement
		float wellThoughtDecision  = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		if (wellThoughtDecision < 0.20f)
			run(E);
		else if (wellThoughtDecision < 0.40f && wellThoughtDecision > 0.20f)
			run(W);
		else if (wellThoughtDecision < 0.60f && wellThoughtDecision > 0.40f)
			run(N);
		else if (wellThoughtDecision < 0.80f && wellThoughtDecision > 0.60f)
			run(S);
		else
			stop();

		// reset countdown
		decisionPace = 0;
	}
	else
		decisionPace++;
}

// ability 1
void Opponent::basicAttack(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &oppoSide) {


}
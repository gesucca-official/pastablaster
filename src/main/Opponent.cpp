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
	
	if (decisionPace == 0) {

		//movement
		float wellThoughtDecision  = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		//std::cout << wellThoughtDecision;

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
		decisionPace = baseDP;
	}

	else
	{
		//stop();
		decisionPace--;
	}

	// counter this if too close to borders!!
		// magic numberssss, magic constants, I love magic!
		if (sprite->getPosition().x > 1200)
			run(W);
		else if (sprite->getPosition().x < 350)
			run(E);

		else if (sprite->getPosition().y < 200)
			run(S);
		else if (sprite->getPosition().y > 700)
			run(N);

		cout << "\n";
		cout<<sprite->getPosition().x;
		cout << "x\n";
		cout<<sprite->getPosition().y;
		cout << "y\n";

}

// ability 1
void Opponent::basicAttack(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &oppoSide) {


}
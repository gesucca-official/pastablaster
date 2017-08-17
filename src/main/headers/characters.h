#include "objects.h"

using namespace std;

class Player : public Persona {
public:
	Player(char img[], Stats s, ControlSet ctrl, AbilitySet a);
	
	void update(sf::FloatRect fieldBounds);
	void handleControls(sf::Event event, vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide);

	inline float getMp() {return stats.mp;}

private:
	ControlSet controls;
	AbilitySet abilities;

	void bigShotAhead(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide);
	void smallShotAround(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide);
	void crazyBullet(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide);
	void crazyBulletsBarrage(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide);
};

class Opponent : public Persona {
public:
	Opponent(char img[], Stats s, AbilitySet a);
	void update(sf::FloatRect fieldBounds);
	void handleAI(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &oppoSide);
private:
	int baseDP;
	int decisionPace;
	AbilitySet abilities;

	void basicAttack(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &oppoSide);
};
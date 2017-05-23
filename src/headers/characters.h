#include "objects.h"

using namespace std;

class Player : public Persona {
public:
	Player(char img[], Stats s, ControlSet ctrl, AbilitySet a);
	void handleControls(sf::Event event, vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide);
	inline float getMp() {return stats.mp;}

private:
	ControlSet controls;
	AbilitySet abilities;

	void bigShotAhead(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide);
	void smallShotAround(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide);

};
#include "objects.h"

using namespace std;

class Player : public Persona {
public:
	Player(char img[], Stats s, ControlSet ctrl);
	void handleControls(sf::Event event, vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide);

private:
	ControlSet controls;

	void bigShotAhead(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide);
	void smallShotAround(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide);

};
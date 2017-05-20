#include "objects.h"

using namespace std;

class Player : public Persona {
public:
	Player(char img[], Stats s, ControlSet ctrl);
	void handleControls(sf::Event event, vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide);

private:
	ControlSet controls;

	void ability1(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide);
	void ability2(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide);

};
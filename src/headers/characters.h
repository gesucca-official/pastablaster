#include "objects.h"

class Player : public Persona {
public:
	Player(char img[], Stats s, ControlSet ctrl);
	void handleControls(sf::Event event, std::vector<DrawableObj*> &toBeDrawn);

private:
	ControlSet controls;

	void ability1(std::vector<DrawableObj*> &toBeDrawn);

};
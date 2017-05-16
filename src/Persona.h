#include "models.h"
#include "interface.h"

class Persona: public DrawableObj, public ModeledObj {

private:
	float currentSpeed;
	float maxSpeed;
	float accel;
	float decel;
	bool running;
	float teleportDist;
	bool teleporting;
	Direction dir; //implement direction drawings on drawableobj level?

public:
	Persona(char img[]);

	void update();
	void collide(ModeledObj &collided);
	sf::FloatRect getBound();

	void run(Direction d);
	void stop();
	void teleport();
};
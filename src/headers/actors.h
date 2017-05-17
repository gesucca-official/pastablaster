#include "models.h"
#include "interface.h"

class Persona: public GameObj, public DrawableObj, public ModeledObj {

private:
	float hp;
	float collisionDmg;

	float currentSpeed;
	float maxSpeed;
	float accel;
	float decel;
	bool running;
	float teleportDist;
	bool teleporting;
	Direction dir; //implement direction drawings on drawableobj level?

public:
	Persona(char img[], int posX, int posY);

	void update();
	void collide(ModeledObj &collided);
	sf::FloatRect getBound();
	bool exist();

	float getCollisionDmg();

	void run(Direction d);
	void stop();
	void teleport();
};

class Player : public Persona {
public:
	Player(char img[], ControlSet ctrl);
	void handleControls(sf::Event event);

private:
	ControlSet controls;
	//abilities
	void sparks(sf::RenderWindow &window);

};
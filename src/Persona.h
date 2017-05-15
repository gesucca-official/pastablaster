#include "drw_upd.h"

typedef enum {
	N,
	S,
	E,
	W
} Direction;

class Persona: public DrawableObj, public UpdatableObj {

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
	void run(Direction d);
	void stop();
	void teleport();
};
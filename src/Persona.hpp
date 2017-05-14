#include "DrawableObj.hpp"

class Persona: public DrawableObj {
protected:
	int runSpeed;

public:
	Persona(char img[]) : DrawableObj(img){
		runSpeed = 10;
	} 

};
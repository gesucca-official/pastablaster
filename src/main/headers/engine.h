#include <vector>
#include "characters.h"

using namespace std;

void garbageCollection(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide, vector<ModeledObj*> &oppoSide);
void detectCollisions(vector<ModeledObj*> &playerSide, vector<ModeledObj*> &oppoSide);
void removeOutOfField(sf::FloatRect bound, vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide, vector<ModeledObj*> &oppoSide);
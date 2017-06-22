#include "headers/engine.h"

void garbageCollection(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide, vector<ModeledObj*> &oppoSide) {

	for (int i = 0; i < toBeDrawn.size(); i++) {
		if (!toBeDrawn[i]->doesExists())
			toBeDrawn.erase(std::remove(toBeDrawn.begin(), toBeDrawn.end(), toBeDrawn[i]), toBeDrawn.end());
	}
	for (int i = 0; i < toBeUpd.size(); i++) {
		if (!toBeUpd[i]->doesExists())
			toBeUpd.erase(std::remove(toBeUpd.begin(), toBeUpd.end(), toBeUpd[i]), toBeUpd.end());
	}
	for (int i = 0; i < playerSide.size(); i++) {
		if (!playerSide[i]->doesExists())
			playerSide.erase(std::remove(playerSide.begin(), playerSide.end(), playerSide[i]), playerSide.end());
	}
	for (int i = 0; i < oppoSide.size(); i++) {
		if (!oppoSide[i]->doesExists())
			oppoSide.erase(std::remove(oppoSide.begin(), oppoSide.end(), oppoSide[i]), oppoSide.end());
	}
}

void detectCollisions(vector<ModeledObj*> &playerSide, vector<ModeledObj*> &oppoSide) {

	// awful, but there's no way (or reason) to optimize it
	for (int i = 0; i < playerSide.size(); i++) {
		for (int j = 0; j < oppoSide.size(); j++) {
			if (playerSide[i]->getBound().intersects(oppoSide[j]->getBound())) {
				playerSide[i]->collide(*oppoSide[j]);
				oppoSide[j]->collide(*playerSide[i]);
			}
		}
	}
}

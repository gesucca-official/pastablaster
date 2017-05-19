#include <SFML/Window.hpp>

#define MAX_PATH_LEN 30

typedef struct {
	sf::Keyboard::Key goRight;
	sf::Keyboard::Key goLeft;
	sf::Keyboard::Key goUp;
	sf::Keyboard::Key goDown;

	sf::Keyboard::Key teleport;

	sf::Keyboard::Key ability1;
	sf::Keyboard::Key ability2;
	sf::Keyboard::Key ability3;
	sf::Keyboard::Key ability4;
} ControlSet;

typedef struct {
	float dmg;
	int bullets;
	char bulletImg[MAX_PATH_LEN];
	float bulletSpeed;
	float shootSpeed;
} Weapon;

typedef struct {
	Weapon w1;
	Weapon w2;
	Weapon w3;
	Weapon w4;
} WeaponSet;

typedef struct {
	float hp;
	float weigth;

	float collisionDmg;
	WeaponSet ws;
	
	float maxSpeed;
	float accel;
	float decel;
	
	float teleportDist;
} Stats;
#include "common.h"
struct Controls {
	bool leftPressed: 1;
	bool rightPressed: 1;
	bool upPressed: 1;
};
void GameLoop(Controls controls, u32 dt);

struct Ship {
	Vec2f pos;
	Vec2f acceleration;
	f32 angle;
};
extern Ship globalShip;
extern Vec2f asteroidsPos[10];

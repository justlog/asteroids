#include "common.h"
struct Controls {
	bool leftPressed: 1;
	bool rightPressed: 1;
	bool upPressed: 1;
};
void GameLoop(Controls controls, u64 dt, u64 frequency);

struct Ship {
	Vec2f pos;
	Vec2f bounds;
	Vec2f acceleration;
	f32 angle;
};
struct Asteroid {
	Vec2f pos;
	Vec2f acceleration;
	f32 angle;
};
#define ASTEROID_COUNT 5
extern Ship globalShip;
extern Asteroid asteroids[ASTEROID_COUNT];

#include "common.h"
struct Controls {
	bool leftPressed: 1;
	bool rightPressed: 1;
	bool upPressed: 1;
};
struct Ship {
	Vec2f pos;
	Vec2f acceleration;
	f32 angle;
};
struct Asteroid {
	Vec2f pos;
	Vec2f acceleration;
	f32 angle;
};
struct GameState {
	RenderingContext renderCtx;
	Controls controls;
	u64 dt;
	u64 frequency;
};
void GameLoop(GameState gameState);

#define ASTEROID_COUNT 5
extern Ship globalShip;
extern Asteroid asteroids[ASTEROID_COUNT];

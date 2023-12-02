#include "common.h"
#include "game.h"
#include <math.h>
#include <stdlib.h>
//Midpoint is (0.5,0.5)?
Ship globalShip;
//Ship globalShip = {{0.5f, 0.5f}, {0.0f,0.0f}, 0.0f};
Asteroid asteroids[ASTEROID_COUNT];


//TODO: Change values to represent "how many x per one second"
#define SHIP_ACCELERATION 0.20f
//#define SHIP_ACCELERATION 0.06f
#define MIN_ASTEROID_ACCELERATION 0.05f
#define MAX_ASTEROID_ACCELERATION 0.1f
//#define MIN_ASTEROID_ACCELERATION 0.01f
//#define MAX_ASTEROID_ACCELERATION 0.05f
#define ASTEROID_ANGULAR_VELOCITY 10.f
#define SHIP_ANGULAR_VELOCITY 35.f
#define MAX_ACCEL 0.3f


#define DEG_TO_RAD 3.14159265359/180;

static bool gameInitialized = false;

static u32 clamp(u32 v, u32 min, u32 max)
{
	return v >= min ? (v <= max ? v : max) : min;
}
static f32 clamp(f32 v, f32 min, f32 max)
{
	return v >= min ? (v <= max ? v : max) : min;
}
static f32 DegreeToRadians(f32 deg)
{
	return deg*DEG_TO_RAD;
}
static void RepositionEntity(Vec2f *pos)
{
	if(pos->x > 1.0f){
		pos->x = 0.0f;
	}
	else if(pos->x < 0.0f){
		pos->x = 1.0f;
	}

	if(pos->y > 1.0f){
		pos->y = 0.0f;
	}
	else if(pos->y < 0.0f){
		pos->y = 1.0f;
	}
}
static f32 RandomF32Normalized()
{
	return (f32)(((f32)rand()) / RAND_MAX);
}
void GameLoop(Controls controls, u64 dt, u64 frequency)
{
	if(!gameInitialized){
		gameInitialized = true;
		globalShip = {0};
		globalShip.pos = Vec2f{0.5f, 0.5f};
		globalShip.acceleration = Vec2f{0.f, 0.f};
		globalShip.angle = 0.f;
		srand(0);

		for(u32 i = 0; i < ASTEROID_COUNT; ++i){
			asteroids[i].pos.x = RandomF32Normalized();
			asteroids[i].pos.y = RandomF32Normalized();
			asteroids[i].acceleration.x = clamp(RandomF32Normalized()*MAX_ASTEROID_ACCELERATION, MIN_ASTEROID_ACCELERATION, MAX_ASTEROID_ACCELERATION);
			asteroids[i].acceleration.y = clamp(RandomF32Normalized()*MAX_ASTEROID_ACCELERATION, MIN_ASTEROID_ACCELERATION, MAX_ASTEROID_ACCELERATION);
			asteroids[i].angle = RandomF32Normalized()*360;
		}
	}

	f64 timeElapsedInSeconds = (f64)dt/(f64)frequency;
	//f64 reciprocalDt = (1.f/(f64)dt);
	//f32 reciprocalDt = 1.f-(1.f/(f32)dt);
	f32 addedAcceleration = (f32)(timeElapsedInSeconds*SHIP_ACCELERATION);
	if(controls.upPressed){
		f32 orientationX = cosf(DegreeToRadians(-globalShip.angle));
		f32 orientationY = sinf(DegreeToRadians(-globalShip.angle));
		globalShip.acceleration.x += addedAcceleration*timeElapsedInSeconds*orientationX;
		globalShip.acceleration.y += addedAcceleration*timeElapsedInSeconds*orientationY;
	}
	if(controls.leftPressed){
		globalShip.angle -= timeElapsedInSeconds*SHIP_ANGULAR_VELOCITY;
	}
	if(controls.rightPressed){
		globalShip.angle += timeElapsedInSeconds*SHIP_ANGULAR_VELOCITY;
	}

	globalShip.pos += globalShip.acceleration;
	RepositionEntity(&globalShip.pos);

	globalShip.acceleration.x = clamp(globalShip.acceleration.x, -MAX_ACCEL, MAX_ACCEL);
	globalShip.acceleration.y = clamp(globalShip.acceleration.y, -MAX_ACCEL, MAX_ACCEL);

	for(u32 i = 0 ; i < ASTEROID_COUNT; ++i){
		Asteroid *ast = &asteroids[i];
		ast->pos += Vec2f{(f32)(ast->acceleration.x*timeElapsedInSeconds), (f32)(ast->acceleration.y*timeElapsedInSeconds)};
		ast->angle += ASTEROID_ANGULAR_VELOCITY*timeElapsedInSeconds;
		if(ast->angle > 360.f){
			ast->angle -= 360;
		}
		RepositionEntity(&ast->pos);
	}
}

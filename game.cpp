#include "common.h"
#include "game.h"
#include <math.h>
//Midpoint is (0.5,0.5)?
Ship globalShip = {{0.5f, 0.5f}, {0.0f,0.0f}, 0.0f};
Vec2f asteroidsPos[10];


#define ACCEL_DRAG 0.001f
#define ACCELERATION 0.05f
#define ANGULAR_VELOCITY 25.f
#define MAX_ACCEL 0.3f


#define DEG_TO_RAD 3.14159265359/180;


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
static void RepositionShip()
{
	if(globalShip.pos.x > 1.0f){
		globalShip.pos.x = 0.0f;
	}
	else if(globalShip.pos.x < 0.0f){
		globalShip.pos.x = 1.0f;
	}

	if(globalShip.pos.y > 1.0f){
		globalShip.pos.y = 0.0f;
	}
	else if(globalShip.pos.y < 0.0f){
		globalShip.pos.y = 1.0f;
	}
}
void GameLoop(Controls controls, u32 dt)
{
	f32 reciprocalDt = 1.f/(f32)dt;
	f32 addedAcceleration = reciprocalDt*ACCELERATION;
	if(controls.upPressed){
		f32 orientationX = cosf(DegreeToRadians(-globalShip.angle));
		f32 orientationY = sinf(DegreeToRadians(-globalShip.angle));
		globalShip.acceleration.x += addedAcceleration*reciprocalDt*orientationX;
		globalShip.acceleration.y += addedAcceleration*reciprocalDt*orientationY;
	}
	if(controls.leftPressed){
		globalShip.angle -= reciprocalDt*ANGULAR_VELOCITY;
	}
	if(controls.rightPressed){
		globalShip.angle += reciprocalDt*ANGULAR_VELOCITY;
	}

	globalShip.pos += globalShip.acceleration;
	RepositionShip();

	globalShip.acceleration.x = clamp(globalShip.acceleration.x, -MAX_ACCEL, MAX_ACCEL);
	globalShip.acceleration.y = clamp(globalShip.acceleration.y, -MAX_ACCEL, MAX_ACCEL);
}

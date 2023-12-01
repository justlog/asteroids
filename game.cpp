#include "common.h"
#include "game.h"
#include <math.h>
//Midpoint is (0.5,0.5)?
Ship globalShip = {{0.5f, 0.5f},0.0f, 0.0f};
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
		globalShip.acceleration += addedAcceleration;
	}
	if(controls.downPressed){//Asteroids doesn't have a "down button"
	//	globalShip.acceleration -= addedAcceleration;
	}
	if(controls.leftPressed){
		globalShip.angle -= reciprocalDt*ANGULAR_VELOCITY;
	}
	if(controls.rightPressed){
		globalShip.angle += reciprocalDt*ANGULAR_VELOCITY;
	}
	f32 angX = cosf(DegreeToRadians(-globalShip.angle));
	f32 angY = sinf(DegreeToRadians(-globalShip.angle));


	globalShip.pos.x += globalShip.acceleration*reciprocalDt*angX;
	globalShip.pos.y += globalShip.acceleration*reciprocalDt*angY;
	RepositionShip();

	//TODO: this is wrong, acceleration should take direction into consideration
	f32 shipAccelDrag = (f32)((i32)(globalShip.acceleration != 0))*reciprocalDt*ACCEL_DRAG;
	if(globalShip.acceleration > 0.f){
		shipAccelDrag = -shipAccelDrag;
	}
	globalShip.acceleration += shipAccelDrag*reciprocalDt;

	globalShip.acceleration = clamp(globalShip.acceleration, -MAX_ACCEL, MAX_ACCEL);
}

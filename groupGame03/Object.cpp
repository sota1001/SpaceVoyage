#include "Object.h"

#include "Camera.h"
#include "DxLib.h"
#include "Input.h"

#define PI 3.1415

bool LoopHole::teleportPlayer = false;
int LoopHole::teleX = 0;
int LoopHole::teleY = 0;
float LoopHole::sizeRateChange = 0.2f;
bool LoopHole::loopIn = false;
bool LoopHole::loopOut = false;
float LoopHole::loopX = 0;
float LoopHole::loopY = 0;

Object::Object()
{
}

void Object::Update()
{
}

void Object::Draw()
{
}

void Object::OnCollision()
{
}

void Object::Start()
{
}

void Object::Connect(Object* loopHole)
{
}


LoopHole::LoopHole(float x, float y, int nextX, int nextY)
{

	this->x = x;
	this->y = y;
	this->size = 40;
	this->angle = 0;
	this->nextX = nextX;
	this->nextY = nextY;

	isLoop = false;
	flipOn = false;
	flipValue = 255;
	frame = 0;
	sizeRate = 0.8f;
	rotateSpeed = 1;
	graph = LoadGraph("Images/LoopHole.png");
	lineGraph = LoadGraph("Images/LoopHole_Line.png");
	
}

void LoopHole::Update()
{

	angle += rotateSpeed;
	if (angle >= 360) {
		angle = 0;
		

	}

	if (isLoop) {
		if (rotateSpeed < 10) {
			rotateSpeed += 2;
			if (rotateSpeed > 10) {
				rotateSpeed = 10;
			}
		}

		sizeRate += GetSizeRateChange();

		if (sizeRate >= 25) {
			loopIn = false;
			loopOut = true;
			teleportPlayer = true;

			teleX = loopHole->GetX();
			teleY = loopHole->GetY();

			loopHole->SetX(x);
			loopHole->SetY(y);

			x = teleX;
			y = teleY;


		}

		

	}
	else if(GetLoopOut()){
		if (rotateSpeed > 1) {
			rotateSpeed -= 2;
			if (rotateSpeed < 1) {
				rotateSpeed = 1;
			}
		}

		if (sizeRate > 0.8f) {
			sizeRate -= GetSizeRateChange();

		}
		else {
			loopOut = false;
			isLoop = false;
			sizeRate = 0.8f;
		}
	}
	else {
		
	}
	
	
	

	if(flipOn) {
		flipValue += 10;
		if (flipValue > 255) flipOn = false;
	}
	else {
		flipValue -= 10;
		if (flipValue <= 0) flipOn = true;
	}
	
}

void LoopHole::Draw()
{

	float rateX;
	float rateY;
	
	if (GetLoopIn()) {

		rateX = (x - GetLoopX()) * sizeRate;
		rateY = (y - GetLoopY()) * sizeRate;
	}
	else if (GetLoopOut()) {


		rateX = (x - GetTeleX()) * sizeRate;
		rateY = (y - GetTeleY()) * sizeRate;

	}
	else {
		rateX = 0;
		rateY = 0;
	}

	
	float camX = Camera::GetX();
	float camY = Camera::GetY();
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, flipValue);
	DrawRotaGraph(x - camX + rateX, y - camY + rateY, sizeRate, angle * PI / 180, lineGraph, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawRotaGraph(x - camX + rateX, y - camY + rateY, sizeRate, angle * PI / 180, graph, true);
	DrawBox(x - size - camX, y - size - camY, x + size - camX, y + size - camY, GetColor(0, 255, 0), FALSE);
	
	
}

void LoopHole::OnCollision()
{
	if(Input::isKey(KEY_INPUT_SPACE)) {
		loopX = x;
		loopY = y;
		isLoop = true;
		loopIn = true;
	}

	
}

void LoopHole::Start()
{


	
}

void LoopHole::TeleportDone()
{

	teleportPlayer = false;
	
}

void Object::SetX(float x)
{

	this->x = x;
	
}

void Object::SetY(float y)
{

	this->y = y;
	
}

void LoopHole::Connect(Object* loopHole)
{

	this->loopHole = loopHole;
	
}

Bomb::Bomb(float x, float y)
{

	this->x = x;
	this->y = y;
	this->size = 20;
	isExplode = false;
	
}

void Bomb::Update()
{
}

void Bomb::Draw()
{
	float camX = Camera::GetX();
	float camY = Camera::GetY();

	if (!isExplode) {
		DrawCircle(x - camX, y - camY, size, GetColor(0, 255, 0), true);
	}
	else {
		DrawCircle(x - camX, y - camY, size, GetColor(255, 0, 0), true);
	}
	
	
}

void Bomb::OnCollision()
{

	isExplode = true;
	
}

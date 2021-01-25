#include "Enemy.h"
#include "Object.h"
#include "Camera.h"
#include "DxLib.h"

Enemy::Enemy()
{
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
}

ExplodingEnemy::ExplodingEnemy(float x, float y)
{

	this->x = x;
	this->y = y;
	this->size = 20;
	this->sizeRate = 0.5;
	this->angle = 0;
	graph = LoadGraph("Resource/Images/Enemy.png");
}

void ExplodingEnemy::Update()
{

	if(LoopHole::GetLoopIn()) {
		sizeRate += LoopHole::GetSizeRateChange();
	}
	else if(LoopHole::GetLoopOut()){
		if(sizeRate > 0.5f) {
			sizeRate -= LoopHole::GetSizeRateChange();
		}
	}
	
}

void ExplodingEnemy::Draw()
{

	float rateX;
	float rateY;
	
	if(LoopHole::GetLoopIn()) {
		rateX = (x - LoopHole::GetLoopX()) * sizeRate;
		rateY = (y - LoopHole::GetLoopY()) * sizeRate;
	}
	else if(LoopHole::GetLoopOut()){

		
		rateX = (x - LoopHole::GetTeleX()) * sizeRate;
		rateY = (y - LoopHole::GetTeleY()) * sizeRate;
		
	}
	else {
		rateX = 0;
		rateY = 0;
	}
	
	float cam = Camera::GetX();
	float camY = Camera::GetY();
	
	DrawRotaGraph(x - cam + rateX , y - camY + rateY, sizeRate, angle, graph, true);
	DrawBox(x - size - cam, y - size - camY, x + size - cam, y + size - camY, GetColor(0, 255, 0), false);
	
}



#pragma once
#include "Define.h"
#include "Object.h"
#include <vector>
#include "Camera.h"

class Player {
public:

	Player();

	void Update();
	void InputProcessing();
	void CollisionProcess(Object *objects);
	void LoadObjects(std::vector<Object *> object);

	void AngleCheck(float &x, float &y, float x1, float y1);
	//bool GravityCheck(float x, float y, float x1, float y1);
	//void GravityPull(float &x, float &y, float x1, float y1);
	//void ColorChange();
	//void CameraFollow();
	void Charge();
	void Attack();

	void Draw();

	float GetX() { return x; }
	float GetY() { return y; }

	float GetStartX() { return startX; }
	float GetStartY() { return startY; }

	float GetAttackX() { return attackX; }
	float GetAttackY() { return attackY; }

	bool GetIsAttack() { return isAttack; }

private:

	float x;
	float y;

	float startX;
	float startY;
	float attackX;
	float attackY;

	bool isAttack;

	float speed;

	int color;

	bool isPulled = false;

	int rocketHandle;
	int wingHandle;
	int particleHandle;

	float angleRocketEnd;
	float angleRocket;
	float nowtime;

	int beamSFX;

	int r;
	int g;
	int b;

	int mouseX;
	int mouseY;

	bool isClick;
	bool isMove;

	bool isHover;

	float moveSpeed;

	int charge;
	const int chargeCount = 25;
	int chargeLevel;

	int delay;

	std::vector<Object *> objects;
};
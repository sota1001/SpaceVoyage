#include "Player.h"
#include "DxLib.h"
#include "Collision.h"
#include <cmath>
#include "Input.h"

Player::Player() {
	x = 300;
	y = 300;

	startX = x;
	startY = y;

	attackX = x;
	attackY = y;

	isAttack = false;

	speed = 5;

	color = GetColor(255, 255, 255);

	isPulled = false;

	rocketHandle = LoadGraph("Resource/Image/rocket.png");
	wingHandle = LoadGraph("Resource/Image/rocket_wing.png");
	particleHandle = LoadGraph("Resource/Image/particle.jpg");
	angleRocketEnd = 0;
	angleRocket = 0;
	nowtime = 0;

	beamSFX = LoadSoundMem("beam.mp3");

	r = 255;
	g = 255;
	b = 255;

	mouseX = WIN_WIDTH / 2;
	mouseY = WIN_HEIGHT / 2;

	isClick = false;
	isMove = false;

	isHover = false;

	moveSpeed = 0;

	charge = 0;
	chargeLevel = 0;

	/*cameraCD = true;

	cameraDelay = 0;

	camX = Camera::GetX();
	camY = Camera::GetY();

	nextCamX = 0;
	nextCamY = 0;*/

	delay = 5;
}

void Player::Update() {

	float camX = Camera::GetX();
	float camY = Camera::GetY();

	InputProcessing();

	for (int i = 0; i < objects.size(); i++) {
		CollisionProcess(objects[i]);
	}

	//âÊñ í[èàóù
	if (x < 32) {
		x = 32;
	}
	/*if (x > WIN_WIDTH - 32) {
		x = WIN_WIDTH - 32;
	}*/
	if (y < 32) {
		y = 32;
	}
	/*if (y > WIN_HEIGHT - 32) {
		y = WIN_HEIGHT - 32;
	}*/
	//è’ìÀîªíË


	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		isClick = true;

		Charge();
		GetMousePoint(&mouseX, &mouseY);

		startX = x;
		startY = y;

		attackX = x;
		attackY = y;

		int mousex = mouseX - (x - camX);
		int mousey = mouseY - (y - camY);

		double z = atan2(mousey, mousex);
		double zz = sqrt((mousex * mousex) + (mousey * mousey));
		angleRocketEnd = atan2(mousey, mousex) - PI / 2;
	}
	else {
		int mousex = mouseX - (x - camX);
		int mousey = mouseY - (y - camY);
		double zz = sqrt((mousex * mousex) + (mousey * mousey));
		double z = atan2(mousey, mousex);
		if (isClick) {

			switch (chargeLevel) {
				case 0:

					angleRocketEnd = atan2(mousey, mousex) - PI / 2;

					moveSpeed = 15;


					/*for (int i = -3; i < 4; i++) {

						DrawLineAA(x + camX, y + camY, x + 200.0f * sin((-angleRocketEnd) + 0.3 / i) + camX, y + 200.0f * cos((angleRocketEnd) + 0.3 / i) + camY, GetColor(255, 255, 255), 10);

					}*/
					break;
				case 1:
					angleRocketEnd = atan2(mousey, mousex) - PI / 2;

					moveSpeed = 20;

					x -= (mousex / zz) * 20;
					y -= (mousey / zz) * 20;
					/*for (float i = -3; i < 4; i++) {

						DrawLineAA(x, y, x + 200.0f * sin((-angleRocketEnd) + 0.3 / i), y + 200.0f * cos((angleRocketEnd)+0.3 / i), GetColor(255, 255, 255), 10);

					}*/
					break;
				case 2:
					angleRocketEnd = atan2(mousey, mousex) - PI / 2;

					moveSpeed = 25;

					x -= (mousex / zz) * 100;
					y -= (mousey / zz) * 100;

					isAttack = true;
					/*for (int i = 0; i < 8; i++) {
						SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
						DrawLineAA(x, y, x + 1000.0f * sin((-angleRocketEnd) + 0.3 / i), y + 1000.0f * cos((angleRocketEnd)+0.3 / i), prismLine[i].color, 50);
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
					}*/


					break;
			}
			isMove = true;
			isClick = false;

			charge = 0;
		}
		r = 255;
		g = 255;
		b = 255;
	}

	if (isMove) {
		float camX = Camera::GetX();
		float camY = Camera::GetY();

		int mousex = mouseX - (x - camX);
		int mousey = mouseY - (y - camY);
		double zz = sqrt((mousex * mousex) + (mousey * mousey));
		double z = atan2(mousey, mousex);

		x -= (mousex / zz) * moveSpeed;
		y -= (mousey / zz) * moveSpeed;

		if (abs(attackX - startX) <= WIN_WIDTH / 2) {
			attackX -= (mousex / zz) * moveSpeed * -30;
		}
		else {
			isAttack = false;
		}
		if (abs(attackY - startY) <= WIN_HEIGHT / 2) {
			attackY -= (mousey / zz) * moveSpeed * -30;
		}
		else {
			isAttack = false;
		}
		Attack();
		chargeLevel = 0;
		moveSpeed--;
		if (moveSpeed < 2) {
			isMove = false;
			isHover = true;
		}

	}


	if ((int)angleRocketEnd == (int)(PI + PI / 2)) {
		angleRocketEnd = 0;
	}

	angleRocket += (angleRocketEnd - angleRocket) * 0.1f;


	/*if (isPulled == true) {

		//GravityPull(x, y, x2, y2);
		//AngleCheck(x, y, x2, y2);

	}*/
	DrawFormatString(0, 0, GetColor(225, 225, 225), "%f\nchargeLV:%d", x, chargeLevel);
}

void Player::Draw() {

	float camX = Camera::GetX();
	float camY = Camera::GetY();

	DrawRotaGraph(x - camX, y - camY, 0.25, angleRocket, rocketHandle, true);
	SetDrawBright(r, g, b);
	DrawRotaGraph(x - camX, y - camY, 0.25, angleRocket, wingHandle, true);
	DrawCircle(x - camX, y - camY, 2, GetColor(255, 255, 255));
	SetDrawBright(255, 255, 255);

	/*DrawFormatString(
		0, 100, GetColor(255, 255, 255), "sX:%f\nsY:%f\naX:%f\naY:%f",
		startX, startY, attackX, attackY);*/
}

void Player::InputProcessing() {

	if (Input::isKey(KEY_INPUT_D)) {
		x += 5;
	}

	if (Input::isKey(KEY_INPUT_A)) {
		x -= 5;
	}

	if (Input::isKey(KEY_INPUT_W)) {
		y -= 5;
	}

	if (Input::isKey(KEY_INPUT_S)) {
		y += 5;
	}

	if (LoopHole::CanTeleport()) {

		x = LoopHole::GetTeleX();
		y = LoopHole::GetTeleY();
		LoopHole::TeleportDone();

	}

}

void Player::CollisionProcess(Object *objects) {

	float rangeX = x - objects->GetX();
	float rangeY = y - objects->GetY();
	int _size = objects->GetSize();

	float calc = (rangeX * rangeX) + (rangeY * rangeY);
	float _size2 = _size * _size;

	if (calc < _size2) {

		objects->OnCollision();

	}

}

void Player::LoadObjects(std::vector<Object *> object) {

	this->objects = object;

}

void Player::AngleCheck(float &x, float &y, float x1, float y1) {
	float rangeX = x - x1;
	float rangeY = y - y1;

	float a = sqrt((rangeX * rangeX) + (rangeY * rangeY));

	float speedX = (rangeX / a) * speed;
	float speedY = (rangeY / a) * speed;

	angleRocketEnd = atan2(rangeY, rangeX) - PI / 2;
	if ((int)angleRocketEnd == (int)(PI + PI / 2)) {
		angleRocketEnd = 0;
	}

	angleRocket += (angleRocketEnd - angleRocket) * 0.1f;
}

void Player::Charge() {
	charge++;
	if (charge <= chargeCount) {
		r = 175;
		g = 175;
		chargeLevel = 0;
	}
	else if (charge <= chargeCount * 2) {
		r = 130;
		g = 130;
		chargeLevel = 1;
	}
	else if (charge <= chargeCount * 3) {
		r = 0;
		g = 0;
		chargeLevel = 2;
	}
	else if (charge > chargeCount * 3) {
		r = 255;
		g = 255;
		charge = 0;
	}
}

void Player::Attack() {
	float camX = Camera::GetX();
	float camY = Camera::GetY();

	if (isAttack == true) {
		SetDrawBlendMode(DX_BLENDMODE_ADD, 250);
		DrawLine(startX - camX, startY - camY, attackX - camX, attackY - camY, GetColor(200, 200, 255), 13);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawBlendMode(DX_BLENDMODE_ADD, 250);
		DrawLine(startX - camX, startY - camY, attackX - camX, attackY - camY, GetColor(10, 10, 155), 26);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

//bool Player::GravityCheck(float x, float y, float x1, float y1){
//
//	float rangeX = x - x1;
//	float rangeY = y - y1;
//
//	if ((rangeX * rangeX) + (rangeY * rangeY) <= 500 * 500) {
//		return 1;
//	}
//	else {
//		return 0;
//	}
//}
//
//void Player::GravityPull(float &x, float &y, float x1, float y1){
//	float rangeX = x - x1;
//	float rangeY = y - y1;
//
//	float a = sqrt((rangeX * rangeX) + (rangeY * rangeY));
//
//	//float speedX = (rangeX / a) * speed;
//	//float speedY = (rangeY / a) * speed;
//
//	int angle = atan2(rangeY, rangeX) * 180 / PI;
//
//	//DrawFormatString(0, 0, GetColor(255, 0, 0), "%f", angleRocketEnd);
//
//	angle += 75;
//
//	x -= cos(angle * PI / 180) * 3;
//	y -= sin(angle * PI / 180) * 3;
//}

//void Player::CameraFollow(){
//	int xAxis = WIN_WIDTH / 2;
//	int yAxis = WIN_HEIGHT / 2;
//
//	int xDiff = x - xAxis;
//	int yDiff = y - yAxis;
//
//	nextCamX = -xDiff;
//	nextCamY = -yDiff;
//
//	if (cameraCD) {
//		cameraDelay--;
//		if (cameraDelay <= 0) {
//			if (xDiff < 0 || xDiff > 0) camX += (nextCamX - camX) * 0.2f;
//			if (yDiff < 0 || yDiff > 0) camY += (nextCamY - camY) * 0.2f;
//		}
//
//		if (camX == nextCamX && camY == nextCamY) {
//			cameraCD = false;
//
//		}
//	}
//	camX += (nextCamX - camX) * 0.2f;
//}



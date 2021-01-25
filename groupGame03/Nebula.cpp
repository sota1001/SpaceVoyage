#include "Nebula.h"
#include "DxLib.h"
#include <stdlib.h>
#include "Camera.h"
#include "Input.h"
#include "Define.h"

Nebula::Nebula(int X, int Y) {

	centerX = X;
	centerY = Y;

	rangeWidth = WIN_WIDTH;
	rangeHeight = 50;

	x = centerX + GetRand(rangeWidth) - (rangeWidth / 2);
	y = centerY + GetRand(rangeHeight) - (rangeHeight / 2);
	r = GetRand(12) + 8;

	speed = 1;

	frame = 0.0;

	isActive = 0;

	screenEffectAlpha = 60;

	lightFlag = true;
}

void Nebula::Activate() {

	x = centerX + GetRand(rangeWidth) - (rangeWidth / 2);
	y = centerY + GetRand(rangeHeight) - (rangeHeight / 2);
	r = GetRand(12) + 8;

	frame = 0.0;
	isActive = 1;

}

void Nebula::Update() {

	if (isActive == 1) {
		frame++;
		//x -= 4.9 * speed;
		/*if (x < centerX) {
			x++;
		}
		if (x > centerY) {
			x--;
		}*/
		if (x < 0) {
			isActive = 0;
		}
	}

	//画面スクロール速度
	if (Input::isKey(KEY_INPUT_SPACE)) {
		speed = 2;
	}
	else {
		speed = 1;
	}

	//操作
	if (Input::isKeyTrigger(KEY_INPUT_F)) {
		switch (lightFlag) {
			case false:
				lightFlag = true;
				break;
			case true:
				lightFlag = false;
				break;
		}
	}
}

void Nebula::Draw() {
	float camX = Camera::GetX();
	float camY = Camera::GetY();

	/*float rateX;
	float rateY;

	if (LoopHole::GetLoopIn()) {
		rateX = (x - LoopHole::GetLoopX()) * sizeRate;
		rateY = (y - LoopHole::GetLoopY()) * sizeRate;
	}
	else if (LoopHole::GetLoopOut()) {


		rateX = (x - LoopHole::GetTeleX()) * sizeRate;
		rateY = (y - LoopHole::GetTeleY()) * sizeRate;

	}
	else {
		rateX = 0;
		rateY = 0;
	}*/

	if (isActive == 1) {
		//ライティング
		if (lightFlag == true) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, screenEffectAlpha / 30);
			DrawCircle(x - camX, y - camY, r * 3, GetColor(160, 160, 160), TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_ADD, screenEffectAlpha);
		DrawCircle(x - camX, y - camY, r, GetColor(5, 55, 45), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void Nebula::GenerationRangeDraw() {
	DrawBox(
		centerX - (rangeWidth / 2), centerY - (rangeHeight / 2),
		centerX + (rangeWidth / 2), centerY + (rangeHeight / 2),
		GetColor(232, 232, 232), FALSE
	);
}

int Nebula::GetIsActive() {
	return isActive;
}

float Nebula::GetRadius(){
	return r;
}

#include "BackGround.h"
#include "DxLib.h"
#include <stdlib.h>
#include "Input.h"
#include "Define.h"
#include "Camera.h"

Background::Background(){
	x = GetRand(WIN_WIDTH * 1.5);
	y = GetRand(WIN_HEIGHT * 1.5);
	r = GetRand(3) + 1;
	alpha = GetRand(60) + 30;
	add_Flag = true;
	lightFlag = true;
	isActive = true;
}

void Background::Activate(){
	float camX = Camera::GetX();
	float camY = Camera::GetY();

	x = GetRand(WIN_WIDTH * 1.5 + camX);
	y = GetRand(WIN_HEIGHT * 1.5 + camY);
	r = GetRand(3) + 1;
	alpha = GetRand(60) + 30;
	add_Flag = true;
	isActive = true;
}

void Background::Update(){
	float camX = Camera::GetX();
	float camY = Camera::GetY();

	if (x - camX < - WIN_WIDTH / 2) {
		isActive = false;
	}
	if (x - camX > WIN_WIDTH * 1.5) {
		isActive = false;
	}
	if (y - camY < -WIN_HEIGHT / 2) {
		isActive = false;
	}
	if (y - camY > WIN_HEIGHT * 1.5) {
		isActive = false;
	}

	//点滅
	if (alpha <= 0) {
		add_Flag = true;
	}
	if (alpha >= 90) {
		add_Flag = false;
	}
	if (add_Flag == true) {
		alpha++;
	}
	if (add_Flag == false) {
		alpha--;
	}
	//ライティング切り替え
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

void Background::Draw(){
	float camX = Camera::GetX();
	float camY = Camera::GetY();

	if (isActive == true) {
		SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
		DrawCircle(x - camX, y - camY, r, GetColor(205, 205, 205));
		if (lightFlag == true) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha / 10);
			DrawCircle(x - camX, y - camY, r * 3, GetColor(220, 220, 220), TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

int Background::GetIsActive(){
	return isActive;
}

#include "BackGround.h"
#include "DxLib.h"
#include <stdlib.h>
#include "Input.h"
#include "Define.h"
#include "Camera.h"

Background::Background(){
	x = GetRand(WIN_WIDTH);
	y = GetRand(WIN_HEIGHT - 150) + 50;
	r = GetRand(3) + 1;
	screenEffectAlpha = GetRand(60) + 30;
	add_Flag = true;
	lightFlag = true;
	isActive = true;
}

void Background::Activate(){
	x = WIN_WIDTH + 50;
	y = GetRand(WIN_HEIGHT - 50) + 50;
	r = GetRand(3) + 1;
	screenEffectAlpha = GetRand(60) + 30;
	isActive = true;
}

void Background::Update(){
	//画面スクロール速度
	

	if (x < 0) {
		isActive = false;
	}
	//点滅
	if (screenEffectAlpha <= 0) {
		add_Flag = true;
	}
	if (screenEffectAlpha >= 90) {
		add_Flag = false;
	}
	if (add_Flag == true) {
		screenEffectAlpha++;
	}
	if (add_Flag == false) {
		screenEffectAlpha--;
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
		SetDrawBlendMode(DX_BLENDMODE_ADD, screenEffectAlpha);
		DrawCircle(x - camX, y - camY, r, GetColor(205, 205, 205));
		if (lightFlag == true) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, screenEffectAlpha / 10);
			DrawCircle(x - camX, y - camY, r * 3, GetColor(220, 220, 220), TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

int Background::GetIsActive(){
	return isActive;
}

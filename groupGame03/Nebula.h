#pragma once
#include "Player.h"

class Nebula {
public:

	Nebula(int X, int Y);

	void Activate();
	void Update();//更新

	void Draw();//描画	
	void GenerationRangeDraw();//エミッター発生範囲描画

	int GetIsActive();
	
	float GetX() { return x; }
	float GetY() { return y; }
	float GetRadius();

private:
	//発生範囲の中心座標
	int centerX;
	int centerY;

	//発生範囲
	int rangeWidth;
	int rangeHeight;

	//パーティクル座標
	float x;
	float y;

	//パーティクル半径
	int r;

	//パーティクル速度
	int speed;

	//フレーム
	float frame;

	int isActive;

	//アルファ値
	int alpha;

	//ライティング
	bool lightFlag;

};
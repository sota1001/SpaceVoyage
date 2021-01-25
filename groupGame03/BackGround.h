#pragma once

class Background {
public:
	Background();
	void Activate();
	void Update();//更新
	void Draw();//描画

	int GetIsActive();
private:
	//座標
	int x;
	int y;
	//半径
	int r;
	//アルファ値
	int screenEffectAlpha;
	//ライティング
	bool lightFlag;
	//アルファ加算
	bool add_Flag;

	int isActive;
};
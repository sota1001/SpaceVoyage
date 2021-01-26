#pragma once
#include "Player.h"

class Nebula {
public:

	Nebula(int X, int Y);

	void Activate();
	void Update();//�X�V

	void Draw();//�`��	
	void GenerationRangeDraw();//�G�~�b�^�[�����͈͕`��

	int GetIsActive();
	
	float GetX() { return x; }
	float GetY() { return y; }
	float GetRadius();

private:
	//�����͈͂̒��S���W
	int centerX;
	int centerY;

	//�����͈�
	int rangeWidth;
	int rangeHeight;

	//�p�[�e�B�N�����W
	float x;
	float y;

	//�p�[�e�B�N�����a
	int r;

	//�p�[�e�B�N�����x
	int speed;

	//�t���[��
	float frame;

	int isActive;

	//�A���t�@�l
	int alpha;

	//���C�e�B���O
	bool lightFlag;

};
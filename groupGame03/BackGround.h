#pragma once

class Background {
public:
	Background();
	void Activate();
	void Update();//�X�V
	void Draw();//�`��

	int GetIsActive();
private:
	//���W
	int x;
	int y;
	//���a
	int r;
	//�A���t�@�l
	int screenEffectAlpha;
	//���C�e�B���O
	bool lightFlag;
	//�A���t�@���Z
	bool add_Flag;

	int isActive;
};
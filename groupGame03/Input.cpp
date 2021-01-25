#include "Input.h"
#include "DxLib.h"

char Input::keys[256] = { 0 };
char Input::oldkeys[256] = { 0 };

void Input::Update()
{
	//�ŐV�̃L�[�{�[�h��񂾂������̂͂P�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
	for (int i = 0; i < 256; i++) {
		oldkeys[i] = keys[i];
	}
	//�ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);
}

bool Input::isKey(int key)
{
	return keys[key];
}

bool  Input::isKeyTrigger(int key)
{
	return keys[key] && !oldkeys[key];
}

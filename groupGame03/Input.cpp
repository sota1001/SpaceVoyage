#include "Input.h"
#include "DxLib.h"

char Input::keys[256] = { 0 };
char Input::oldkeys[256] = { 0 };

void Input::Update()
{
	//最新のキーボード情報だったものは１フレーム前のキーボード情報として保存
	for (int i = 0; i < 256; i++) {
		oldkeys[i] = keys[i];
	}
	//最新のキーボード情報を取得
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

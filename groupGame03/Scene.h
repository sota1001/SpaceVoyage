#pragma once
#include "DxLib.h"
#include "Define.h"
#include "BackGround.h"
#include "Nebula.h"
#include "Player.h"
#include "Enemy.h"
#include "Object.h"
#include "Input.h"
#include "Collision.h"
#include "Camera.h"
#include <vector>
#include <math.h>
#include <time.h>

class Scene {
public:

	Scene();
	void Init();
	void Load();
	void Update();

private:

	SCENE currentScene;
	Background *background[STAR_NUM];
	Nebula *emitterUp[EMITTER_MAX];
	Nebula *emitterDown[EMITTER_MAX];
	Player *player;

	std::vector<Enemy *> enemys;
	std::vector<Object *> objects;

	//エミッター密度
	int density;

	int screenEffectGraph;
	int screenEffectAlpha;
	int screenEffectTimer;

	int vignetteAlpha;

	int count;
};

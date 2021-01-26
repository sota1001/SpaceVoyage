#include "Scene.h"

Scene::Scene() {
	count = 0;

	//エミッター密度
	density = 10;

	for (int i = 0; i < STAR_NUM; i++) {
		background[i] = new Background();
	}

	for (int i = 0; i < EMITTER_MAX; i++) {
		emitterUp[i] = new Nebula(WIN_WIDTH / 2, 0);
		emitterDown[i] = new Nebula(WIN_WIDTH / 2, WIN_HEIGHT);
	}
	player = new Player();

	currentScene = SCENE::INIT;

	screenEffectGraph = LoadGraph("Resource/Image/ScreenEffect.png");
	screenEffectAlpha = 0;
	screenEffectTimer = 1;

	vignetteAlpha = 100;
}

void Scene::Init() {
	count = 0;

	//エミッター密度
	density = 10;

	for (int i = 0; i < STAR_NUM; i++) {
		background[i] = new Background();
	}

	for (int i = 0; i < EMITTER_MAX; i++) {
		emitterUp[i] = new Nebula(WIN_WIDTH / 2, 0);
		emitterDown[i] = new Nebula(WIN_WIDTH / 2, WIN_HEIGHT);
	}
	player = new Player();

	currentScene = SCENE::INIT;

	screenEffectGraph = LoadGraph("Resource/Image/ScreenEffect.png");
	screenEffectAlpha = 0;
	screenEffectTimer = 1;

	vignetteAlpha = 100;

	Camera::Reset();
	Load();
	currentScene = SCENE::TITLE;
}

void Scene::Load() {
	objects.push_back(new LoopHole(500, 100, 300, 300));
	objects.push_back(new LoopHole(300, 300, 500, 100));
	objects[0]->Connect(objects[1]);
	objects[1]->Connect(objects[0]);
	objects.push_back(new Bomb(100, 400));
	enemys.push_back(new ExplodingEnemy(300, 300));

	player->LoadObjects(objects);
}

void Scene::Update() {

	Input::Update();

	if (Input::isKeyTrigger(KEY_INPUT_RETURN)) {
		switch (currentScene) {
			case SCENE::TITLE:
				currentScene = SCENE::GAME;
				break;
			case SCENE::GAME:
				currentScene = SCENE::CLEAR;
				break;
			case SCENE::GAMEOVER:
				currentScene = SCENE::ENDING;
				break;
			case SCENE::CLEAR:
				currentScene = SCENE::ENDING;
				break;
			case SCENE::ENDING:
				currentScene = SCENE::INIT;
				break;
		}
	}

	switch (currentScene) {
		case SCENE::INIT:

			Init();

			break;
		case SCENE::TITLE:
			break;
		case SCENE::GAME:
			//更新処理
			//アクティベート
			//背景
			for (int i = 0; i < STAR_NUM; i++) {
				if (background[i]->GetIsActive() == 0) {
					background[i]->Activate();
				}
			}

			//エミッター
			for (int i = 0; i < EMITTER_MAX; i++) {
				if (emitterUp[i]->GetIsActive() == 0) {
					emitterUp[i]->Activate();
					if (i % density == 0) {
						break;
					}
				}
				if (emitterDown[i]->GetIsActive() == 0) {
					emitterDown[i]->Activate();
					if (i % density == 0) {
						break;
					}
				}
			}

			//背景更新
			for (int i = 0; i < STAR_NUM; i++) {
				background[i]->Update();
			}

			//エミッター更新
			for (int i = 0; i < EMITTER_MAX; i++) {
				emitterUp[i]->Update();
				emitterDown[i]->Update();
			}

			//プレイヤー更新
			player->Update();

			//敵更新
			for (int i = 0; i < enemys.size(); i++) enemys[i]->Update();

			//オブジェクト更新
			for (int i = 0; i < objects.size(); i++) objects[i]->Update();

			//カメラ更新
			Camera::Update(player->GetX(), player->GetY());

			//プレイヤー攻撃
			if (player->GetIsAttack() == true) {

				vignetteAlpha = 25;
				if (CollisionPAE(player, enemys[0])) {
					count++;
				}

			}
			else {
				if (vignetteAlpha < 100) {
					vignetteAlpha += 2;
				}
			}

			//衝突判定(プレイヤーとエミッター)
			for (int i = 0; i < EMITTER_MAX; i++) {
				if ((CollisionPN(player, emitterUp[i]) || CollisionPN(player, emitterDown[i])) && screenEffectAlpha < 255) {
					screenEffectTimer++;
					if (screenEffectTimer % 60 == 0) {
						screenEffectAlpha++;
					}
				}
			}
			if (screenEffectAlpha > 0 && screenEffectTimer > 0) {
				screenEffectTimer--;
				if (screenEffectTimer % 2 == 0) {
					screenEffectAlpha--;
				}
				if (screenEffectAlpha == 0) {
					screenEffectTimer = 0;
				}
			}

			//描画処理
			//背景描画
			for (int i = 0; i < STAR_NUM; i++) {
				background[i]->Draw();
			}

			//ビネット描画
			SetDrawBlendMode(DX_BLENDMODE_INVSRC, vignetteAlpha);
			DrawGraph(0, 0, screenEffectGraph, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			//エミッター描画
			for (int i = 0; i < EMITTER_MAX; i++) {
				emitterUp[i]->Draw();
				emitterDown[i]->Draw();
			}

			//オブジェクト描画
			for (int i = 0; i < objects.size(); i++) objects[i]->Draw();

			//敵描画
			for (int i = 0; i < enemys.size(); i++) enemys[i]->Draw();

			//プレイヤー描画
			player->Draw();

			//スクリーンエフェクト描画
			SetDrawBright(20, 220, 180);
			SetDrawBlendMode(DX_BLENDMODE_ADD, screenEffectAlpha);
			DrawGraph(0, 0, screenEffectGraph, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			SetDrawBright(255, 255, 255);

			DrawFormatString(0, 0, GetColor(225, 225, 225), "\n\nCamX:%f", Camera::GetX());
			DrawFormatString(0, 300, GetColor(225, 225, 225), "ヒット回数:%d", count);
			//emitterUp[0]->GenerationRangeDraw();
			break;
		case SCENE::GAMEOVER:
			break;
		case SCENE::CLEAR:
			break;
		case SCENE::ENDING:
			break;
	}

}

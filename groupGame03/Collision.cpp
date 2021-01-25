#include"DxLib.h"
#include"Collision.h"
#include"Define.h"
#include"math.h"

//衝突判定
//bool CollisionPE(Player *player, Enemy *enemy, const int i) {
//
//	//プレイヤー座標を取得
//	float player_X;
//	float player_Y;
//
//	player->Get_player_Position(player_X, player_Y);
//
//	//敵座標を取得(2点)
//	float enemy_X[ENEMY_NUM];
//	float enemy_Y[ENEMY_NUM];
//
//	enemy->Get_enemy_Position(enemy_X, enemy_Y);
//
//	float enemy_X2[ENEMY_NUM];
//	float enemy_Y2[ENEMY_NUM];
//
//	enemy_X2[i] = enemy_X[i] + GRAPH_SIZE;
//	enemy_Y2[i] = enemy_Y[i] + GRAPH_SIZE;
//
//	//衝突判定
//	if (enemy_X[i] < player_X && player_X < enemy_X2[i] &&
//		enemy_Y[i] < player_Y && player_Y < enemy_Y2[i]) {
//		return true;
//	}
//
//	return false;
//}

bool CollisionPAE(Player *player, Enemy *enemy){
	return false;
}

bool CollisionPN(Player *player, Nebula *nebula){
	//プレイヤー座標を取得
	float playerX = player->GetX();
	float playerY = player->GetY();
	float playerR = 32;

	//パーティクル座標を取得
	float particleX = nebula->GetX();
	float particleY = nebula->GetY();
	float particleR = nebula->GetRadius();

	float distanceX = pow((double)particleX - playerX, 2);
	float distanceY = pow((double)particleY - playerY, 2);
	float distance = distanceX + distanceY;

	if (sqrtf(distance) < playerR + particleR * 3) {
		return true;
	}
	return false;
}

bool CollisionPO(Player *player, Object *object){
	//プレイヤー座標を取得
	float playerX = player->GetX();
	float playerY = player->GetY();
	float playerR = 32;

	//オブジェクト座標を取得
	float objectX = object->GetX();
	float objectY = object->GetY();
	float objectR = object->GetSize();

	float distanceX = pow((double)objectX - playerX, 2);
	float distanceY = pow((double)objectY - playerY, 2);
	float distance = distanceX + distanceY;

	if (sqrtf(distance) < playerR + objectR) {
		return true;
	}
	return false;
}

#include"DxLib.h"
#include"Collision.h"
#include"Define.h"
#include"math.h"

//�Փ˔���
//bool CollisionPE(Player *player, Enemy *enemy, const int i) {
//
//	//�v���C���[���W���擾
//	float player_X;
//	float player_Y;
//
//	player->Get_player_Position(player_X, player_Y);
//
//	//�G���W���擾(2�_)
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
//	//�Փ˔���
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
	//�v���C���[���W���擾
	float playerX = player->GetX();
	float playerY = player->GetY();
	float playerR = 32;

	//�p�[�e�B�N�����W���擾
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
	//�v���C���[���W���擾
	float playerX = player->GetX();
	float playerY = player->GetY();
	float playerR = 32;

	//�I�u�W�F�N�g���W���擾
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

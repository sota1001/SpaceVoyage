#pragma once
#include "Player.h"
#include "Nebula.h"
#include "Enemy.h"
#include "Object.h"

//�Փ˔���(�v���C���[�ƓG)
//bool CollisionPE(Player *player, Enemy *enemy, const int i);

//�Փ˔���(�v���C���[�U���ƓG)
bool CollisionPAE(Player *player, Enemy *enemy);

//�Փ˔���(�v���C���[�Ɛ��_)
bool CollisionPN(Player *player, Nebula *nebula);

//�Փ˔���(�v���C���[�ƃI�u�W�F�N�g)
bool CollisionPO(Player *player, Object *object);

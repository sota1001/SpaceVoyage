#pragma once
#include "Player.h"
#include "Nebula.h"
#include "Enemy.h"
#include "Object.h"

//衝突判定(プレイヤーと敵)
//bool CollisionPE(Player *player, Enemy *enemy, const int i);

//衝突判定(プレイヤー攻撃と敵)
bool CollisionPAE(Player *player, Enemy *enemy);

//衝突判定(プレイヤーと星雲)
bool CollisionPN(Player *player, Nebula *nebula);

//衝突判定(プレイヤーとオブジェクト)
bool CollisionPO(Player *player, Object *object);

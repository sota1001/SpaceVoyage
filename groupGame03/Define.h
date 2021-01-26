#pragma once

const int WIN_WIDTH = 1080;
const int WIN_HEIGHT = 720;

//エミッター最大量
const int EMITTER_MAX = 1200;
//星の数
const int STAR_NUM = 100;

const float PI = 3.1415;

enum class SCENE {
	INIT,
	TITLE,
	GAME,
	GAMEOVER,
	CLEAR,
	ENDING
};
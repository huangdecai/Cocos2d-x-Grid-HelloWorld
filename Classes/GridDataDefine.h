
#pragma once
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN  
#endif
#define BUTTON_START        "sound/button_start.wav"
#define POP_STAR        "sound/pop_star.wav"
#define BUTTON_SELECT        "sound/select.wav"
#define GAME_OVER          "sound/gameover.wav"
#define BUTTON_ROTATION        "sound/rotation.ogg"
#define DOWN_BOTTOM          "sound/fastDown.ogg"
//portrait设置竖屏
const float INT_SCALE = 0.5;
const int GAME_PLAY_STATUS = 1;
const int GAME_FREE_STATUS = 0;
const int GAME_PAUSE_STATUS = 2;
const float REDUCE_INTERVAL_TIME = 0.8f;//游戏速度控制
//图片大小
namespace
{
	const int STAR_WIDTH = 67 * INT_SCALE;
	const int STAR_HEIGHT = 67 * INT_SCALE;
	const int window_width = 540;
	const int window_hight = 960;
	static int shouJiWidth = 0;
	static int shouJiHeight = 0;
	static float SHOU_JI_SCALE_X = 1.0;
	static float SHOU_JI_SCALE_Y = 1.0;
}
enum
{
	ROW_NUM = 24, // 行数
	COL_NUM = 10, // 列数

	REVERSE_NUM = 100, // 预留允许最大数
};
enum 
{
	//特效种类
	PARTICLE_EXPLOSION = 1,
	PARTICLE_FIRE ,
	PARTICLE_RING,
};
//方格定义
struct POINT_GRID
{
	int x;
	int y;
	bool bVisable;
};
//游戏记录数据
struct RECORD_GRID 
{
	int gameScore;
	int historyBestScore;
	int level;
	float speed;
};
struct STRUT_GRID
{

	POINT_GRID gridNum[4];
	STRUT_GRID(){ memset(gridNum, 0, sizeof(POINT_GRID) * 4); }
	int type;

};
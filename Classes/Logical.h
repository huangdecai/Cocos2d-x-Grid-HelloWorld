#pragma once
#include "cocos2d.h"
#include "Grid.h"
#include "GridDataDefine.h"
#include "StarParticle.h"
USING_NS_CC;
class GameMainLayer;
class CLogical
{
	//enum
	//{
	//	ROW_NUM = 15, // 行数
	//	COL_NUM = 10 // 列数
	//};
	//方格类型
	enum
	{
		V_YI_GRID = 0,
		H_YI_GRID,
		TIAN_ZI_GRID,
		ZHENG_QI_LEFT_GRID,
		ZHENG_QI_UP_GRID,
		ZHENG_QI_RIGHT_GRID,
		ZHENG_QI_DOWN_GRID,
		FAN_QI_LEFT_GRID,
		FAN_QI_UP_GRID,
		FAN_QI_RIGHT_GRID,
		FAN_QI_DOWN_GRID,
		ZHENG_ER_GRID,
		FAN_ER_GRID,
		KA_LEFT_GRID,
		KA_UP_GRID,
		KA_RIGHT_GRID,
		KA_DOWN_GRID,
		GRID_NUMS,
	};
public:

	~CLogical();
	//翻转方格
	void RollGrid();
	//左移格子
	void LeftMoveGrid();
	//右移格子
	void RightMoveGrid();
	//下称格子
	bool DownMoveGrid();
	//获得一个随机的方格
	void GetRandGrid(STRUT_GRID &grid);
	//是否隐藏一个方格
	void isVisableGrid(STRUT_GRID &grid, bool bVisable);
	//初始化方格
	void InitGrid(GameMainLayer* layer);
	//消除方格
	void DestroyGrid();
	//开始游戏
	void StartGame();
	//暂停游戏
	void PauseGame();
	//退出游戏
	void ExitGame();
	//游戏结束
	void GameOver();
	//动画检测
	bool AnimationDetection();
	//动画是否完成
	bool IsAnimationFinsh(){return m_bAnimationFinsh;}
	//设置动画
	void SetAnimationBool(bool bAnimation){m_bAnimationFinsh = bAnimation;}

	void onUpdate(float delta);
	//游戏得分
	int GetGameScore(){ return m_gameScore; }
	float GetGameSpeed(){ return m_speedChange; }
	static CLogical*GetInstance();
	//返回游戏数据
	POINT_GRID *GetGameData();
	//设置游戏速度加快
	void SetGameSpeedFast();
	//设置游戏记录速度
	void SetGarmeHistorySpeed(float speed);
	void SetGameScore(int score);
	//游戏检测
	bool GameDetection();
private:
	CLogical();
	//记录动画的当前方格
	//STRUT_GRID m_AnimationCurrentGrid;
	//记录当前的方格
	STRUT_GRID m_currentGrid;
	//记录下一个方格
	STRUT_GRID m_nextGrid;
	//所有的方格的精灵
	CGrid*			stars[ROW_NUM][COL_NUM];
    //下一个方格的精灵
	CGrid*          starsNext[4];
	//每一个方格的属性
	POINT_GRID      m_grid[ROW_NUM][COL_NUM];
	//方格消灭时使用
	POINT_GRID      m_CopyGrid[ROW_NUM][COL_NUM];
	//游戏主界面
	GameMainLayer*	gameLayer;
	//方格流动的时间
	float		elapsedTime;
	//方格速度变更
	float    m_speedChange;
	//游戏状态
	int gGameStatus;
	//游戏成绩
	float m_gameScore;
	//是否进行动画测试
	bool m_bStartAnimation;
	//中间消灭特殊控制变量
	bool m_bCenterDestoryGrid;
	static CLogical* pLogical;
	//特效类
	MyParticleIF *m_myExplosion;
	MyParticleIF *m_MyFire;
	MyParticleIF *m_MyRing;

	MyParticleIF *m_MyParticle;
    //动画是否完成
	bool m_bAnimationFinsh;
};


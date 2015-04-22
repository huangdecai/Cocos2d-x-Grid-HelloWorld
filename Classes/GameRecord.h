#pragma once
#include "cocos2d.h"
#include "GridDataDefine.h"
USING_NS_CC;
using namespace std;
class CGameRecord
{
public:
	
	~CGameRecord();

	void CreateRecordFile();
	//获取游戏记录
	void GetGameGridRecord(POINT_GRID *grid);
	//读取记录
	void SaveGameRecord(POINT_GRID *grid, int historyScore, int score, int level,float speed);
	//每一个方格的属性
	static CGameRecord*GetInstance();
	//获取历史分数
	int  GetHistoryScore();
	//获取游戏速度
	float GetGameSpeed();
	//获取游戏成绩
	int GetGameScore();
	//获取等级
	int GetGameLevel();
private:
	CGameRecord();
	static CGameRecord* m_pGameRecord;
	RECORD_GRID    m_recordGrid;
	POINT_GRID      m_grid[ROW_NUM][COL_NUM];
	CCUserDefault *m_pUserDefaul;

};


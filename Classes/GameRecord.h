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
	//��ȡ��Ϸ��¼
	void GetGameGridRecord(POINT_GRID *grid);
	//��ȡ��¼
	void SaveGameRecord(POINT_GRID *grid, int historyScore, int score, int level,float speed);
	//ÿһ�����������
	static CGameRecord*GetInstance();
	//��ȡ��ʷ����
	int  GetHistoryScore();
	//��ȡ��Ϸ�ٶ�
	float GetGameSpeed();
	//��ȡ��Ϸ�ɼ�
	int GetGameScore();
	//��ȡ�ȼ�
	int GetGameLevel();
private:
	CGameRecord();
	static CGameRecord* m_pGameRecord;
	RECORD_GRID    m_recordGrid;
	POINT_GRID      m_grid[ROW_NUM][COL_NUM];
	CCUserDefault *m_pUserDefaul;

};


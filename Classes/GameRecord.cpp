#include "GameRecord.h"
CGameRecord* CGameRecord::m_pGameRecord = 0;

CGameRecord::CGameRecord()
{
	m_pUserDefaul = CCUserDefault::sharedUserDefault();
	memset(&m_recordGrid, 0, sizeof(m_recordGrid));

}


CGameRecord::~CGameRecord()
{
	CC_SAFE_DELETE(m_pGameRecord);
	m_pGameRecord = NULL;
}




void CGameRecord::CreateRecordFile()
{

	

}


void CGameRecord::GetGameGridRecord(POINT_GRID *grid)
{
	
	char szData_b[32] = { 0 };
	int x = 0, y = 0;
	bool b = false;
	for (int row = 0; row < ROW_NUM; ++row)
	{
		for (int col = 0; col < COL_NUM; ++col)
		{
			snprintf(szData_b, 32, "bool:%d%d", row, col);
			b = m_pUserDefaul->getBoolForKey(szData_b);
			(*grid).bVisable = b;
			grid++;
		}
	}
	//获取历史分数
	 GetHistoryScore();
	//获取游戏速度
	 GetGameSpeed();
	//获取游戏成绩
     GetGameScore();
	//获取等级
	 GetGameLevel();

	
}


void CGameRecord::SaveGameRecord(POINT_GRID *grid, int historyScore, int score, int level, float speed)
{
	
	char szData_b[32] = { 0 };
	for (int row = 0; row < ROW_NUM; ++row)
	{
		for (int col = 0; col < COL_NUM; ++col)
		{
			snprintf(szData_b, 32, "bool:%d%d", row,col);
			m_pUserDefaul->setBoolForKey(szData_b, (*grid).bVisable);
			grid++;
		}
	}
	if (historyScore > m_recordGrid.historyBestScore)
	{
		snprintf(szData_b, 32, "historyScore");
		m_pUserDefaul->setIntegerForKey(szData_b, historyScore);
	}
	snprintf(szData_b, 32, "score");
	m_pUserDefaul->setIntegerForKey(szData_b,score );
	snprintf(szData_b, 32, "level");
	m_pUserDefaul->setIntegerForKey(szData_b, level);
	snprintf(szData_b, 32, "speed");
	m_pUserDefaul->setIntegerForKey(szData_b, speed);
	m_pUserDefaul->flush();
}
CGameRecord *CGameRecord::GetInstance()
{

	if (!m_pGameRecord)
	{
		m_pGameRecord = new CGameRecord();
	}
	return m_pGameRecord;

}
int  CGameRecord::GetHistoryScore()
{
	char szData_b[32] = { 0 };
	snprintf(szData_b, 32, "historyScore");
	m_recordGrid.historyBestScore = m_pUserDefaul->getIntegerForKey(szData_b);
	return m_recordGrid.historyBestScore;
}
float  CGameRecord::GetGameSpeed()
{
	char szData_b[32] = { 0 };
	snprintf(szData_b, 32, "speed");
	m_recordGrid.speed = m_pUserDefaul->getIntegerForKey(szData_b);
	return m_recordGrid.speed;
}
int  CGameRecord::GetGameScore()
{
	char szData_b[32] = { 0 };
	snprintf(szData_b, 32, "score");
	m_recordGrid.gameScore = m_pUserDefaul->getIntegerForKey(szData_b);
	return m_recordGrid.gameScore;
}

int CGameRecord::GetGameLevel()
{
	char szData_b[32] = { 0 };
	snprintf(szData_b, 32, "level");
	m_recordGrid.level = m_pUserDefaul->getIntegerForKey(szData_b);
	return m_recordGrid.level;
}



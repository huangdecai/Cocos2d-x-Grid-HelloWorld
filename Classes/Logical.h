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
	//	ROW_NUM = 15, // ����
	//	COL_NUM = 10 // ����
	//};
	//��������
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
	//��ת����
	void RollGrid();
	//���Ƹ���
	void LeftMoveGrid();
	//���Ƹ���
	void RightMoveGrid();
	//�³Ƹ���
	bool DownMoveGrid();
	//���һ������ķ���
	void GetRandGrid(STRUT_GRID &grid);
	//�Ƿ�����һ������
	void isVisableGrid(STRUT_GRID &grid, bool bVisable);
	//��ʼ������
	void InitGrid(GameMainLayer* layer);
	//��������
	void DestroyGrid();
	//��ʼ��Ϸ
	void StartGame();
	//��ͣ��Ϸ
	void PauseGame();
	//�˳���Ϸ
	void ExitGame();
	//��Ϸ����
	void GameOver();
	//�������
	bool AnimationDetection();
	//�����Ƿ����
	bool IsAnimationFinsh(){return m_bAnimationFinsh;}
	//���ö���
	void SetAnimationBool(bool bAnimation){m_bAnimationFinsh = bAnimation;}

	void onUpdate(float delta);
	//��Ϸ�÷�
	int GetGameScore(){ return m_gameScore; }
	float GetGameSpeed(){ return m_speedChange; }
	static CLogical*GetInstance();
	//������Ϸ����
	POINT_GRID *GetGameData();
	//������Ϸ�ٶȼӿ�
	void SetGameSpeedFast();
	//������Ϸ��¼�ٶ�
	void SetGarmeHistorySpeed(float speed);
	void SetGameScore(int score);
	//��Ϸ���
	bool GameDetection();
private:
	CLogical();
	//��¼�����ĵ�ǰ����
	//STRUT_GRID m_AnimationCurrentGrid;
	//��¼��ǰ�ķ���
	STRUT_GRID m_currentGrid;
	//��¼��һ������
	STRUT_GRID m_nextGrid;
	//���еķ���ľ���
	CGrid*			stars[ROW_NUM][COL_NUM];
    //��һ������ľ���
	CGrid*          starsNext[4];
	//ÿһ�����������
	POINT_GRID      m_grid[ROW_NUM][COL_NUM];
	//��������ʱʹ��
	POINT_GRID      m_CopyGrid[ROW_NUM][COL_NUM];
	//��Ϸ������
	GameMainLayer*	gameLayer;
	//����������ʱ��
	float		elapsedTime;
	//�����ٶȱ��
	float    m_speedChange;
	//��Ϸ״̬
	int gGameStatus;
	//��Ϸ�ɼ�
	float m_gameScore;
	//�Ƿ���ж�������
	bool m_bStartAnimation;
	//�м�����������Ʊ���
	bool m_bCenterDestoryGrid;
	static CLogical* pLogical;
	//��Ч��
	MyParticleIF *m_myExplosion;
	MyParticleIF *m_MyFire;
	MyParticleIF *m_MyRing;

	MyParticleIF *m_MyParticle;
    //�����Ƿ����
	bool m_bAnimationFinsh;
};


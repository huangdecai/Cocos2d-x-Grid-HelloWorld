#ifndef __GAME_LEVEL_H__
#define __GAME_LEVEL_H__

#include "cocos2d.h"
#include "Logical.h"
//#include "CCControlButton.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;

class GameMainLayer : public cocos2d::CCLayer
{
public:
	~GameMainLayer();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	//static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(GameMainLayer);

	void onTimeUp(float delta);
	void update(float delta);

	void RollGridCallback(CCObject* pSender);
	void StartGameCallBack(CCObject* pSender);
	void PauseGameCallBack(CCObject* pSender);
	void ExitGameCallBack(CCObject* pSender);
	void DrawGameScore();
    //保存游戏数据
	void SaveGameData();
	//触屏响应重写这三个方法
	
	void RunGameOverLabel();
	void LeftDowninsideaction(CCObject* sender, CCControlEvent);
	void LeftUpinsideaction(CCObject* sender, CCControlEvent);
	void RightDowninsideaction(CCObject* sender, CCControlEvent);
	void RightUpinsideaction(CCObject* sender, CCControlEvent);
	void DownDowninsideaction(CCObject* sender, CCControlEvent);
	void DownUpinsideaction(CCObject* sender, CCControlEvent);
	virtual void keyMenuVolumeDown();
	virtual void keyMenuVolumeUp();
	void SetGameScore(int score);
	void SetGameLevel(int level);
private:
	enum GUI_EVENT_TYPE
	{
		LEFT_MOVE,
		RIGHT_MOVE,
		DOWN_MOVE,
		BUTTON_FREE

	};
	GUI_EVENT_TYPE ButtonEvent;
	cocos2d::CCLabelTTF* labelLevel;
	cocos2d::CCLabelTTF* labelHistory;
	cocos2d::CCLabelTTF* labelGameScore;
	cocos2d::CCSprite* labelGameOver;
	float m_volume;
	int m_gameScore;
	int m_historyBestScore;
	int m_level;
	//CGridNode*  m_gridNode;
	CLogical  *m_logical;
	CCControlButton button;
	//按钮
	CCControlButton *m_pLeftButton;
	CCMenuItemImage *item2;
	CCControlButton *m_pRightButton;
	CCControlButton *m_pDownButton;
	CCMenuItemImage *item5;
	CCMenuItemImage *item6;
	CCMenuItemImage *item7;

	//方格移动的速度
	float		m_elapsedTime;
	bool        m_bPushButton;
};
#endif // __GAME_LEVEL_H__

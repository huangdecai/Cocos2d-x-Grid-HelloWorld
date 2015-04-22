#ifndef __START_LAYER_H__
#define __START_LAYER_H__

#include "cocos2d.h"
#include"GridDataDefine.h"
#include "GameRecord.h"
#include "Grid.h"
class GameMainLayer;
class StartLayer : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(StartLayer);
	//进入游戏
	void onEnterGameCallback(cocos2d::CCObject* obj);
	//继续游戏
	void onContinueGameCallback(cocos2d::CCObject* obj);
	// a selector callback
	void menuCloseCallback(CCObject* pSender);
	//游戏记录
	void SaveGameData();
	virtual void keyMenuVolumeDown();
	virtual void keyMenuVolumeUp();
	void InitAaimation();
private:
	float m_volume;
	CCMenuItemImage* item2;
	CCSprite* AnimationStars[5];
};

#endif // __START_LAYER_H__

#include "GameScene.h"
#include "GameMainLayer.h"
#include "StartLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;


CCScene* StartLayer::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	//StartLayer *layer = StartLayer::create();
	StartLayer *layer = StartLayer::create();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool StartLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	item2 = NULL;
	m_volume = 0.5f;
	CLogical::GetInstance();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	float scale = visibleSize.width/320.f;

	CCSprite* popStarBg = CCSprite::create("popstar_start.png");
	popStarBg->setPosition(ccp(visibleSize.width * INT_SCALE, visibleSize.height* INT_SCALE));
	popStarBg->setScaleX(1.0);
	popStarBg->setScaleY(1.0);
	this->addChild(popStarBg, 0);

	AnimationStars[0] = CCSprite::create("stars/tian.png");
	AnimationStars[1] = CCSprite::create("stars/fanqi.png");
	AnimationStars[2] = CCSprite::create("stars/ka.png");
	AnimationStars[3] = CCSprite::create("stars/zhengqi.png");
	AnimationStars[4] = CCSprite::create("stars/shu.png");
	for (int i = 0; i < 5; i++)
	{

		AnimationStars[i]->setPosition(ccp(origin.x + visibleSize.width/8  +i * 100, origin.y + visibleSize.height-80));
		AnimationStars[i]->setScaleX(0.5);
		AnimationStars[i]->setScaleY(0.5);
		this->addChild(AnimationStars[i], 1);

		CCPoint posGameOver = AnimationStars[i]->getPosition();
		CCActionInterval*  actionTo1 = CCMoveTo::create(2, ccp(posGameOver.x, posGameOver.y - visibleSize.height/2));
		actionTo1->setDuration(10.0f);
		CCRepeatForever* moveGameOver = CCRepeatForever::create(actionTo1);

		CCActionInterval*  actionTo2 = CCMoveTo::create(2, ccp(posGameOver.x, posGameOver.y + visibleSize.height));
		actionTo2->setDuration(10.0f);
		CCRepeatForever* moveGameOver2 = CCRepeatForever::create(actionTo1);
		//by强调旋转的相对角度，不论现在多少度都会旋转90度，以to和by结尾的动作类都是相同的道理
		CCRotateBy * rotateBy = CCRotateBy::create(2.0, 360);
		CCSequence * sequence = CCSequence::create(rotateBy, actionTo1, rotateBy, actionTo2, NULL);
		AnimationStars[i]->runAction(sequence);
	}
	
	CCMenuItemImage* item = CCMenuItemImage::create("buttons/default/btn_enterGameNormal.png",
		"buttons/default/btn_enterGamePush.png",this,menu_selector(StartLayer::onEnterGameCallback));
	item2 = CCMenuItemImage::create("buttons/default/btn_continueGameNormal.png",
		"buttons/default/btn_continueGamePush.png", this, menu_selector(StartLayer::onContinueGameCallback));
	item->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	item2->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 - item2->getContentSize().height));
	item->setScale(1.0, 1.0);
	item2->setScale(1.0, 1.0);
	CCMenu* menu = CCMenu::create(item,item2, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(StartLayer::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width / 2,
		origin.y + pCloseItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 2);
	CGameRecord::GetInstance()->GetHistoryScore();

	SimpleAudioEngine::sharedEngine()->preloadEffect(BUTTON_START);
	SimpleAudioEngine::sharedEngine()->preloadEffect(POP_STAR);
	SimpleAudioEngine::sharedEngine()->preloadEffect(BUTTON_SELECT);
	SimpleAudioEngine::sharedEngine()->preloadEffect(GAME_OVER);
	SimpleAudioEngine::sharedEngine()->preloadEffect(BUTTON_ROTATION);
	SimpleAudioEngine::sharedEngine()->preloadEffect(DOWN_BOTTOM);
	setKeypadEnabled(true);
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(m_volume);
	return true;
}
void StartLayer::keyMenuVolumeDown()
{
	if (m_volume>0.0f)
	{
		m_volume -= 0.1f;
	}
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(m_volume);
}
void StartLayer::keyMenuVolumeUp()
{
	if (m_volume <1.0f)
	{
		m_volume += 0.1f;
	}
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(m_volume);
}

void StartLayer::onEnterGameCallback(CCObject* obj)
{
	
	SimpleAudioEngine::sharedEngine()->playEffect(BUTTON_START);
	//SimpleAudioEngine::sharedEngine()->vibrate(500);
	changeLayer(this, GameMainLayer::create());
	
}
void StartLayer::onContinueGameCallback(CCObject* obj)
{
	//游戏记录读取
	GameMainLayer *gameLayer = GameMainLayer::create();
	
	SimpleAudioEngine::sharedEngine()->playEffect(BUTTON_START);
	CGameRecord::GetInstance()->GetGameGridRecord(CLogical::GetInstance()->GetGameData());
	CLogical::GetInstance()->SetGarmeHistorySpeed(CGameRecord::GetInstance()->GetGameSpeed());
	CLogical::GetInstance()->SetGameScore(CGameRecord::GetInstance()->GetGameScore());
	gameLayer->SetGameScore(CGameRecord::GetInstance()->GetGameScore());
	gameLayer->SetGameLevel(CGameRecord::GetInstance()->GetGameLevel());
	changeLayer(this, gameLayer);
	
}
void StartLayer::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}
void StartLayer::InitAaimation()
{
	
}


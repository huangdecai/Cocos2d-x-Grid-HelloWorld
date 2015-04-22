
#include "GameScene.h"
#include "GameMainLayer.h"
#include "StartLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
float Main_INT_SCREEN_POS_X;
float Main_INT_SCREEN_POS_Y;
const float BUTTON_INTERVAL_TIME = 0.8f;
GameMainLayer::~GameMainLayer()
{

}
// on "init" you need to initialize your instance
bool GameMainLayer::init()
{
	//////////////////////////////

	m_gameScore = 0;
	m_historyBestScore = 0;
	m_level = 1;
	m_elapsedTime = 0;
	m_bPushButton = false;
	labelGameOver = NULL;
	ButtonEvent = BUTTON_FREE;
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}
	m_logical = CLogical::GetInstance();
	m_logical->InitGrid(this);
	this->schedule(schedule_selector(GameMainLayer::onTimeUp), 4);
	this->schedule(schedule_selector(GameMainLayer::update));
	srand((unsigned)time(NULL));
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	Main_INT_SCREEN_POS_X = origin.x + visibleSize.width / 2 - (COL_NUM / 2) * STAR_WIDTH;
	Main_INT_SCREEN_POS_Y = origin.y + 3 * STAR_HEIGHT;

	CCSprite* pBackSprite = CCSprite::create("back.png");
	CCSprite* pNextGridSprite = CCSprite::create("nextText.png");
	CCSprite* pScoreSprite = CCSprite::create("score.png");
	pScoreSprite->setScaleY(0.8f);
	pBackSprite->setPosition(ccp(origin.x + 177, origin.y + 440 + 5 * STAR_HEIGHT));
	pScoreSprite->setPosition(ccp(visibleSize.width / 2 + origin.x + 185, origin.y + 760));
	pBackSprite->setScaleX(0.94f);
	pBackSprite->setScaleY(1.0);

	this->addChild(pBackSprite, 0);
	this->addChild(pScoreSprite, 0);
	//************************************************************************
	//游戏成绩
	char szData[32] = { 0 };
	snprintf(szData, 32, "S:%d", m_gameScore);
	labelGameScore = CCLabelTTF::create(szData, "Arial", 18);
	labelGameScore->setAnchorPoint(CCPointMake(0, 0.5f));
	labelGameScore->setPosition(ccp(Main_INT_SCREEN_POS_X + 280,
		Main_INT_SCREEN_POS_Y + 290 + 370));
	this->addChild(labelGameScore, 1);

	m_historyBestScore = CGameRecord::GetInstance()->GetHistoryScore();
		snprintf(szData, 32, "HS:%d", m_historyBestScore);
	labelHistory = CCLabelTTF::create(szData, "Arial", 18);
	labelHistory->setAnchorPoint(CCPointMake(0, 0.5f));
	labelHistory->setPosition(ccp(Main_INT_SCREEN_POS_X + 280,
		Main_INT_SCREEN_POS_Y + 380 + 340));
	this->addChild(labelHistory, 1);

	snprintf(szData, 32, "L:%d", m_level);
	labelLevel = CCLabelTTF::create(szData, "Arial", 18);
	labelLevel->setAnchorPoint(CCPointMake(0, 0.5f));
	labelLevel->setPosition(ccp(Main_INT_SCREEN_POS_X + 280,
		Main_INT_SCREEN_POS_Y + 270 + 320));
	this->addChild(labelLevel, 1);


	//************************************************************************
	//按钮创建
	CCScale9Sprite *sprite1 = CCScale9Sprite::create("btn_backNormal.png");
	CCScale9Sprite *sprite2 = CCScale9Sprite::create("btn_backPush.png");
	m_pLeftButton = CCControlButton::create(sprite1);

	CCScale9Sprite *sprite3 = CCScale9Sprite::create("btn_rightNoral.png");
	CCScale9Sprite *sprite4 = CCScale9Sprite::create("btn_rightPush.png");
	m_pRightButton = CCControlButton::create(sprite3);

	CCScale9Sprite *sprite5 = CCScale9Sprite::create("bt_downNormal.png");
	CCScale9Sprite *sprite6 = CCScale9Sprite::create("bt_downPush.png");
	m_pDownButton = CCControlButton::create(sprite5);

	m_pLeftButton->setPreferredSize(CCSizeMake(180, 90));
	m_pRightButton->setPreferredSize(CCSizeMake(180, 90));
	m_pDownButton->setPreferredSize(CCSizeMake(100, 150));
	
	m_pLeftButton->setBackgroundSpriteForState(sprite2, CCControlStateHighlighted);
	m_pRightButton->setBackgroundSpriteForState(sprite4, CCControlStateHighlighted);
	m_pDownButton->setBackgroundSpriteForState(sprite6, CCControlStateHighlighted);

	m_pLeftButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameMainLayer::LeftDowninsideaction), CCControlEventTouchDown);
	m_pRightButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameMainLayer::RightDowninsideaction), CCControlEventTouchDown);
	m_pDownButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameMainLayer::DownDowninsideaction), CCControlEventTouchDown);

	m_pLeftButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameMainLayer::LeftUpinsideaction), CCControlEventTouchUpInside);
	m_pRightButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameMainLayer::RightUpinsideaction), CCControlEventTouchUpInside);
	m_pDownButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameMainLayer::DownUpinsideaction), CCControlEventTouchUpInside);
	this->addChild(m_pLeftButton);
	this->addChild(m_pRightButton);
	this->addChild(m_pDownButton);
	//item1 = CCMenuItemImage::create("btn_backNormal.png", "btn_backPush.png", this, menu_selector(GameMainLayer::LeftGridCallback));
	item2 = CCMenuItemImage::create("btn_rollNomal.png", "btn_rollPush.png", this, menu_selector(GameMainLayer::RollGridCallback));
	item5 = CCMenuItemImage::create("btn_startNormal.png", "btn_StartPush.png", this, menu_selector(GameMainLayer::StartGameCallBack));
	item6 = CCMenuItemImage::create("btn_pauseNormal.png", "btn_pausePush.png", this, menu_selector(GameMainLayer::PauseGameCallBack));
	item7 = CCMenuItemImage::create("btn_exitNormal.png", "btn_exitPush.png", this, menu_selector(GameMainLayer::ExitGameCallBack));

	origin.x += 20;
	CCMenu *menu = CCMenu::create( item2, item5, item6, item7, NULL);

	menu->setPosition(CCPointZero);
	m_pLeftButton->setPosition(ccp(origin.x + 70,
		origin.y + 140 + m_pLeftButton->getContentSize().height / 2));
	item2->setPosition(ccp(origin.x + visibleSize.width / 2 + 150,
		origin.y + 30 + item2->getContentSize().height / 2));
	m_pRightButton->setPosition(ccp(origin.x + 250,
		origin.y + 140 + m_pRightButton->getContentSize().height / 2));
	m_pDownButton->setPosition(ccp(origin.x + 160,
		origin.y + m_pDownButton->getContentSize().height / 2));
	item5->setPosition(ccp(origin.x + visibleSize.width / 2 + item2->getContentSize().width - m_pDownButton->getContentSize().width / 2,
		origin.y + 360 + item5->getContentSize().height));
	item6->setPosition(ccp(origin.x + visibleSize.width / 2 + item2->getContentSize().width - m_pDownButton->getContentSize().width / 2,
		origin.y + 280 + item5->getContentSize().height));
	item7->setPosition(ccp(origin.x + visibleSize.width / 2 + item2->getContentSize().width - m_pDownButton->getContentSize().width / 2,
		origin.y + 200 + item5->getContentSize().height));
	pNextGridSprite->setPosition(ccp(origin.x + visibleSize.width / 2 + item2->getContentSize().width - m_pDownButton->getContentSize().width / 2,
		origin.y + 580 + item5->getContentSize().height));
	addChild(menu, 1);
	this->addChild(pNextGridSprite, 0);
	//设置音量
	setKeypadEnabled(true);
	m_volume = SimpleAudioEngine::sharedEngine()->getEffectsVolume();
	return true;
}
void GameMainLayer::RunGameOverLabel()
{
	 
	labelGameOver = CCSprite::create("GameOverLabel.png");
	//labelGameOver->setAnchorPoint(CCPointMake(0, 0.5f));
	labelGameOver->setPosition(ccp(Main_INT_SCREEN_POS_X +80,
		Main_INT_SCREEN_POS_Y + 800));
	this->addChild(labelGameOver, 1);

	CCPoint posGameOver = labelGameOver->getPosition();
	CCMoveTo* moveGameOver = CCMoveTo::create(2, ccp(posGameOver.x, posGameOver.y - 450));
	labelGameOver->runAction(moveGameOver);
}
void GameMainLayer::onTimeUp(float delta)
{

}

void  GameMainLayer::DrawGameScore()
{

	char szData[32] = { 0 };
	m_gameScore = m_logical->GetGameScore();
		snprintf(szData, 32, "S:%d", m_gameScore);

	labelGameScore->setString(szData);
	if (m_gameScore/4000>(m_level-1))
	{
		m_level++;
		m_logical->SetGameSpeedFast();
	}
	if (m_gameScore > m_historyBestScore)
	{
		m_historyBestScore = m_gameScore;
	}
	snprintf(szData, 32, "L:%d", m_level);
	labelLevel->setString(szData);



}
void GameMainLayer::update(float delta)
{
	if (m_bPushButton)
	{
		m_elapsedTime += delta;
		if (m_elapsedTime >= BUTTON_INTERVAL_TIME - 0.6)
		{
			switch (ButtonEvent)
			{
			case GameMainLayer::LEFT_MOVE:
				m_logical->LeftMoveGrid();
				m_elapsedTime -= BUTTON_INTERVAL_TIME - 0.7;
				//m_elapsedTime = 0;
				break;
			case GameMainLayer::RIGHT_MOVE:
				m_logical->RightMoveGrid();
				m_elapsedTime -= BUTTON_INTERVAL_TIME - 0.7;
				//m_elapsedTime = 0;
				break;
			case GameMainLayer::DOWN_MOVE:
				m_elapsedTime -= BUTTON_INTERVAL_TIME - 0.8;
				if (m_logical->DownMoveGrid())
				{
						m_elapsedTime = 0;
						m_bPushButton = false;
						
				}
				break;
			default:
				break;
			}
			if (m_elapsedTime > 0.5f)
				m_elapsedTime = 0;
			
		}
	}

	m_logical->onUpdate(delta);
	DrawGameScore();
}
void GameMainLayer::RollGridCallback(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect(BUTTON_ROTATION);
	m_logical->RollGrid();
}


void GameMainLayer::StartGameCallBack(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect(BUTTON_SELECT);
	if (labelGameOver != NULL)
	{
		CCPoint posGameOver = labelGameOver->getPosition();
		CCMoveTo* moveGameOver = CCMoveTo::create(2, ccp(posGameOver.x, posGameOver.y - 600));
		labelGameOver->runAction(moveGameOver);
	}
	m_logical->StartGame();
	
}
void GameMainLayer::PauseGameCallBack(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect(BUTTON_SELECT);
	m_logical->PauseGame();
}
void GameMainLayer::ExitGameCallBack(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect(BUTTON_SELECT);
	m_logical->ExitGame();
	SaveGameData();
	changeLayer(this, StartLayer::create());
}

void GameMainLayer::SaveGameData()
{
	
	CGameRecord::GetInstance()->SaveGameRecord(m_logical->GetGameData(), m_historyBestScore, m_gameScore, m_level, m_logical->GetGameSpeed());
}


void GameMainLayer::LeftUpinsideaction(CCObject* sender, CCControlEvent)
{
	m_bPushButton = false;

}
void GameMainLayer::LeftDowninsideaction(CCObject* sender, CCControlEvent)
{
	SimpleAudioEngine::sharedEngine()->playEffect(BUTTON_SELECT);
	m_logical->LeftMoveGrid();
	m_bPushButton = true;
	ButtonEvent = LEFT_MOVE; m_elapsedTime = 0;
}
void GameMainLayer::RightUpinsideaction(CCObject* sender, CCControlEvent)
{
	m_bPushButton = false;
}
void GameMainLayer::RightDowninsideaction(CCObject* sender, CCControlEvent)
{
	SimpleAudioEngine::sharedEngine()->playEffect(BUTTON_SELECT);
	m_logical->RightMoveGrid();
	m_bPushButton = true;
	ButtonEvent = RIGHT_MOVE; m_elapsedTime = 0;
}
void GameMainLayer::DownUpinsideaction(CCObject* sender, CCControlEvent)
{
	m_bPushButton = false;
}
void GameMainLayer::DownDowninsideaction(CCObject* sender, CCControlEvent)
{
	SimpleAudioEngine::sharedEngine()->playEffect(BUTTON_SELECT);
	m_logical->DownMoveGrid();
	m_bPushButton = true;
	ButtonEvent = DOWN_MOVE; m_elapsedTime = 0;
}
void GameMainLayer::keyMenuVolumeDown()
{
	if (m_volume > 0.0f)
	{
		m_volume -= 0.1f;
	}

	SimpleAudioEngine::sharedEngine()->setEffectsVolume(m_volume);
}
void GameMainLayer::keyMenuVolumeUp()
{
	if (m_volume < 1.0f)
	{
		m_volume += 0.1f;
	}
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(m_volume);
}
void GameMainLayer::SetGameScore(int score)
{
	m_gameScore = score;

}
void GameMainLayer::SetGameLevel(int level)
{
	m_level = level;
}
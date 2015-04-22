#pragma once
#include "cocos2d.h"
USING_NS_CC;
class CGrid :
	public cocos2d::CCSprite
{
public:
	CGrid();
	~CGrid();

	virtual bool init();
	static CGrid* create();
	void onUpdate(float delta);
	void setPos(const cocos2d::CCPoint& pos);
	void draw(void);
private:
	
};


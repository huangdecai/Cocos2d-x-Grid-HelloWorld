#include "StarParticle.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
const float ONE_CLEAR_TIME = 0.05f;
CMyParticleExplosion::CMyParticleExplosion()
{
	m_clearSumTime = 0.0f;
	m_row = 0;
	m_GridNum = 0;
	for (int row = 0; row < 4; ++row)
	{
		
		for (int col = 0; col < COL_NUM; ++col)
		{
		starsParticle[row][col] = NULL;
		}
	}
	for (int i = 0; i < 4 * COL_NUM; i++)
	{
		effect[i] = CCParticleExplosion::create();
		//effect->retain();
		effect[i]->setTexture(CCTextureCache::sharedTextureCache()->addImage("stars/red.png"));
	}
}
void CMyParticleExplosion::showStarParticleEffect(int color, CCPoint position, CCNode* node){
	

	static int num = 0;

	num++;
	if (num == 4 * COL_NUM)
	{
		num = 0;
	}
	effect[num]->setTotalParticles(20);
	effect[num]->setStartColor(ccColor4F{ 240 / 255.0f, 99 / 255.0f, 108 / 255.0f, 1 });
	effect[num]->setStartColorVar(ccColor4F{ 0, 0, 0, 1 });
	effect[num]->setEndColor(ccColor4F{ 253 / 255.0f, 143 / 255.0f, 150 / 255.0f, 1 });
	effect[num]->setEndColorVar(ccColor4F{ 0, 0, 0, 1 });
	effect[num]->setStartSize(7.0f);
	effect[num]->setGravity(CCPoint(0, -100));
	effect[num]->setLife(4.0f);
	effect[num]->setSpeed(200);
	effect[num]->setSpeedVar(10);
	effect[num]->setPosition(position);
	node->addChild(effect[num]);
}

ccColor4F CMyParticleExplosion::getColor4F(int color){
	return ccColor4F{ 240 / 255.0f, 99/ 255.0f, 108 / 255.0f, 1 };

}
void CMyParticleExplosion::GetGrid(CGrid* grid, POINT_GRID *PointGrid, int count)
{
	m_PointGrid[m_row][count] = PointGrid;
	 starsParticle[m_row][count] = grid;
	 m_GridNum++;
	 if (count==COL_NUM-1)
	 {
		 m_row++;
		 if (m_row==4)
		 {
			 m_row = 0;
		 }
	 }

}
bool CMyParticleExplosion::clearMatrixOneByOne(float delta, CCNode* node)
{
	
	m_clearSumTime += delta;
	if (m_clearSumTime >= ONE_CLEAR_TIME)
	{
		m_clearSumTime -= ONE_CLEAR_TIME;
		for (int row = 0; row < 4; ++row)
		{
		
			for (int col = 0; col < COL_NUM; ++col)
			{
				if(starsParticle[row][col] == NULL)
					continue;
				SimpleAudioEngine::sharedEngine()->playEffect(POP_STAR);
				showStarParticleEffect(1, starsParticle[row][col]->getPosition(), node);
				starsParticle[row][col]->setVisible(false);
				starsParticle[row][col]->onUpdate(delta);
				starsParticle[row][col] = NULL;
				m_PointGrid[row][col]->bVisable = false;
				m_GridNum--;
				return false;
			}
		}
	}
	if (m_GridNum==0)
	{
		return true;
	}
	return false;
}

//火焰系统

CMyParticleFire::CMyParticleFire()
{
	m_clearSumTime = 0.0f;
	m_row = 0;
	m_GridNum = 0;
	for (int row = 0; row < 4; ++row)
	{

		for (int col = 0; col < COL_NUM; ++col)
		{
			starsParticle[row][col] = NULL;
		}
	}

	for (int i = 0; i < 4 * COL_NUM; i++)
	{

		
	}
}
void CMyParticleFire::showStarParticleEffect(int color, CCPoint position, CCNode* node){
	
	CCParticleSystem *effect = CCParticleSun::create();
	//effect->retain();
	effect->setTexture(CCTextureCache::sharedTextureCache()->addImage("stars/fire.png"));
	effect->setStartSize(10.0f);
	effect->setLife(4.0f);
	effect->setDuration(1.0f);
	effect->setPosition(position);
	effect->setAutoRemoveOnFinish(true);

	node->addChild(effect);
}

ccColor4F CMyParticleFire::getColor4F(int color){
	return ccColor4F{ 240 / 255.0f, 99 / 255.0f, 108 / 255.0f, 1 };

}
void CMyParticleFire::GetGrid(CGrid* grid, POINT_GRID *PointGrid, int count)
{
	m_PointGrid[m_row][count] = PointGrid;
	starsParticle[m_row][count] = grid;
	m_GridNum++;
	if (count == COL_NUM - 1)
	{
		m_row++;
		if (m_row == 4)
		{
			m_row = 0;
		}
	}

}
bool CMyParticleFire::clearMatrixOneByOne(float delta, CCNode* node)
{

	m_clearSumTime += delta;
	if (m_clearSumTime >= ONE_CLEAR_TIME)
	{
		m_clearSumTime -= ONE_CLEAR_TIME;
		for (int row = 0; row < 4; ++row)
		{

			for (int col = 0; col < COL_NUM; ++col)
			{
				if (starsParticle[row][col] == NULL)
					continue;
				SimpleAudioEngine::sharedEngine()->playEffect(POP_STAR);
				showStarParticleEffect(1, starsParticle[row][col]->getPosition(), node);
				starsParticle[row][col]->setVisible(false);
				starsParticle[row][col]->onUpdate(delta);
				starsParticle[row][col] = NULL;
				m_PointGrid[row][col]->bVisable = false;
				m_GridNum--;
				return false;
			}
		}
	}
	if (m_GridNum == 0)
	{
		return true;
	}
	return false;
}

//ring系统
CMyParticleRing::CMyParticleRing()
{
	m_clearSumTime = 0.0f;
	m_row = 0;
	m_GridNum = 0;
	for (int row = 0; row < 4; ++row)
	{

		for (int col = 0; col < COL_NUM; ++col)
		{
			starsParticle[row][col] = NULL;
		}
	}
	for (int i = 0; i < 4 * COL_NUM; i++)
	{
		
		effect[i] = CCParticleSystemQuad::create();
		effect[i]->setTexture(CCTextureCache::sharedTextureCache()->addImage("stars/red.png"));
	
		effect[i]->setStartColor(ccColor4F{ 240 / 255.0f, 99 / 255.0f, 108 / 255.0f, 1 });
		effect[i]->setStartColorVar(ccColor4F{ 0, 0, 0, 1 });
		effect[i]->setEndColor(ccColor4F{ 253 / 255.0f, 143 / 255.0f, 150 / 255.0f, 1 });
		effect[i]->setEndColorVar(ccColor4F{ 0, 0, 0, 1 });
		
	}
}
void CMyParticleRing::showStarParticleEffect(int color, CCPoint position, CCNode* node){
	static int num = 0;
	
	num++;
	if (num==4*COL_NUM)
	{
		num = 0;
	}
	effect[num]->setStartSize(40.0f);
	effect[num]->setTotalParticles(15);
	effect[num]->setLife(4.0f);
	effect[num]->setDuration(2.0f);

	effect[num]->setLifeVar(0);
	effect[num]->setSpeed(100);
	effect[num]->setSpeedVar(0);


	effect[num]->setStartSpin(10);
	effect[num]->setStartSpinVar(0);
	effect[num]->setEndSpin(1500);
	effect[num]->setEndSpinVar(0);
	effect[num]->setPosition(position);
	effect[num]->setEmissionRate(10000);
	node->addChild(effect[num]);
}

ccColor4F CMyParticleRing::getColor4F(int color){
	return ccColor4F{ 240 / 255.0f, 99 / 255.0f, 108 / 255.0f, 1 };

}
void CMyParticleRing::GetGrid(CGrid* grid, POINT_GRID *PointGrid, int count)
{
	m_PointGrid[m_row][count] = PointGrid;
	starsParticle[m_row][count] = grid;
	m_GridNum++;
	if (count == COL_NUM - 1)
	{
		m_row++;
		if (m_row == 4)
		{
			m_row = 0;
		}
	}

}
bool CMyParticleRing::clearMatrixOneByOne(float delta, CCNode* node)
{

	m_clearSumTime += delta;
	if (m_clearSumTime >= ONE_CLEAR_TIME)
	{
		m_clearSumTime -= ONE_CLEAR_TIME;
		for (int row = 0; row < 4; ++row)
		{

			for (int col = 0; col < COL_NUM; ++col)
			{
				if (starsParticle[row][col] == NULL)
					continue;
				SimpleAudioEngine::sharedEngine()->playEffect(POP_STAR);
				showStarParticleEffect(1, starsParticle[row][col]->getPosition(), node);
				starsParticle[row][col]->setVisible(false);
				starsParticle[row][col]->onUpdate(delta);
				starsParticle[row][col] = NULL;
				m_PointGrid[row][col]->bVisable = false;
				m_GridNum--;
				return false;
			}
		}
	}
	if (m_GridNum == 0)
	{
		return true;
	}
	return false;
}


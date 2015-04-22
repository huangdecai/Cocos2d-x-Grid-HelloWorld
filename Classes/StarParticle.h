#ifndef _STAR_PARTICLE_H_
#define _STAR_PARTICLE_H_
#include "cocos2d.h"
#include "GridDataDefine.h"
#include "Grid.h"
USING_NS_CC;
class MyParticleIF
{
public:
	virtual void showStarParticleEffect(int color, CCPoint position, CCNode* node)=0;
	virtual ccColor4F getColor4F(int color) = 0;
	virtual bool clearMatrixOneByOne(float delta, CCNode* node) = 0;
	virtual void GetGrid(CGrid* grid, POINT_GRID *PointGrid, int count) = 0;
};
class CMyParticleExplosion : public MyParticleIF
{
public:
	CMyParticleExplosion();
	void showStarParticleEffect(int color, CCPoint position, CCNode* node);
	ccColor4F getColor4F(int color);
	bool clearMatrixOneByOne(float delta, CCNode* node);
	void GetGrid(CGrid* grid, POINT_GRID *PointGrid, int count);
private:
	CCParticleSystem* effect[4 * COL_NUM];
	CGrid*			starsParticle[4][COL_NUM];
	POINT_GRID       *m_PointGrid[4][COL_NUM];
	float m_clearSumTime;
	int m_row;
	int m_GridNum;
};

class CMyParticleFire : public MyParticleIF
{
public:
	CMyParticleFire();
	void showStarParticleEffect(int color, CCPoint position, CCNode* node);
	ccColor4F getColor4F(int color);
	bool clearMatrixOneByOne(float delta, CCNode* node);
	void GetGrid(CGrid* grid, POINT_GRID *PointGrid, int count);
private:
	//CCParticleSystem* effect[4 * COL_NUM];
	CGrid*			starsParticle[4][COL_NUM];
	POINT_GRID       *m_PointGrid[4][COL_NUM];
	float m_clearSumTime;
	int m_row;
	int m_GridNum;
};

class CMyParticleRing : public MyParticleIF
{
public:
	CMyParticleRing();
	void showStarParticleEffect(int color, CCPoint position, CCNode* node);
	ccColor4F getColor4F(int color);
	bool clearMatrixOneByOne(float delta, CCNode* node);
	void GetGrid(CGrid* grid, POINT_GRID *PointGrid, int count);
private:
	CCParticleSystem* effect[4 * COL_NUM];
	CGrid*			starsParticle[4][COL_NUM];
	POINT_GRID       *m_PointGrid[4][COL_NUM];
	float m_clearSumTime;
	int m_row;
	int m_GridNum;

};
#endif

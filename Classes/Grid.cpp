#include "Grid.h"
CGrid::CGrid()
{
	init();
}


CGrid::~CGrid()
{
}
bool CGrid::init()
{
	if (!CCSprite::init())
	{
		return false;
	}

	return true;
}
CGrid* CGrid::create()
{
	CGrid* pRet = new CGrid;
	const static std::string path("stars/red.png");
	bool bfilePath=pRet->initWithFile(path.c_str());
	if (pRet &&bfilePath)
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}
void CGrid::setPos(const cocos2d::CCPoint& pos)
{
	CCSprite::setPosition(pos);

	
}
void CGrid::draw(void)
{
	CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");

	CCAssert(!m_pobBatchNode, "If CCSprite is being rendered by CCSpriteBatchNode, CCSprite#draw SHOULD NOT be called");

	CC_NODE_DRAW_SETUP();

	//if (true)
	//{
	//	ccGLBlendFunc(GL_SRC_COLOR, GL_ONE);
	//}
	//else
	{
		ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);
	}


	ccGLBindTexture2D(m_pobTexture->getName());
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);



#define kQuadSize sizeof(m_sQuad.bl)
#ifdef EMSCRIPTEN
	long offset = 0;
	setGLBufferData(&m_sQuad, 4 * kQuadSize, 0);
#else
	long offset = (long)&m_sQuad;
#endif // EMSCRIPTEN

	// vertex
	int diff = offsetof(ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// texCoods
	diff = offsetof(ccV3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// color
	diff = offsetof(ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));


	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	CHECK_GL_ERROR_DEBUG();


#if CC_SPRITE_DEBUG_DRAW == 1
	// draw bounding box
	CCPoint vertices[4] = {
		ccp(m_sQuad.tl.vertices.x, m_sQuad.tl.vertices.y),
		ccp(m_sQuad.bl.vertices.x, m_sQuad.bl.vertices.y),
		ccp(m_sQuad.br.vertices.x, m_sQuad.br.vertices.y),
		ccp(m_sQuad.tr.vertices.x, m_sQuad.tr.vertices.y),
	};
	ccDrawPoly(vertices, 4, true);
#elif CC_SPRITE_DEBUG_DRAW == 2
	// draw texture box
	CCSize s = this->getTextureRect().size;
	CCPoint offsetPix = this->getOffsetPosition();
	CCPoint vertices[4] = {
		ccp(offsetPix.x, offsetPix.y), ccp(offsetPix.x + s.width, offsetPix.y),
		ccp(offsetPix.x + s.width, offsetPix.y + s.height), ccp(offsetPix.x, offsetPix.y + s.height)
	};
	ccDrawPoly(vertices, 4, true);
#endif // CC_SPRITE_DEBUG_DRAW



	CC_INCREMENT_GL_DRAWS(1);

	CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
}

void CGrid::onUpdate(float delta)
{
	

	//setPosition(ccp(tempPosX, tempPosY));

}
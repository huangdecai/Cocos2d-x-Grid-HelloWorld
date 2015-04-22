#include "Logical.h"
#include "GameMainLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
//#include "GridDataDefine.h"
float INT_SCREEN_POS_X;
float INT_SCREEN_POS_Y;

CLogical* CLogical::pLogical = 0;
CLogical::CLogical()
{   

	m_myExplosion = new CMyParticleExplosion;
	m_MyFire = new CMyParticleFire;
	m_MyRing = new CMyParticleRing;

	m_MyParticle = m_myExplosion;
}


CLogical::~CLogical()
{
	CC_SAFE_DELETE(m_myExplosion);
	CC_SAFE_DELETE(m_MyFire);
	CC_SAFE_DELETE(m_MyRing);
	CC_SAFE_DELETE(pLogical);
	pLogical = NULL;
	for (int row = 0; row < ROW_NUM; ++row)
	{
		for (int col = 0; col < COL_NUM; ++col)
		{
			CGrid* star = stars[row][col];
			if (stars[row][col])
			{
				gameLayer->removeChild(stars[row][col]);
				stars[row][col] = NULL;
			}
		}
	}
	gameLayer = NULL;
}
//翻转格子
void CLogical::RollGrid()
{
	if ((gGameStatus != GAME_PLAY_STATUS) || (m_bStartAnimation != false))
	{
		return;
	}
	isVisableGrid(m_currentGrid, false);
	STRUT_GRID tempCurrentGrid = m_currentGrid;
	switch (m_currentGrid.type)
	{
	case 	V_YI_GRID:
	{
		//由竖转为横
	    
		if (m_currentGrid.gridNum[0].y > 7)
			{
			int temp = m_currentGrid.gridNum[0].y - 7;
				for (int i = 0; i < 4; i++)
				{
					m_currentGrid.gridNum[i].y -= temp;
				}
			}
		if (m_currentGrid.gridNum[0].y == 0)
		    {
			for (int i = 0; i < 4; i++)
			{
				m_currentGrid.gridNum[i].y += 1;
			}
			
		   }
		if (m_grid[m_currentGrid.gridNum[3].x][m_currentGrid.gridNum[3].y - 1].bVisable == false &&
			m_grid[m_currentGrid.gridNum[3].x][m_currentGrid.gridNum[3].y + 1].bVisable == false &&
			m_grid[m_currentGrid.gridNum[3].x][m_currentGrid.gridNum[3].y + 2].bVisable == false
			)
		{
	     m_currentGrid.gridNum[0].x = m_currentGrid.gridNum[3].x; m_currentGrid.gridNum[0].y = m_currentGrid.gridNum[3].y-1;
		 m_currentGrid.gridNum[1].x = m_currentGrid.gridNum[0].x; m_currentGrid.gridNum[1].y = m_currentGrid.gridNum[0].y+1;
		 m_currentGrid.gridNum[2].x = m_currentGrid.gridNum[0].x;  m_currentGrid.gridNum[2].y = m_currentGrid.gridNum[0].y+2;
		 m_currentGrid.gridNum[3].y = m_currentGrid.gridNum[0].y + 3;
		 m_currentGrid.type = H_YI_GRID;
		}
		else
		{
			m_currentGrid = tempCurrentGrid;
		}
	
		break;
	}
		
	case H_YI_GRID:
	{
		//由横转为竖

		if (m_grid[m_currentGrid.gridNum[1].x + 1][m_currentGrid.gridNum[1].y].bVisable == false &&
			m_grid[m_currentGrid.gridNum[1].x + 2][m_currentGrid.gridNum[1].y].bVisable == false &&
			m_grid[m_currentGrid.gridNum[1].x + 3][m_currentGrid.gridNum[1].y].bVisable == false
			)
		{
			m_currentGrid.gridNum[0].x = m_currentGrid.gridNum[1].x+3; m_currentGrid.gridNum[0].y = m_currentGrid.gridNum[1].y;
			m_currentGrid.gridNum[1].x = m_currentGrid.gridNum[0].x- 1; m_currentGrid.gridNum[1].y = m_currentGrid.gridNum[0].y;
			m_currentGrid.gridNum[2].x = m_currentGrid.gridNum[0].x- 2;  m_currentGrid.gridNum[2].y = m_currentGrid.gridNum[0].y;
			m_currentGrid.gridNum[3].x = m_currentGrid.gridNum[0].x - 3; m_currentGrid.gridNum[3].y = m_currentGrid.gridNum[0].y;
			m_currentGrid.type = V_YI_GRID;

		}
	break;	
	}
		
	case TIAN_ZI_GRID:
	{
		break;
	}
		
	case ZHENG_QI_LEFT_GRID:
	{
		//由左转上
	  
		if (m_currentGrid.gridNum[1].y == 9)
		{
			for (int i = 0; i < 4; i++)
			{
				m_currentGrid.gridNum[i].y --;
			}
		}
		if (m_grid[m_currentGrid.gridNum[3].x ][m_currentGrid.gridNum[3].y-1].bVisable == false &&
			m_grid[m_currentGrid.gridNum[3].x][m_currentGrid.gridNum[3].y+1].bVisable == false &&
			m_grid[m_currentGrid.gridNum[3].x+1][m_currentGrid.gridNum[3].y+1].bVisable == false
			)
		{
			m_currentGrid.gridNum[0].x = m_currentGrid.gridNum[3].x; m_currentGrid.gridNum[0].y = m_currentGrid.gridNum[3].y-1;
			m_currentGrid.gridNum[1].x = m_currentGrid.gridNum[0].x; m_currentGrid.gridNum[1].y = m_currentGrid.gridNum[0].y+1;
			m_currentGrid.gridNum[2].x = m_currentGrid.gridNum[0].x;  m_currentGrid.gridNum[2].y = m_currentGrid.gridNum[0].y+2;
			m_currentGrid.gridNum[3].x = m_currentGrid.gridNum[0].x+1; m_currentGrid.gridNum[3].y = m_currentGrid.gridNum[0].y+2;
			m_currentGrid.type = ZHENG_QI_UP_GRID;
		}
		else
		{
			m_currentGrid = tempCurrentGrid;
		}
	
	}
		break;
	case ZHENG_QI_UP_GRID:
	{
		//由上转右

		if (m_grid[m_currentGrid.gridNum[0].x+1][m_currentGrid.gridNum[0].y ].bVisable == false &&
			m_grid[m_currentGrid.gridNum[0].x+2][m_currentGrid.gridNum[0].y ].bVisable == false 
			)
		{
			m_currentGrid.gridNum[0].x = m_currentGrid.gridNum[0].x+2; m_currentGrid.gridNum[0].y = m_currentGrid.gridNum[0].y;
			m_currentGrid.gridNum[1].x = m_currentGrid.gridNum[0].x-1; m_currentGrid.gridNum[1].y = m_currentGrid.gridNum[0].y ;
			m_currentGrid.gridNum[2].x = m_currentGrid.gridNum[0].x-2;  m_currentGrid.gridNum[2].y = m_currentGrid.gridNum[0].y;
			m_currentGrid.gridNum[3].x = m_currentGrid.gridNum[0].x-2; m_currentGrid.gridNum[3].y = m_currentGrid.gridNum[0].y +1;
			m_currentGrid.type = ZHENG_QI_RIGHT_GRID;
		}
	
		break;
	}
	case ZHENG_QI_RIGHT_GRID:
			{
		if (m_currentGrid.gridNum[3].y == 9)
		{
			for (int i = 0; i < 4; i++)
			{
				m_currentGrid.gridNum[i].y--;
			}
		}
	//由右转下
		if (m_grid[m_currentGrid.gridNum[1].x ][m_currentGrid.gridNum[1].y+1].bVisable == false &&
			m_grid[m_currentGrid.gridNum[1].x ][m_currentGrid.gridNum[1].y+2].bVisable == false
			)
		{
			m_currentGrid.gridNum[0].x = m_currentGrid.gridNum[1].x ; m_currentGrid.gridNum[0].y = m_currentGrid.gridNum[0].y;
			m_currentGrid.gridNum[1].x = m_currentGrid.gridNum[0].x; m_currentGrid.gridNum[1].y = m_currentGrid.gridNum[0].y+1;
			m_currentGrid.gridNum[2].x = m_currentGrid.gridNum[0].x ;  m_currentGrid.gridNum[2].y = m_currentGrid.gridNum[0].y+2;
			m_currentGrid.gridNum[3].x = m_currentGrid.gridNum[0].x - 1; m_currentGrid.gridNum[3].y = m_currentGrid.gridNum[0].y;
			m_currentGrid.type = ZHENG_QI_DOWN_GRID;
		}
		else
		{
			m_currentGrid = tempCurrentGrid;
		}
	

				break;
			}
	case ZHENG_QI_DOWN_GRID:
	{
		//由下转左
		if (m_grid[m_currentGrid.gridNum[1].x][m_currentGrid.gridNum[1].y+1].bVisable == false &&
			m_grid[m_currentGrid.gridNum[0].x-1][m_currentGrid.gridNum[0].y].bVisable == false
			)
		{
			m_currentGrid.gridNum[0].x = m_currentGrid.gridNum[0].x+1; m_currentGrid.gridNum[0].y = m_currentGrid.gridNum[0].y;
			m_currentGrid.gridNum[1].x = m_currentGrid.gridNum[0].x; m_currentGrid.gridNum[1].y = m_currentGrid.gridNum[0].y + 1;
			m_currentGrid.gridNum[2].x = m_currentGrid.gridNum[0].x-1;  m_currentGrid.gridNum[2].y = m_currentGrid.gridNum[0].y +1;
			m_currentGrid.gridNum[3].x = m_currentGrid.gridNum[0].x - 2; m_currentGrid.gridNum[3].y = m_currentGrid.gridNum[0].y+1;
			m_currentGrid.type = ZHENG_QI_LEFT_GRID;
		}
	

		break;
	}
	case FAN_QI_LEFT_GRID:
	{
		if (m_currentGrid.gridNum[1].y == 9)
		{
			for (int i = 0; i < 4; i++)
			{
				m_currentGrid.gridNum[i].y--;
			}
		}
		//由左转上
		if (m_grid[m_currentGrid.gridNum[3].x+1][m_currentGrid.gridNum[3].y ].bVisable == false &&
			m_grid[m_currentGrid.gridNum[2].x][m_currentGrid.gridNum[2].y + 1].bVisable == false
			)
		{
			
			m_currentGrid.gridNum[0].x = m_currentGrid.gridNum[3].x ; m_currentGrid.gridNum[0].y = m_currentGrid.gridNum[3].y;
			m_currentGrid.gridNum[1].x = m_currentGrid.gridNum[0].x;     m_currentGrid.gridNum[1].y = m_currentGrid.gridNum[0].y + 1;
			m_currentGrid.gridNum[2].x = m_currentGrid.gridNum[0].x ;  m_currentGrid.gridNum[2].y = m_currentGrid.gridNum[0].y + 2;
			m_currentGrid.gridNum[3].x = m_currentGrid.gridNum[0].x +1; m_currentGrid.gridNum[3].y = m_currentGrid.gridNum[0].y ;
			m_currentGrid.type = FAN_QI_UP_GRID;
		}
		else
		{
			m_currentGrid = tempCurrentGrid;
		}
		break;
	}
	case FAN_QI_UP_GRID:
	{//由上转右
		if (m_grid[m_currentGrid.gridNum[3].x + 1][m_currentGrid.gridNum[3].y].bVisable == false &&
			m_grid[m_currentGrid.gridNum[3].x+1][m_currentGrid.gridNum[3].y + 1].bVisable == false
			)
		{
			m_currentGrid.gridNum[0].x = m_currentGrid.gridNum[3].x+1; m_currentGrid.gridNum[0].y = m_currentGrid.gridNum[3].y;
			m_currentGrid.gridNum[1].x = m_currentGrid.gridNum[0].x-1;     m_currentGrid.gridNum[1].y = m_currentGrid.gridNum[0].y ;
			m_currentGrid.gridNum[2].x = m_currentGrid.gridNum[0].x-2;  m_currentGrid.gridNum[2].y = m_currentGrid.gridNum[0].y;
			m_currentGrid.gridNum[3].x = m_currentGrid.gridNum[0].x ; m_currentGrid.gridNum[3].y = m_currentGrid.gridNum[0].y+1;
			m_currentGrid.type = FAN_QI_RIGHT_GRID;
		}
		break;
	}
	case FAN_QI_RIGHT_GRID:
	{    
		if (m_currentGrid.gridNum[3].y == 9)
		{
			for (int i = 0; i < 4; i++)
			{
				m_currentGrid.gridNum[i].y--;
			}
		}
		//由右转下
		if (m_grid[m_currentGrid.gridNum[1].x ][m_currentGrid.gridNum[1].y+1].bVisable == false &&
			m_grid[m_currentGrid.gridNum[1].x][m_currentGrid.gridNum[1].y + 2].bVisable == false&&
			m_grid[m_currentGrid.gridNum[1].x-1][m_currentGrid.gridNum[1].y + 2].bVisable == false
			)
		{
			m_currentGrid.gridNum[0].x = m_currentGrid.gridNum[1].x; m_currentGrid.gridNum[0].y = m_currentGrid.gridNum[1].y;
			m_currentGrid.gridNum[1].x = m_currentGrid.gridNum[0].x;     m_currentGrid.gridNum[1].y = m_currentGrid.gridNum[0].y + 1;
			m_currentGrid.gridNum[2].x = m_currentGrid.gridNum[0].x;  m_currentGrid.gridNum[2].y = m_currentGrid.gridNum[0].y + 2;
			m_currentGrid.gridNum[3].x = m_currentGrid.gridNum[0].x - 1; m_currentGrid.gridNum[3].y = m_currentGrid.gridNum[0].y+2;
			m_currentGrid.type = FAN_QI_DOWN_GRID;
		}
		else
		{
			m_currentGrid = tempCurrentGrid;
		}
		break;
	}
	case FAN_QI_DOWN_GRID:
	{  //由下转左
		if (m_grid[m_currentGrid.gridNum[1].x + 1][m_currentGrid.gridNum[1].y].bVisable == false &&
			m_grid[m_currentGrid.gridNum[1].x-1][m_currentGrid.gridNum[1].y ].bVisable == false&&
			m_grid[m_currentGrid.gridNum[1].x - 1][m_currentGrid.gridNum[1].y-1].bVisable == false
			)
		{
			m_currentGrid.gridNum[0].x = m_currentGrid.gridNum[1].x+1; m_currentGrid.gridNum[0].y = m_currentGrid.gridNum[1].y;
			m_currentGrid.gridNum[1].x = m_currentGrid.gridNum[0].x-1;     m_currentGrid.gridNum[1].y = m_currentGrid.gridNum[0].y;
			m_currentGrid.gridNum[2].x = m_currentGrid.gridNum[0].x-2;  m_currentGrid.gridNum[2].y = m_currentGrid.gridNum[0].y ;
			m_currentGrid.gridNum[3].x = m_currentGrid.gridNum[0].x -2; m_currentGrid.gridNum[3].y = m_currentGrid.gridNum[0].y-1;
			m_currentGrid.type = FAN_QI_LEFT_GRID;
		}
		break;
	}
		
	case ZHENG_ER_GRID:
	{
		//由横转坚
		if (m_grid[m_currentGrid.gridNum[0].x -1][m_currentGrid.gridNum[0].y].bVisable == false &&
			m_grid[m_currentGrid.gridNum[1].x + 1][m_currentGrid.gridNum[1].y].bVisable == false &&
			(m_currentGrid.gridNum[3].y - m_currentGrid.gridNum[0].y  == 2)
			)
		{
			m_currentGrid.gridNum[0].x = m_currentGrid.gridNum[0].x - 1; m_currentGrid.gridNum[0].y = m_currentGrid.gridNum[0].y;
			m_currentGrid.gridNum[1].x = m_currentGrid.gridNum[0].x+ 1;     m_currentGrid.gridNum[1].y = m_currentGrid.gridNum[0].y;
			m_currentGrid.gridNum[2].x = m_currentGrid.gridNum[0].x + 1;  m_currentGrid.gridNum[2].y = m_currentGrid.gridNum[0].y+1;
			m_currentGrid.gridNum[3].x = m_currentGrid.gridNum[0].x+2 ; m_currentGrid.gridNum[3].y = m_currentGrid.gridNum[0].y + 1;
			
		}
		else
		{
			if (m_currentGrid.gridNum[3].y == 9)
			{
				for (int i = 0; i < 4; i++)
				{
					m_currentGrid.gridNum[i].y--;
				}
			}
	if (m_grid[m_currentGrid.gridNum[2].x - 1][m_currentGrid.gridNum[2].y].bVisable == false &&
				m_grid[m_currentGrid.gridNum[2].x - 1][m_currentGrid.gridNum[2].y+1].bVisable == false &&
				m_currentGrid.gridNum[3].y - m_currentGrid.gridNum[0].y == 1)
		{
			//由坚转横
			m_currentGrid.gridNum[0].x = m_currentGrid.gridNum[1].x; m_currentGrid.gridNum[0].y = m_currentGrid.gridNum[1].y;
			m_currentGrid.gridNum[1].x = m_currentGrid.gridNum[0].x ;     m_currentGrid.gridNum[1].y = m_currentGrid.gridNum[0].y+1;
			m_currentGrid.gridNum[2].x = m_currentGrid.gridNum[0].x - 1;  m_currentGrid.gridNum[2].y = m_currentGrid.gridNum[0].y + 1;
			m_currentGrid.gridNum[3].x = m_currentGrid.gridNum[0].x -1; m_currentGrid.gridNum[3].y = m_currentGrid.gridNum[0].y + 2;
		}
	else
	{
		m_currentGrid = tempCurrentGrid;
	}
		}
		
		break;
	}
		
	case FAN_ER_GRID:
	{
		//由横转坚
		if (m_grid[m_currentGrid.gridNum[0].x][m_currentGrid.gridNum[0].y-1].bVisable == false &&
			m_grid[m_currentGrid.gridNum[1].x + 1][m_currentGrid.gridNum[1].y-1].bVisable == false &&
			(m_currentGrid.gridNum[3].y - m_currentGrid.gridNum[0].y == 2)
			)
		{
			m_currentGrid.gridNum[0].x = m_currentGrid.gridNum[2].x +1; m_currentGrid.gridNum[0].y = m_currentGrid.gridNum[2].y-1;
			m_currentGrid.gridNum[1].x = m_currentGrid.gridNum[0].x- 1;     m_currentGrid.gridNum[1].y = m_currentGrid.gridNum[0].y;
			m_currentGrid.gridNum[2].x = m_currentGrid.gridNum[0].x - 1;  m_currentGrid.gridNum[2].y = m_currentGrid.gridNum[0].y + 1;
			m_currentGrid.gridNum[3].x = m_currentGrid.gridNum[0].x - 2; m_currentGrid.gridNum[3].y = m_currentGrid.gridNum[0].y + 1;

		}
		else
		{
			if (m_currentGrid.gridNum[3].y == 9)
			{
				for (int i = 0; i < 4; i++)
				{
					m_currentGrid.gridNum[i].y--;
				}
			}
        if (m_grid[m_currentGrid.gridNum[3].x ][m_currentGrid.gridNum[3].y-1].bVisable == false &&
				m_grid[m_currentGrid.gridNum[2].x][m_currentGrid.gridNum[2].y + 1].bVisable == false &&
				m_currentGrid.gridNum[3].y - m_currentGrid.gridNum[0].y == 1)
			{
			//由坚转横
			m_currentGrid.gridNum[0].x = m_currentGrid.gridNum[3].x; m_currentGrid.gridNum[0].y = m_currentGrid.gridNum[3].y-1;
			m_currentGrid.gridNum[1].x = m_currentGrid.gridNum[0].x;     m_currentGrid.gridNum[1].y = m_currentGrid.gridNum[0].y + 1;
			m_currentGrid.gridNum[2].x = m_currentGrid.gridNum[0].x+1;  m_currentGrid.gridNum[2].y = m_currentGrid.gridNum[0].y + 1;
			m_currentGrid.gridNum[3].x = m_currentGrid.gridNum[0].x+ 1; m_currentGrid.gridNum[3].y = m_currentGrid.gridNum[0].y + 2;
			}
else
{
	m_currentGrid = tempCurrentGrid;
}
           
		}
			
		break;
	}
	case KA_LEFT_GRID:
	{
		if (m_currentGrid.gridNum[1].y == 9)
		{
			for (int i = 0; i < 4; i++)
			{
				m_currentGrid.gridNum[i].y--;
			}
		}
		//由左转上
		if (m_grid[m_currentGrid.gridNum[3].x ][m_currentGrid.gridNum[3].y-1].bVisable == false &&
			m_grid[m_currentGrid.gridNum[3].x ][m_currentGrid.gridNum[3].y+1].bVisable == false
			)
		{
			m_currentGrid.gridNum[0].x = m_currentGrid.gridNum[2].x ; m_currentGrid.gridNum[0].y = m_currentGrid.gridNum[2].y;
			m_currentGrid.gridNum[1].x = m_currentGrid.gridNum[0].x -1;     m_currentGrid.gridNum[1].y = m_currentGrid.gridNum[0].y-1;
			m_currentGrid.gridNum[2].x = m_currentGrid.gridNum[0].x -1;  m_currentGrid.gridNum[2].y = m_currentGrid.gridNum[0].y;
			m_currentGrid.gridNum[3].x = m_currentGrid.gridNum[0].x -1; m_currentGrid.gridNum[3].y = m_currentGrid.gridNum[0].y+ 1;
			m_currentGrid.type = KA_UP_GRID;
		}
		else
		{
			m_currentGrid = tempCurrentGrid;
		}
		break;
	}
		break;
	case KA_UP_GRID:
	{
		//由上转右
		if (m_grid[m_currentGrid.gridNum[1].x+1][m_currentGrid.gridNum[1].y ].bVisable == false &&
			m_grid[m_currentGrid.gridNum[1].x+2][m_currentGrid.gridNum[1].y ].bVisable == false
			)
		{
			m_currentGrid.gridNum[0].x = m_currentGrid.gridNum[0].x; m_currentGrid.gridNum[0].y = m_currentGrid.gridNum[0].y ;
			m_currentGrid.gridNum[1].x = m_currentGrid.gridNum[0].x+1;     m_currentGrid.gridNum[1].y = m_currentGrid.gridNum[0].y- 1;
			m_currentGrid.gridNum[2].x = m_currentGrid.gridNum[0].x;  m_currentGrid.gridNum[2].y = m_currentGrid.gridNum[0].y -1;
			m_currentGrid.gridNum[3].x = m_currentGrid.gridNum[0].x- 1; m_currentGrid.gridNum[3].y = m_currentGrid.gridNum[0].y- 1;
			m_currentGrid.type = KA_RIGHT_GRID;
		}
		break;
	}
	break;
	case KA_RIGHT_GRID:
	{
		if (m_currentGrid.gridNum[0].y == 9)
		{
			for (int i = 0; i < 4; i++)
			{
				m_currentGrid.gridNum[i].y--;
			}
		}
		//由右转下
		if (m_grid[m_currentGrid.gridNum[0].x][m_currentGrid.gridNum[0].y + 1].bVisable == false &&
			m_grid[m_currentGrid.gridNum[0].x-1][m_currentGrid.gridNum[0].y ].bVisable == false
			)
		{
			m_currentGrid.gridNum[0].x = m_currentGrid.gridNum[0].x-1; m_currentGrid.gridNum[0].y = m_currentGrid.gridNum[0].y ;
			m_currentGrid.gridNum[1].x = m_currentGrid.gridNum[0].x+1;     m_currentGrid.gridNum[1].y = m_currentGrid.gridNum[0].y - 1;
			m_currentGrid.gridNum[2].x = m_currentGrid.gridNum[0].x+1;  m_currentGrid.gridNum[2].y = m_currentGrid.gridNum[0].y;
			m_currentGrid.gridNum[3].x = m_currentGrid.gridNum[0].x + 1; m_currentGrid.gridNum[3].y = m_currentGrid.gridNum[0].y + 1;
			m_currentGrid.type = KA_DOWN_GRID;
		}
		else
		{
			m_currentGrid = tempCurrentGrid;
		}
		break;
	}
	
	case KA_DOWN_GRID:
	{
		//由下转左
		if (m_grid[m_currentGrid.gridNum[2].x+1][m_currentGrid.gridNum[2].y ].bVisable == false
			)
		{
			m_currentGrid.gridNum[0].x = m_currentGrid.gridNum[1].x; m_currentGrid.gridNum[0].y = m_currentGrid.gridNum[1].y ;
			m_currentGrid.gridNum[1].x = m_currentGrid.gridNum[0].x+1;     m_currentGrid.gridNum[1].y = m_currentGrid.gridNum[0].y + 1;
			m_currentGrid.gridNum[2].x = m_currentGrid.gridNum[0].x;  m_currentGrid.gridNum[2].y = m_currentGrid.gridNum[0].y + 1;
			m_currentGrid.gridNum[3].x = m_currentGrid.gridNum[0].x - 1; m_currentGrid.gridNum[3].y = m_currentGrid.gridNum[0].y + 1;
			m_currentGrid.type = KA_LEFT_GRID;
		}
		break;
	}
	
	default:
		break;
	}
	isVisableGrid(m_currentGrid, true);
}
//左移格子
void CLogical::LeftMoveGrid()
{
	if ((gGameStatus != GAME_PLAY_STATUS )|| (m_bStartAnimation != false))
	{
		return;
	}
	STRUT_GRID grid = m_currentGrid;

	for (int i = 0; i < 4; i++)
	{
		if (grid.gridNum[i].y == 0)
			return;
		grid.gridNum[i].y--;
		bool bEqual = false;
		for (int j = 0; j < 4; j++)
		{
			if ((grid.gridNum[i].x == m_currentGrid.gridNum[j].x) && (grid.gridNum[i].y == m_currentGrid.gridNum[j].y))
				bEqual = true;
		}
		if (m_grid[grid.gridNum[i].x][grid.gridNum[i].y].bVisable == true && bEqual != true)
		{
			return;
		}
	}
	isVisableGrid(m_currentGrid, false);
		for (int i = 0; i < 4;i++)
	{
			m_currentGrid.gridNum[i].y--;
	}
		
		isVisableGrid(m_currentGrid, true);
}
//右移格子
void CLogical::RightMoveGrid()
{
	if ((gGameStatus != GAME_PLAY_STATUS)||(m_bStartAnimation !=false))
	{
		return;
	}
	STRUT_GRID grid = m_currentGrid;
	for (int i = 0; i < 4; i++)
	{
		if (grid.gridNum[i].y == COL_NUM-1)
			return;
		grid.gridNum[i].y++;
		bool bEqual = false;
		for (int j = 0; j < 4; j++)
		{
			if ((grid.gridNum[i].x == m_currentGrid.gridNum[j].x) && (grid.gridNum[i].y == m_currentGrid.gridNum[j].y))
				bEqual = true;
		}
		if (m_grid[grid.gridNum[i].x][grid.gridNum[i].y].bVisable == true && bEqual != true)
		{
			return;
		}
	}

	isVisableGrid(m_currentGrid, false);
	{
		m_currentGrid.gridNum[0].y++;
		m_currentGrid.gridNum[1].y++;
		m_currentGrid.gridNum[2].y++;
		m_currentGrid.gridNum[3].y++;
	}
	isVisableGrid(m_currentGrid, true);
}
bool  CLogical::DownMoveGrid()
{
	if (gGameStatus != GAME_PLAY_STATUS)
	{
		return false;
	}

	STRUT_GRID grid = m_currentGrid;
	
	for (int i = 0; i < 4; i++)
	{
		if (grid.gridNum[i].x == 0)
		{
			//m_AnimationCurrentGrid = m_currentGrid;

			m_bStartAnimation = true;
			if (AnimationDetection()==true)
			{
				memcpy(m_CopyGrid, m_grid, sizeof(POINT_GRID) * ROW_NUM * COL_NUM);
				return true;
			}
			DestroyGrid();
			GameOver();
			if (IsAnimationFinsh())
			{
				m_currentGrid = m_nextGrid;
				GetRandGrid(m_nextGrid);
				elapsedTime = 0.0f;
			}
				
			SimpleAudioEngine::sharedEngine()->playEffect(DOWN_BOTTOM);
		
			return true;
		}
		grid.gridNum[i].x--;
		bool bEqual = false;
		for (int j = 0; j < 4;j++)
		{
			if ((grid.gridNum[i].x == m_currentGrid.gridNum[j].x) && (grid.gridNum[i].y == m_currentGrid.gridNum[j].y))
				bEqual = true;
		}
		
		if (m_bCenterDestoryGrid == false)
		{
			
			memcpy(m_grid,m_CopyGrid, sizeof(POINT_GRID) * ROW_NUM * COL_NUM);
		}
		if ((m_grid[grid.gridNum[i].x][grid.gridNum[i].y].bVisable == true) && (bEqual != true))
		{
			//m_AnimationCurrentGrid = m_currentGrid;
			m_bStartAnimation = true;
	
			if (m_bCenterDestoryGrid ==true)
			{
				if (AnimationDetection() == true)
				{
					m_bCenterDestoryGrid = false;
					memcpy(m_CopyGrid, m_grid, sizeof(POINT_GRID) * ROW_NUM * COL_NUM);
					return true;
				}
			}
			DestroyGrid();
			GameOver();
			if (IsAnimationFinsh())
			{
				m_currentGrid = m_nextGrid;
				GetRandGrid(m_nextGrid);
				elapsedTime = 0.0f;
			}

			SimpleAudioEngine::sharedEngine()->playEffect(DOWN_BOTTOM);
			
			return true;
		}
	
	}
	//if (m_bCenterDestoryGrid==false)
	//{
	//	m_bCenterDestoryGrid = true;
	//	DestroyGrid();
	//	GameOver();
	//	if (IsAnimationFinsh())
	//	{
	//		m_currentGrid = m_nextGrid;
	//		GetRandGrid(m_nextGrid);
	//	}
	//}
	
	isVisableGrid(m_currentGrid, false);
	{
		m_currentGrid.gridNum[0].x--;
			m_currentGrid.gridNum[1].x--;
		m_currentGrid.gridNum[2].x--;
		m_currentGrid.gridNum[3].x--;
	}
	isVisableGrid(m_currentGrid, true);

	return false;
}
//获得一个随机的方格
void CLogical::GetRandGrid(STRUT_GRID &grid)
{
	int type = (rand() % (GRID_NUMS+11));//加上11是为了平均各个方块出现的机率
	//type = 9;
	int base_x = ROW_NUM-1;
	int base_y = COL_NUM -6;
		switch (type)
		{
		case 	V_YI_GRID:
		case    GRID_NUMS:
		{
			grid.type = V_YI_GRID;
			grid.gridNum[0].x = base_x ;                 grid.gridNum[0].y = base_y;
			grid.gridNum[1].x = base_x - 1;     grid.gridNum[1].y = base_y ;
			grid.gridNum[2].x = base_x - 2; grid.gridNum[2].y = base_y;
			grid.gridNum[3].x = base_x  - 3; grid.gridNum[3].y = base_y;
			
		}
			break;
		case GRID_NUMS+1:
		case H_YI_GRID:
		{
			grid.type = H_YI_GRID;
			grid.gridNum[0].x = base_x-3;          grid.gridNum[0].y = base_y;
			grid.gridNum[1].x = base_x-3 ;      grid.gridNum[1].y = base_y+1;
			grid.gridNum[2].x = base_x-3 ;      grid.gridNum[2].y = base_y+2;
			grid.gridNum[3].x = base_x -3;     grid.gridNum[3].y = base_y+3;
		}
			break;
		case TIAN_ZI_GRID:
		case    GRID_NUMS+2:
		case    GRID_NUMS+3:
		case    GRID_NUMS+4:
		{
			grid.type = TIAN_ZI_GRID;
			grid.gridNum[0].x = base_x-2;          grid.gridNum[0].y = base_y;
			grid.gridNum[1].x = base_x-2;      grid.gridNum[1].y = base_y + 1;
			grid.gridNum[2].x = base_x-3;      grid.gridNum[2].y = base_y ;
			grid.gridNum[3].x = base_x-3;     grid.gridNum[3].y = base_y + 1;
		}
			break;
		case ZHENG_QI_LEFT_GRID:
		{
			grid.type = ZHENG_QI_LEFT_GRID;
			grid.gridNum[0].x = base_x-1;          grid.gridNum[0].y = base_y;
			grid.gridNum[1].x = base_x-1;      grid.gridNum[1].y = base_y + 1;
			grid.gridNum[2].x = base_x-2;      grid.gridNum[2].y = base_y + 1;
			grid.gridNum[3].x = base_x-3;     grid.gridNum[3].y = base_y + 1;
			break;
		}
			break;
		case ZHENG_QI_UP_GRID:
		{
			grid.type = ZHENG_QI_UP_GRID;
			grid.gridNum[0].x = base_x-3;          grid.gridNum[0].y = base_y;
			grid.gridNum[1].x = base_x-3;      grid.gridNum[1].y = base_y + 1;
			grid.gridNum[2].x = base_x - 3;      grid.gridNum[2].y = base_y + 2;
			grid.gridNum[3].x = base_x - 2;     grid.gridNum[3].y = base_y + 2;
			break;
		}
		case ZHENG_QI_RIGHT_GRID:
		{
			grid.type = ZHENG_QI_RIGHT_GRID;
			grid.gridNum[0].x = base_x-1;          grid.gridNum[0].y = base_y;
			grid.gridNum[1].x = base_x-2;      grid.gridNum[1].y = base_y ;
			grid.gridNum[2].x = base_x - 3;      grid.gridNum[2].y = base_y ;
			grid.gridNum[3].x = base_x - 3;     grid.gridNum[3].y = base_y + 1;
			break;
		}
		case ZHENG_QI_DOWN_GRID:
		{
			grid.type = ZHENG_QI_DOWN_GRID;
			grid.gridNum[0].x = base_x-2;          grid.gridNum[0].y = base_y;
			grid.gridNum[1].x = base_x-2;      grid.gridNum[1].y = base_y + 1;
			grid.gridNum[2].x = base_x - 2;      grid.gridNum[2].y = base_y + 2;
			grid.gridNum[3].x = base_x - 3;     grid.gridNum[3].y = base_y ;
			break;
		}
		case FAN_QI_LEFT_GRID:
		{
			grid.type = FAN_QI_LEFT_GRID;
			grid.gridNum[0].x = base_x - 1;          grid.gridNum[0].y = base_y+1;
			grid.gridNum[1].x = base_x - 2;      grid.gridNum[1].y = base_y+1 ;
			grid.gridNum[2].x = base_x - 3;      grid.gridNum[2].y = base_y+1 ;
			grid.gridNum[3].x = base_x - 3;     grid.gridNum[3].y = base_y;
			break;
		}
		case FAN_QI_UP_GRID:
		{
			grid.type = FAN_QI_UP_GRID;
			grid.gridNum[0].x = base_x - 3;          grid.gridNum[0].y = base_y;
			grid.gridNum[1].x = base_x - 3;      grid.gridNum[1].y = base_y+1 ;
			grid.gridNum[2].x = base_x - 3;      grid.gridNum[2].y = base_y + 2;
			grid.gridNum[3].x = base_x - 2;     grid.gridNum[3].y = base_y;
			break;
		}
		case FAN_QI_RIGHT_GRID:
		{
			grid.type = FAN_QI_RIGHT_GRID;
			grid.gridNum[0].x = base_x - 1;          grid.gridNum[0].y = base_y;
			grid.gridNum[1].x = base_x - 2;      grid.gridNum[1].y = base_y ;
			grid.gridNum[2].x = base_x - 3;      grid.gridNum[2].y = base_y ;
			grid.gridNum[3].x = base_x - 1;     grid.gridNum[3].y = base_y+1;
			break;
		}
		
		case FAN_QI_DOWN_GRID:
		{
			grid.type = FAN_QI_DOWN_GRID;
			grid.gridNum[0].x = base_x - 2;          grid.gridNum[0].y = base_y;
			grid.gridNum[1].x = base_x - 2;      grid.gridNum[1].y = base_y + 1;
			grid.gridNum[2].x = base_x - 2;      grid.gridNum[2].y = base_y + 2;
			grid.gridNum[3].x = base_x - 3;     grid.gridNum[3].y = base_y+2;
			break;
		}
		
		case    GRID_NUMS + 5:
		case    GRID_NUMS + 6:
		case    GRID_NUMS + 7:
		case ZHENG_ER_GRID:
		{
			grid.type = ZHENG_ER_GRID;
			int tempType = rand() % 2 ;
			if (tempType==1)
			{
				grid.gridNum[0].x = base_x - 2;          grid.gridNum[0].y = base_y;
				grid.gridNum[1].x = base_x - 2;      grid.gridNum[1].y = base_y + 1;
				grid.gridNum[2].x = base_x - 3;      grid.gridNum[2].y = base_y + 1;
				grid.gridNum[3].x = base_x - 3;     grid.gridNum[3].y = base_y + 2;
			}
			else
			{
				grid.gridNum[0].x = base_x - 3;          grid.gridNum[0].y = base_y;
				grid.gridNum[1].x = base_x - 2;      grid.gridNum[1].y = base_y ;
				grid.gridNum[2].x = base_x - 2;      grid.gridNum[2].y = base_y + 1;
				grid.gridNum[3].x = base_x - 1;     grid.gridNum[3].y = base_y + 1;
			}
		
			break;
		}
		case    GRID_NUMS + 8:
		case    GRID_NUMS + 9:
		case    GRID_NUMS + 10:
		case FAN_ER_GRID:
		{
			grid.type = FAN_ER_GRID;
			int tempType = rand() % 2;
			if (tempType==1)
			{
				grid.gridNum[0].x = base_x - 3;          grid.gridNum[0].y = base_y;
				grid.gridNum[1].x = base_x - 3;      grid.gridNum[1].y = base_y + 1;
				grid.gridNum[2].x = base_x - 2;      grid.gridNum[2].y = base_y + 1;
				grid.gridNum[3].x = base_x - 2;     grid.gridNum[3].y = base_y + 2;
			}
			else
			{
				grid.gridNum[0].x = base_x - 1;          grid.gridNum[0].y = base_y;
				grid.gridNum[1].x = base_x - 2;      grid.gridNum[1].y = base_y;
				grid.gridNum[2].x = base_x - 2;      grid.gridNum[2].y = base_y + 1;
				grid.gridNum[3].x = base_x - 3;     grid.gridNum[3].y = base_y + 1;
			}
		
            break;
		}
		case KA_LEFT_GRID:
		{
			grid.type = KA_LEFT_GRID;
			grid.gridNum[0].x = base_x - 2;          grid.gridNum[0].y = base_y ;
			grid.gridNum[1].x = base_x - 1;      grid.gridNum[1].y = base_y + 1;
			grid.gridNum[2].x = base_x - 2;      grid.gridNum[2].y = base_y + 1;
			grid.gridNum[3].x = base_x - 3;     grid.gridNum[3].y = base_y+1;
			break;
		}
		case KA_UP_GRID:
		{
			grid.type = KA_UP_GRID;
		grid.gridNum[0].x = base_x - 2;          grid.gridNum[0].y = base_y + 1;
		grid.gridNum[1].x = base_x - 3;      grid.gridNum[1].y = base_y ;
		grid.gridNum[2].x = base_x - 3;      grid.gridNum[2].y = base_y + 1;
		grid.gridNum[3].x = base_x - 3;     grid.gridNum[3].y = base_y+2;
			break;
		}
		case KA_RIGHT_GRID:
		{
			grid.type = KA_RIGHT_GRID;
			grid.gridNum[0].x = base_x - 2;          grid.gridNum[0].y = base_y + 1;
			grid.gridNum[1].x = base_x - 1;      grid.gridNum[1].y = base_y ;
			grid.gridNum[2].x = base_x - 2;      grid.gridNum[2].y = base_y ;
			grid.gridNum[3].x = base_x - 3;     grid.gridNum[3].y = base_y;
			break;
		}
		case KA_DOWN_GRID:
				{
			grid.type = KA_DOWN_GRID;
			grid.gridNum[0].x = base_x - 3;          grid.gridNum[0].y = base_y + 1;
			grid.gridNum[1].x = base_x - 2;      grid.gridNum[1].y = base_y ;
			grid.gridNum[2].x = base_x - 2;      grid.gridNum[2].y = base_y + 1;
			grid.gridNum[3].x = base_x - 2;     grid.gridNum[3].y = base_y+2;
					break;
				}
		default:
			break;
		}
		//isVisableGrid(m_currentGrid, true);
}
void CLogical::isVisableGrid(STRUT_GRID &grid, bool bVisable)
{
	for (int i = 0; i < 4; i++)
	{
		grid.gridNum[i].bVisable=bVisable;
		m_grid[grid.gridNum[i].x][grid.gridNum[i].y].bVisable = bVisable;
	}
}

void  CLogical::InitGrid(GameMainLayer* layer)
{
	memset(stars, 0, sizeof(stars));
	memset(m_grid, 0, sizeof(POINT_GRID) * ROW_NUM * COL_NUM);
	memset(m_CopyGrid, 0, sizeof(POINT_GRID) * ROW_NUM * COL_NUM);
	memset(starsNext, 0, sizeof(CGrid) * 4);
	//memset(&m_AnimationCurrentGrid, 0, sizeof(m_AnimationCurrentGrid));
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	INT_SCREEN_POS_X = origin.x + 20;
	INT_SCREEN_POS_Y = origin.y + 8 * STAR_HEIGHT;
	elapsedTime = 0.0f;
	gGameStatus = GAME_FREE_STATUS;
	m_gameScore = 0;
	m_speedChange = 0.0f;
	m_bAnimationFinsh = true;
	m_bCenterDestoryGrid = true;
	gameLayer = layer;
	m_bStartAnimation = false;
	
	GetRandGrid(m_currentGrid);
	GetRandGrid(m_nextGrid);
	/*for (int i = 0; i < 10;i++)
	{
		m_grid[i][6].bVisable = true;
	}*/
	for (int row = 0; row < ROW_NUM; ++row)
	{
		for (int col = 0; col < COL_NUM; ++col)
		{
			int index = (rand() % 5) + 1;
			CGrid* star = CGrid::create();
			if (star)
			{
				star->setScale(INT_SCALE);

				star->setPos(ccp(INT_SCREEN_POS_X + STAR_WIDTH*col + (STAR_WIDTH / 2), STAR_HEIGHT*row + STAR_HEIGHT / 2 + INT_SCREEN_POS_Y));
				if (row < ROW_NUM - 4)
					star->setVisible(m_grid[row][col].bVisable);
				else
					star->setVisible(false);
				gameLayer->addChild(star);

				stars[row][col] = star;
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		starsNext[i] = CGrid::create();
		starsNext[i]->setScale(INT_SCALE);
		CCPoint nextPos = stars[m_nextGrid.gridNum[i].x][m_nextGrid.gridNum[i].y]->getPosition();
		starsNext[i]->setPos(ccp(nextPos.x + 220, nextPos.y - (ROW_NUM-10) * STAR_HEIGHT+10));
		starsNext[i]->setVisible(true);
			gameLayer->addChild(starsNext[i]);
	}
}

void CLogical::onUpdate(float delta)
{
	
	for (int row = 0; row < ROW_NUM - 4; ++row)
	{
		for (int col = 0; col < COL_NUM; ++col)
		{
			CGrid* star = stars[row][col];
			if (star)
			{
				star->setVisible(m_grid[row][col].bVisable);
				star->onUpdate(delta);
			}
		}
	}

	if (gGameStatus!=GAME_PLAY_STATUS)
	{
		return;
	}
	if (m_bStartAnimation ==true)
	{
		SetAnimationBool(m_MyParticle->clearMatrixOneByOne(delta, gameLayer));
	}
	if (IsAnimationFinsh())
	{
	elapsedTime += delta;
	if (elapsedTime >= REDUCE_INTERVAL_TIME-m_speedChange)
	{
		elapsedTime -= (REDUCE_INTERVAL_TIME - m_speedChange);
			elapsedTime = 0.0f;
	      
			DownMoveGrid();
		
		for (int i = 0; i < 4; i++)
		{
			CCPoint nextPos = stars[m_nextGrid.gridNum[i].x][m_nextGrid.gridNum[i].y]->getPosition();
			starsNext[i]->setPos(ccp(nextPos.x + 220, nextPos.y - (ROW_NUM - 10) * STAR_HEIGHT + 10));
			//starsNext[i]->setVisible(true);
			starsNext[i]->onUpdate(delta);
		
		}
	}
	}
}
//消除方格
void  CLogical::DestroyGrid()
{

	int dieNum = 0;
	int row = 1000;
	for (int i = 0; i < 4; i++)
	{
		row = m_currentGrid.gridNum[i].x < row ? m_currentGrid.gridNum[i].x: row;
	}
	int tempRowNum = row + 4;
	for (; row < tempRowNum; ++row)
	{   
		int col = 0;
		for ( col = 0; col < COL_NUM; ++col)
		{
			if(m_CopyGrid[row][col].bVisable == false)
				break;
		}
		if (col==COL_NUM)
		{
			if (!IsAnimationFinsh())
				return;
		   dieNum++;
		   m_bCenterDestoryGrid = true;
		   for (col = 0; col < COL_NUM; ++col)
		   {
			   m_CopyGrid[row][col].bVisable = false;
			   m_grid[row][col].bVisable = false;
		   }
			for (	int tempRow = row; tempRow < ROW_NUM-1; ++tempRow)
			{
				for (col = 0; col < COL_NUM; ++col)
				{
					
					m_grid[tempRow][col].bVisable = m_grid[tempRow+1][col].bVisable;
					m_grid[tempRow+1][col].bVisable = false;
					m_CopyGrid[tempRow][col].bVisable = m_CopyGrid[tempRow+1][col].bVisable;
					m_CopyGrid[tempRow + 1][col].bVisable = false;

				}
			}
			row--;
		}
		if (dieNum==4)
		{
			break;
		}
	}
	m_bStartAnimation = false;
}
//开始游戏
void CLogical::StartGame()
{
	gGameStatus = GAME_PLAY_STATUS;
}
//暂停游戏
void CLogical::PauseGame()
{
	gGameStatus = GAME_PAUSE_STATUS;
}
//退出游戏
void CLogical::ExitGame()
{
	gGameStatus = GAME_FREE_STATUS;
}
void CLogical::GameOver()
{
	int tempRow = ROW_NUM - 4;
	for (int i = 0; i < COL_NUM;i++)
	{
		if (m_grid[tempRow][i].bVisable == true)
		{
			gGameStatus = GAME_FREE_STATUS;
			memset(m_grid, 0, sizeof(POINT_GRID) * ROW_NUM * COL_NUM);
			gameLayer->RunGameOverLabel();
			SimpleAudioEngine::sharedEngine()->playEffect(GAME_OVER);
			m_gameScore = 0;
			break;
		}	
	}
	
}
POINT_GRID* CLogical::GetGameData()
{
	isVisableGrid(m_currentGrid, false);
	POINT_GRID *a = &m_grid[0][0];
	return a;
}
CLogical *CLogical::GetInstance()
{

	if (!pLogical)
	{
		pLogical = new CLogical();
	}

	return pLogical;

}
void CLogical::SetGameScore(int score)
{
	m_gameScore = score;
}

void CLogical::SetGameSpeedFast()
{
		m_speedChange = m_speedChange + 0.05;
}
void  CLogical::SetGarmeHistorySpeed(float speed)
{
	m_speedChange = speed;
}
bool CLogical::AnimationDetection()
{

	if (gGameStatus != GAME_PLAY_STATUS || m_bStartAnimation==false)
	{
		return false;
	}
	STRUT_GRID grid = m_currentGrid;
	bool bTestSuccess = false;
	int dieNum = 0;
	int row = 1000;
	for (int i = 0; i < 4; i++)
	{
		row = grid.gridNum[i].x < row ? grid.gridNum[i].x : row;
	}
			//CCAssert((row >= 0)|| (row<ROW_NUM),"row < 0,row >=ROW_NUM");
	int sand = (rand() % 3)+1;
	//sand = 3;
	switch (sand)
	{
	case PARTICLE_EXPLOSION:
		m_MyParticle = m_myExplosion;
		break;
	case PARTICLE_FIRE:
		m_MyParticle = m_MyFire;
		break;
	case  PARTICLE_RING:
		m_MyParticle = m_MyRing;
		break;
	default:
		break;
	}
	int tempRow = row + 4;
	for (; row < tempRow; ++row)
			{
				int col = 0;
				for (col = 0; col < COL_NUM; ++col)
				{
					if (m_grid[row][col].bVisable == false)
						break;
				}
				if (col == COL_NUM)
				{	
					dieNum++;
					bTestSuccess = true;
					SetAnimationBool(false);
					for (int tempCol = 0; tempCol < COL_NUM; ++tempCol)
					{
					
						m_MyParticle->GetGrid(stars[row][tempCol], &m_grid[row][tempCol], tempCol);
					}
					
				}
			}
	//成绩统计
	if (dieNum == 1)
	{
		m_gameScore += 100;

	}
	else if (dieNum == 2)
	{
		m_gameScore += 300;
	}
	else if (dieNum == 3)
	{
		m_gameScore += 600;
	}
	else if (dieNum == 4)
	{
		m_gameScore += 1200;
	}
	else
	{

	}


	return bTestSuccess;
}


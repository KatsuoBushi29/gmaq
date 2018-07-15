
#include <gl/freeglut.h>
#include "CreatureManager.h"
/* Creature */
#include "Wolf.h"

/* namespace */
using namespace std;

/* constant */
const unsigned int	CREATURE_MNG_EDGE_POS			= (0x00000000u);
const unsigned int	CREATURE_MNG_FILED_SIZE_ZERO	= (0x00000000u);

const unsigned int	CREATURE_MNG_NO_EXIST_CREATURES	= (0x00000000u);


CreatureManager::CreatureManager( const unsigned int	initNum
								, spaceSize_t			&pFieldSize
								, const unsigned int	fateSeed )
{
	m_creatureNum	= initNum;
	m_fieldWidth	= pFieldSize.leftLength - pFieldSize.rightLength;
	m_fieldHeight	= pFieldSize.frontLength - pFieldSize.backLength;

	m_pCreatureList = new vector<Creature *>(m_creatureNum, nullptr);
	m_p2dField		= new vector<vector<Ground *>>(m_fieldHeight
								, vector<Ground *>(m_fieldWidth, nullptr));

	m_pFateModule	= new mt19937;
//	m_pFateModule->seed(fateSeed); /* TODO : Need Modify */
}


CreatureManager::~CreatureManager(void)
{
	delete m_pCreatureList;
	
	/* clear creature */
	for(unsigned int creatureIdx = 0u; creatureIdx < m_creatureNum; creatureIdx++){
		delete m_pCreatureList->at(creatureIdx);
	}

	/* clear field */
	for(unsigned int heightIdx = 0u; heightIdx < m_fieldHeight; heightIdx++){
		for(unsigned int widthIdx = 0u; widthIdx < m_fieldWidth; widthIdx++){
			delete m_p2dField->at(heightIdx).at(widthIdx);
		}
	}
	delete m_p2dField;

	delete m_pFateModule;
}


unsigned int CreatureManager::getCreatures( const spaceSize_t		&size,
											queue<const Creature *>	&pCreatures )
{
	unsigned int	findNum = CREATURE_MNG_NO_EXIST_CREATURES;
	areaIndex_t		area;

	if (true == calcAreaIdx(size, area)) {
		/* search Creatures */
		for (unsigned int xIdx = area.lowerXIdx; xIdx < area.upperXIdx; xIdx++) {
			for (unsigned int yIdx = area.lowerYIdx; yIdx < area.upperYIdx; yIdx++) {
				findNum += m_p2dField->at(yIdx).at(xIdx)->refer(pCreatures);
			}
		}	
	}
	return findNum;
}


unsigned int CreatureManager::getGrounds(const spaceSize_t &size, vector<vector<Ground *>> &pGrounds)
{
	areaIndex_t		area;
	unsigned int	horNum;
	unsigned int	verNum;
	unsigned int	totalNum;

	if (true == calcAreaIdx(size, area)) {
		horNum		= area.upperXIdx - area.lowerXIdx + 1;
		verNum		= area.upperYIdx - area.lowerYIdx + 1;
		totalNum	= horNum * verNum;
		pGrounds	= vector<vector<Ground *>>(horNum, vector<Ground *>(verNum, nullptr));
		
		for (unsigned int xIdx = area.lowerXIdx; xIdx < area.upperXIdx; xIdx++) {
			for (unsigned int yIdx = area.lowerYIdx; yIdx < area.upperYIdx; yIdx++) {
				pGrounds.at(xIdx - area.lowerXIdx).at(yIdx - area.lowerYIdx)
					= m_p2dField->at(yIdx).at(xIdx);
			}
		}
	}
	else {
		totalNum	= 0u;
	}
	return totalNum;
}


bool CreatureManager::initCreateCreatures(void)/* çÏê¨Ç∑ÇÈCreatureÇÃì‡ñÛÇà¯êîéwíËÇ≈Ç´ÇÈÇ∆Ç¢Ç¢Ç©Ç‡... */
{
	posInfo_t initPos		= {0u, 0u};
	unsigned int widthIdx	= 0u;
	unsigned int heightIdx	= 0u;

	/* create 2d field */
	for(heightIdx = 0u; heightIdx < m_fieldHeight; heightIdx++){
		for(widthIdx = 0u; widthIdx < m_fieldWidth; widthIdx++){
			m_p2dField->at(heightIdx).at(widthIdx) = new Ground();
		}
	}

	/* create init creatures */
	for(unsigned int creatureIdx = 0u; creatureIdx < m_creatureNum; creatureIdx++){
		initPos.xHorPos = 50 << POS_INFO_DECIMAL;//(*m_pFateModule)() % (m_fieldWidth << POS_INFO_DECIMAL);
		initPos.yHorPos = 50 << POS_INFO_DECIMAL;//(*m_pFateModule)() % (m_fieldHeight << POS_INFO_DECIMAL);
		widthIdx		= initPos.xHorPos >> POS_INFO_DECIMAL;
		heightIdx		= initPos.yHorPos >> POS_INFO_DECIMAL;
		m_pCreatureList->at(creatureIdx) = new Wolf((LocalSpace *)(this) ,&initPos);
		/* register Creatures to Ground */
		m_p2dField->at(heightIdx).at(widthIdx)->put( *(m_pCreatureList->at(creatureIdx)) );
	}

	return true;
}


bool CreatureManager::execInteraction(void)
{
	for(unsigned int creatureIdx = 0u; creatureIdx < m_creatureNum; creatureIdx++){
		m_pCreatureList->at(creatureIdx)->sense();
		m_pCreatureList->at(creatureIdx)->action();
		m_pCreatureList->at(creatureIdx)->reflect();
		m_pCreatureList->at(creatureIdx)->update();
	}
	return true;
}


void CreatureManager::drawCreatures(void)
{
	const posInfo_t *pPosInfo;
	const creatureResource_t *pResource;
	GLdouble pos_x;
	GLdouble pos_y;
	GLdouble pos_z;
	GLdouble red;
	GLdouble green;
	GLdouble blue;
	GLdouble width_tick = 2;
	GLdouble heigth_tick = 2;

	glBegin(GL_QUADS);

	for(unsigned int creatureIdx = 0u; creatureIdx < m_creatureNum; creatureIdx++){
		/* get position */
		pPosInfo = m_pCreatureList->at(creatureIdx)->getPosition();
		pos_x = ((GLdouble)pPosInfo->xHorPos)/(1 << POS_INFO_DECIMAL);
		pos_y = ((GLdouble)pPosInfo->yHorPos)/(1 << POS_INFO_DECIMAL);
		pos_z = 0;
		/* get creature graphics */
		m_pCreatureList->at(creatureIdx)->getColor(red, green, blue);
		glColor3f( red, green, blue );
		glVertex3d(pos_x				, pos_y				, pos_z					);
		glVertex3d(pos_x + width_tick	, pos_y				, pos_z					);
		glVertex3d(pos_x + width_tick	, pos_y				, pos_z + heigth_tick	);
		glVertex3d(pos_x				, pos_y				, pos_z + heigth_tick	);

		/* get creature resource */
		pResource = m_pCreatureList->at(creatureIdx)->getResource();
		pos_x = (GLdouble)50.0;
		pos_y = (GLdouble)50.0;
		pos_z = (GLdouble)0.0;
		/* health */
		glColor3f( 1.0, 0.0, 0.0 );
		glVertex3d(pos_x				, pos_y														, pos_z	);
		glVertex3d(pos_x + width_tick	, pos_y														, pos_z	);
		glVertex3d(pos_x + width_tick	, pos_y + ((GLdouble)(pResource->pHealth->getValue()))/10	, pos_z	);
		glVertex3d(pos_x				, pos_y + ((GLdouble)(pResource->pHealth->getValue()))/10	, pos_z	);
		/* stamina */
		glColor3f( 0.0, 1.0, 0.0 );
		glVertex3d(pos_x + width_tick		, pos_y														, pos_z	);
		glVertex3d(pos_x + (2 * width_tick)	, pos_y														, pos_z	);
		glVertex3d(pos_x + (2 * width_tick)	, pos_y + ((GLdouble)(pResource->pStamina->getValue()))/10	, pos_z	);
		glVertex3d(pos_x + width_tick		, pos_y + ((GLdouble)(pResource->pStamina->getValue()))/10	, pos_z	);
		/* energy */
		/* stamina */
		glColor3f( 0.0, 0.0, 1.0 );
		glVertex3d(pos_x + (2 * width_tick)	, pos_y													, pos_z	);
		glVertex3d(pos_x + (3 * width_tick)	, pos_y													, pos_z	);
		glVertex3d(pos_x + (3 * width_tick)	, pos_y + ((GLdouble)(pResource->pEnergy->get()))/10	, pos_z	);
		glVertex3d(pos_x + (2 * width_tick)	, pos_y + ((GLdouble)(pResource->pEnergy->get()))/10	, pos_z	);
	}
	glEnd();
}


bool CreatureManager::calcAreaIdx(const spaceSize_t	&size,
										areaIndex_t	&retArea )
{
	bool isSuccess	= false;

	if ((0u < (size.frontLength + size.backLength)) &&
		(0u < (size.leftLength + size.rightLength))) {
		/* calc index to search to area */
		retArea.lowerXIdx	= calcLowerIdx(size.mid.xHorPos, size.leftLength);
		retArea.lowerYIdx	= calcLowerIdx(size.mid.yHorPos, size.frontLength);
		retArea.upperXIdx	= calcUpperIdx(size.mid.xHorPos, size.rightLength, m_fieldWidth);
		retArea.upperYIdx	= calcUpperIdx(size.mid.yHorPos, size.backLength, m_fieldHeight);
		isSuccess			= true;
	}
	return isSuccess;
}


unsigned int CreatureManager::calcLowerIdx( const unsigned int horPos,
											const unsigned int length )
{
	unsigned int initIdx;

	if (horPos < (length << POS_INFO_DECIMAL)) {
		initIdx = CREATURE_MNG_EDGE_POS; 
	} 
	else {
		initIdx = (horPos - (length << POS_INFO_DECIMAL)) >> POS_INFO_DECIMAL;
	}
	return initIdx;
}


unsigned int CreatureManager::calcUpperIdx( const unsigned int horPos,
											const unsigned int length,
											const unsigned int edgeIdx )
{
	unsigned int endIdx	= (horPos + (length << POS_INFO_DECIMAL)) >> POS_INFO_DECIMAL;

	if (edgeIdx < endIdx) {
		endIdx = edgeIdx; 
	}
	return endIdx;
}
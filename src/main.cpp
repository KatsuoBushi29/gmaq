
/*- include -*/
#include <gl/freeglut.h>
#include <memory>

#include "GroundPanel.h"
#include "CreatureManager.h"
#include "FieldManager.h"
#include "Camera.h"


/*- prototype function -*/
void tmp_display(void);
void tmp_rephase(int w, int h);
void tmp_timer(int value);
void tmp_mouseEvent(int button, int state, int x, int y);

void initDisplayParam(void);
void registFunc(void);
void initWindow(void);

static void createFieldManager(void);
static bool createCameraModule(FieldManager &fieldMgr);

void draw2dGrid(void);

/*- gloval variable -*/
std::unique_ptr<GroundPanel> m_panel;
std::unique_ptr<CreatureManager> pTmp_mng;
std::unique_ptr<FieldManager> m_pFieldMng;
std::unique_ptr<Camera> m_pCameraMod;

static cameraParam_t m_cameraParam;
static spatialArea_t m_subjectParam;

GLdouble	G_CENTER_POS_X	= 50.0;
GLdouble	G_CENTER_POS_Y	= 50.0;
GLdouble	G_CENTER_POS_Z	= 0.0;

GLdouble	g_cameraXPos	= (G_CENTER_POS_X + 30.0);
GLdouble	g_cameraYPos	= (G_CENTER_POS_Y + 50.0);
GLdouble	g_cameraZPos	= (G_CENTER_POS_Z + 40.0);
GLdouble	g_cameraXDir	= G_CENTER_POS_X;
GLdouble	g_cameraYDir	= G_CENTER_POS_Y;
GLdouble	g_cameraZDir	= G_CENTER_POS_Z;
GLdouble	g_cameraXTopDir	= 0.0;
GLdouble	g_cameraYTopDir	= 0.0;
GLdouble	g_cameraZTopDir	= 1.0;


/*- main method -*/
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	/* initialize parameter for display */
	initDisplayParam();

	/* regist callback function */
	registFunc();

	/* initialize window */
	initWindow();

	/* test : instance */
	//m_panel = new GroundPanel();
	m_panel.reset(new GroundPanel);
	m_panel->setShape( 2, 2, 1 );
	m_panel->setColor( 0.8, 0.8, 0.8, 0.0);

	/* create CreatureManager */
	spaceSize_t fieldSize;
		fieldSize.frontLength	= 100u;
		fieldSize.backLength	= 0u;
		fieldSize.leftLength	= 100u;
		fieldSize.rightLength	= 0u;
	pTmp_mng.reset(new CreatureManager(1, fieldSize, 0));
	pTmp_mng->initCreateCreatures();

	/* create FieldManager */
	createFieldManager();

	/* create Camera */
	if (false == createCameraModule(*m_pFieldMng)) {
		goto exit_proc;
	}

	/* exec main loop */
	glutMainLoop();

	/* test : delete */

exit_proc:
	
	return 0;
}

void tmp_display(void)
{
	/*** update for user control ***/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/* user's eyesight */
	gluLookAt(g_cameraXPos,		g_cameraYPos,		g_cameraZPos
			, g_cameraXDir,		g_cameraYDir,		g_cameraZDir
			, g_cameraXTopDir,	g_cameraYTopDir,	g_cameraZTopDir );

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*** update interaction : TODO move into main loop ***/
	pTmp_mng->execInteraction();

	/*** redraw object ***/
	m_panel->drawObject( 0, 0, 0 );
	pTmp_mng->drawCreatures();
	m_pCameraMod->draw();
	draw2dGrid();

	/*** update display buffer ***/
	glutSwapBuffers();
	
	return;
}

void tmp_rephase(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)w/(double)h, 1.0, 100.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(g_cameraXPos, g_cameraYPos, g_cameraZPos
			, g_cameraXDir, g_cameraYDir, g_cameraZDir
			, g_cameraXTopDir, g_cameraYTopDir, g_cameraZTopDir);

	return;
}

void tmp_timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(value, tmp_timer, 17);

	return;
}

static int fx = 0;
static int fy = 0;
static bool firstFlg = false;

void tmp_mouseEvent(int button, int state, int x, int y)
{
	windowPos_t		winPos;
	spatialCoord_t	selectPos;

	switch(button){
	case GLUT_LEFT_BUTTON:
		winPos.horPos	= x;
		winPos.verPos	= y;
		/* select object(Creature or Building) */
		selectPos		= m_pCameraMod->get(winPos);
		break;
	case GLUT_RIGHT_BUTTON:
		if(GLUT_DOWN == state){
			fx = x;
			fy = y;
			if(false == firstFlg){
				firstFlg = true;
			}
			else if(true == firstFlg) {
				g_cameraXPos += fx - x;
				g_cameraYPos += fy - y;
			}
		}
		else if(GLUT_UP == state){
			if(true == firstFlg) {
				firstFlg = false;
			}
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		break;
	default :
		break;
	}
}

void initDisplayParam(void)
{
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize (640, 480);
	glutCreateWindow ("GiveMeAQuest");

	return;
}

void registFunc(void)
{
	glutDisplayFunc(tmp_display);
	glutReshapeFunc(tmp_rephase);
	glutMouseFunc(tmp_mouseEvent);
	glutTimerFunc(0, tmp_timer, 17);

	return;
}

void initWindow(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	return;
}


static void createFieldManager(void)
{
	spatialCoord_t pos;
	spatialCoord_t size;

	pos.xValue	= 0u;
	pos.yValue	= 0u;
	pos.zValue	= 0u;
	size.xValue	= 100u;
	size.yValue	= 100u;
	size.zValue	= 100u;
	m_pFieldMng.reset(new FieldManager(pos, size));

	return;
}


static bool createCameraModule(FieldManager &fieldMgr)
{
	bool isSuccess = false;

	spatialCoord_t lowerPos;
	spatialCoord_t upperPos;

	/* set camera parameter */
	m_cameraParam.topDirection.xValue	= 0u;
	m_cameraParam.topDirection.yValue	= 0u;
	m_cameraParam.topDirection.zValue	= 1u;
	m_cameraParam.viewPosition.xValue	= fieldMgr.getCenterPos(FIELD_MGR_DIR_X);
	m_cameraParam.viewPosition.yValue	= fieldMgr.getCenterPos(FIELD_MGR_DIR_Y);
	m_cameraParam.viewPosition.zValue	= fieldMgr.getCenterPos(FIELD_MGR_DIR_Z);
	m_cameraParam.centerPosition.xValue	= m_cameraParam.viewPosition.xValue + 30u;/* TBD */
	m_cameraParam.centerPosition.yValue	= m_cameraParam.viewPosition.yValue + 50u;/* TBD */
	m_cameraParam.centerPosition.zValue	= m_cameraParam.viewPosition.zValue + 40u;/* TBD */
	m_cameraParam.windowSize.width		= 640u;/* TBD */
	m_cameraParam.windowSize.height		= 480u;/* TBD */

	/* set subject parameter */
	lowerPos = fieldMgr.getEdgePos(FIELD_MGR_EDGE_LOWER);
	upperPos = fieldMgr.getEdgePos(FIELD_MGR_EDGE_UPPER);
	m_subjectParam.top.xValue		= lowerPos.xValue;
	m_subjectParam.top.yValue		= lowerPos.yValue;
	m_subjectParam.top.zValue		= 0u;/* TBD */
	m_subjectParam.left.xValue		= lowerPos.xValue;
	m_subjectParam.left.yValue		= upperPos.yValue;
	m_subjectParam.left.zValue		= 0u;/* TBD */
	m_subjectParam.bottom.xValue	= upperPos.xValue;
	m_subjectParam.bottom.yValue	= upperPos.yValue;
	m_subjectParam.bottom.zValue	= 0u;/* TBD */
	m_subjectParam.right.xValue		= upperPos.xValue;
	m_subjectParam.right.yValue		= lowerPos.yValue;
	m_subjectParam.right.zValue		= 0u;/* TBD */

	if (true == fieldMgr.isOverSpatial(m_cameraParam.centerPosition)) {
		/* DUMP : Invalid position for fieldMgr */
		goto exit_proc;
	}

	m_pCameraMod.reset(new Camera(m_cameraParam ,fieldMgr, m_subjectParam));
	isSuccess = true;

exit_proc:

	return isSuccess;
}


void draw2dGrid(void)
{
	double gridLineXLen = 100.0;
	double gridLineYLen = 100.0;
	double lineInterval = 1.0;
	double lineWidth	= 2.0;

	glColor3d(0.8, 0.8, 0.8);
	glBegin(GL_LINES);
	for (double lineYIdx = (G_CENTER_POS_Y - gridLineYLen);
				lineYIdx < (G_CENTER_POS_Y + gridLineYLen);
				lineYIdx+=lineInterval)
	{
		glVertex3d( (G_CENTER_POS_X - gridLineXLen), lineYIdx, 0.0 );
		glVertex3d( (G_CENTER_POS_X + gridLineXLen), lineYIdx, 0.0 );
	}
	for (double lineXIdx = (G_CENTER_POS_X - gridLineXLen);
				lineXIdx < (G_CENTER_POS_X + gridLineXLen);
				lineXIdx+=lineInterval)
	{
		glVertex3d( lineXIdx, (G_CENTER_POS_Y - gridLineYLen), 0.0 );
		glVertex3d( lineXIdx, (G_CENTER_POS_Y + gridLineYLen), 0.0 );
	}
	glEnd();
}

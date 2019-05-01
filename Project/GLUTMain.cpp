
#include "cGame.h"

//Delete console
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

cGame Game;

void AppReshape(int w, int h)
{
	Game.Reshape(w,h);
}
void AppRender()
{
	Game.Render();
}
void AppKeyboard(unsigned char key, int x, int y)
{
	Game.ReadKeyboard(key,x,y,true);
}
void AppKeyboardUp(unsigned char key, int x, int y)
{
	Game.ReadKeyboard(key,x,y,false);
}
void AppSpecialKeys(int key, int x, int y)
{
	Game.ReadSpecialKeyboard(key,x,y,true);
}
void AppSpecialKeysUp(int key, int x, int y)
{
	Game.ReadSpecialKeyboard(key,x,y,false);
}
void AppMouse(int button, int state, int x, int y)
{
	Game.ReadMouse(button,state,x,y);
}
void AppMouseMotion(int x, int y)
{
	Game.ReadMouseMotion(x,y);
}
void AppIdle()
{
	if(!Game.Loop()) exit(0);
}

void main(int argc, char** argv)
{
	int res_x,res_y,pos_x,pos_y;

	//GLUT initialization
	glutInit(&argc, argv);

	//RGBA with double buffer
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);

	//Create centered window
	res_x = glutGet(GLUT_SCREEN_WIDTH);
	res_y = glutGet(GLUT_SCREEN_HEIGHT);
	pos_x = (res_x>>1)-(SCREEN_WIDTH>>1);
	pos_y = (res_y>>1)-(SCREEN_HEIGHT>>1);
	
	glutInitWindowPosition(pos_x,pos_y);
	glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
	glutCreateWindow("The Ballenger");
	glutFullScreen();

	/*glutGameModeString("800x600:32");
	glutEnterGameMode();*/

	//Make the default cursor disappear
	glutSetCursor(GLUT_CURSOR_NONE);

	//Register callback functions
	glutReshapeFunc(AppReshape);
	glutDisplayFunc(AppRender);			
	glutKeyboardFunc(AppKeyboard);		
	glutKeyboardUpFunc(AppKeyboardUp);	
	glutSpecialFunc(AppSpecialKeys);	
	glutSpecialUpFunc(AppSpecialKeysUp);
	glutMouseFunc(AppMouse);
    glutMotionFunc(AppMouseMotion);
    glutPassiveMotionFunc(AppMouseMotion);
	glutIdleFunc(AppIdle);

	//GLEW initialization
	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		printf("ERROR: %s\n",glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
	}

	//Game initializations
	Game.Init(1);

	//Application loop
	glutMainLoop();	
}

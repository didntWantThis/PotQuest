#include <windows.h>
#include "Game.h"
#include "Includes.h"

/******************************************/
/********** GLOBAL VARIABLES **************/
/******************************************/


Game *theGame;

void TimerCallbackFunction(int value)
{
	theGame->update();		
	//HAVE TO SET THE FRAME RATE AND REDISPLAY WITH SFML------------------------------------------------------------------------------------------------------
	//glutPostRedisplay();
	//glutTimerFunc(FRAME_DELAY_SPRITE,TimerCallbackFunction,0);
}

void WindowReshapeCallbackFunction(int w,int h){}//TODO make this funtion-------------------------------------------------------------------------------------

int main()
{
	//init my game window
	/*sf::Window App(sf::VideoMode(WINDOW_SCREEN_WIDTH,WINDOW_SCREEN_HEIGHT,32),"Pot Quest");
	App.SetFramerateLimit(FRAMES_PER_SECOND);
	App.UseVerticalSync(isVerticalSync);	*/

	/* init the game */
	theGame = new Game();
	theGame->setNewWindowSize(theGame->screenInfo.WINDOW_WIDTH,theGame->screenInfo.WINDOW_HEIGHT);
	theGame->initializeGame();

	//main game loop
	while (theGame->App->IsOpened()){
		theGame->deltaT = theGame->App->GetFrameTime();
		theGame->InputHandler();		

		theGame->update();
		theGame->Draw();
	}
	return 0;
}
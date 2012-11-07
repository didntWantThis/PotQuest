#pragma once

#include "Includes.h"
#include "Properties.h"
#include "Mesh.h"
#include "Model.h"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Window/WindowSettings.hpp>

typedef struct _ScreenInfo{
	//values for the window
	unsigned short WINDOW_WIDTH;
	unsigned short WINDOW_HEIGHT;
	GLfloat aspectRatio;
	GLfloat fov, zNear, zFar;
}ScreenInfo;


#define FRAMES_PER_SECOND 60
const int FRAME_DELAY_SPRITE=1000/FRAMES_PER_SECOND;

enum {
	STATE_GAMEPLAY=0, 
	STATE_MAINMENU, 
	STATE_CREDITS
};

typedef struct _CameraInfo
{
	GLfloat eX,eY,eZ;
	GLfloat cX,cY,cZ;
	GLfloat uX,uY,uZ;
}CameraInfo;

//input information
typedef struct _InputInfo
{
	bool mouseDown; // is the mouse down?
	int button; // which mouse button
	float clickX,clickY; // where the mouse was clicked
	float currentX,currentY;
}InputInfo;

// convenience structure to hold rgb values
typedef struct _RGBColor
{
	float red,green,blue;
}RGBColor;

// GameStateInfo
// this stores anything related to the state of the game
// i.e. what level are we on?, what is the score? etc.
typedef struct _GameStateInfo
{
	int gameState; // the game state, see enum's above
	//RGBColor bgClearColor; // the default clear color of the background

	// window width/height are the actual size of the window
	int windowWidth, windowHeight;

	// screen width/height are the apparent size of the window
	// i.e. you can have a 640x480 game screen stretched to 1280x1024
	// your calculations for actual pixel locations will depend on the ratio
	//   between screen and window width/height
	int screenWidth, screenHeight;

	float ratioWidth,ratioHeight;
}GameStateInfo;

class Game
{
public:
	Game(void);
	~Game(void);

	void initializeGame();
	void Draw(); // called from the main

	void DrawElements();

	/* update routines, the game loop */
	void update(); // called from main frequently

	void addToDrawList(Model *m);

	/* input callback function */
	void InputHandler();
	void resizeScreen();

	void drawFloor();

	// convenience functions 
	// screen size is the apparent size in pixels
	void setScreenSize(int w, int h)
	{
		stateInfo.screenWidth = w;
		stateInfo.screenHeight = h;
	}

	// sets the window size in pixels for the window itself
	void setNewWindowSize(int width,int height)
	{
		stateInfo.windowWidth = width;
		stateInfo.windowHeight = height;
	}

	/*****************************************************/
	/******************  Vareables  **********************/
	/*****************************************************/

	float deltaT;

	/* game state info */
	GameStateInfo stateInfo;

	InputInfo input;
	ScreenInfo screenInfo;
	CameraInfo camera;

	//this is the draw array
	std::vector<Model*> meshDrawList;

	/* timer's for rendering and animation/physics update */
	sf::Clock *renderingTimer;
	sf::Clock *updateTimer; // for physics/collisions etc.

	//sf handlers
	sf::Window *App;
	sf::WindowSettings *winSetting;

	//lights
	/*GLfloat AmbientLightValues[4];

	GLfloat LightAmbient[4];
	GLfloat LightDiffuse[4];
	GLfloat LightPosition[4];*/

	// Objects
	Model *player, *player2;
	Model *floor;
};


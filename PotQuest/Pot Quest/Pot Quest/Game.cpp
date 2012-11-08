#include "Game.h"

void drawCube (float w, float h, float d);

GLfloat AmbientLightValues[]={1,1,1,1};

GLfloat LightAmbient[]={1,1,1,1};
GLfloat LightDiffuse[]={0.5,0.5,0.5,1};
GLfloat LightPosition[]={100,0,0,1};

//temp image stuff
sf::Image img_data;
GLuint texture_handle;
GLuint texture;


float posX,posY;

Game::Game(){
	/* init state */
	stateInfo.gameState = STATE_GAMEPLAY;
	renderingTimer = new sf::Clock();
	updateTimer = new sf::Clock();
	screenInfo.WINDOW_WIDTH = 1280;
	screenInfo.WINDOW_HEIGHT = 720;
	screenInfo.aspectRatio = GLfloat(screenInfo.WINDOW_WIDTH)/GLfloat(screenInfo.WINDOW_HEIGHT);
	screenInfo.fov = 70.0f, screenInfo.zNear = 1.0f, screenInfo.zFar = 1000.0f;
	resizeScreen();
}


Game::~Game(void)
{
}


void Game::initializeGame(){
	//setting up the screen

	App = new sf::Window(sf::VideoMode(screenInfo.WINDOW_WIDTH,screenInfo.WINDOW_HEIGHT,32),"Pot Quest");
	//App->SetFramerateLimit(FRAMES_PER_SECOND);
	App->EnableKeyRepeat(false);
	winSetting = new sf::WindowSettings();
	winSetting->AntialiasingLevel = 2;

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLightValues);
	glEnable(GL_LIGHTING);

	posX = 0.0f;
	posY = 0.0f;

	glLightfv(GL_LIGHT1,GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1,GL_POSITION, LightPosition);
	glEnable(GL_LIGHT1);// Enable Light One

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);							//enable texture
	//load texture from file
	img_data.LoadFromFile ("Images/checker.jpg");
	glGenTextures(1, &texture_handle);//how many, the handler
	glBindTexture(GL_TEXTURE_2D,texture_handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_data.GetWidth(),
		img_data.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data.GetPixelsPtr());

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	//init camera
	camera.eX = 0.0f;
	camera.eY = -5.0f;
	camera.eZ = 0.0f;
	camera.cX = 0.0f;
	camera.cY = 0.0f;
	camera.cZ = 0.0f;
	camera.uX = 0;
	camera.uY = 1;
	camera.uZ = 0;

	player = new Model("models/nachoman.obj");
	floor = new Model("models/floor.obj");
	this->addToDrawList(player);
	this->addToDrawList(floor);
}

void Game::Draw(){
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluPerspective(screenInfo.fov, screenInfo.aspectRatio, screenInfo.zNear, screenInfo.zFar); // reset how it all looks
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLightfv();
	//light position

	gluLookAt(camera.eX,camera.eY,camera.eZ,camera.cX,camera.cY,camera.cZ,camera.uX,camera.uY,camera.uZ);	
	//gluLookAt(0,0,-10,0,0,0,0,1,0);


	/*glPushMatrix();
		std::vector<Model*>::iterator it; 
		for(it=meshDrawList.begin(); it != meshDrawList.end();it++)
		{
			Model *s = (*it);
			s->Draw();
		}
	glPopMatrix();*/

	player->Draw();
	glBindTexture(GL_TEXTURE_2D, texture_handle);
	//floor->Draw();
	glColor4f(0.5f, 0.3f, 0.2f, 1.0f);
	glBegin(GL_QUADS);
		glNormal3f( 0.0f, 1.0f, 0.0f);
	    glTexCoord2f(1.0f, 1.0f); glVertex3f(-500.0, -5.0, 500.0);
	    glTexCoord2f(1.0f, 0.0f); glVertex3f( 500.0, -5.0, 500.0);
	    glTexCoord2f(0.0f, 0.0f); glVertex3f( 500.0, -5.0,-500.0);
	    glTexCoord2f(0.0f, 1.0f); glVertex3f(-500.0, -5.0,-500.0);
	glEnd();
	
	this->App->Display();
}

void Game::update(){
	//update objects
	player->update(deltaT);

	//update camera
	camera.eX = player->position.x;
	camera.eY = player->position.y + 15;
	camera.eZ = player->position.z - 20;

	camera.cX = player->position.x;
	camera.cY = player->position.y;
	camera.cZ = player->position.z;
}

void Game::addToDrawList(Model *m){
	if(m)
		//adds the element to the draw list
		this->meshDrawList.push_back(m);
}

void Game::resizeScreen(){
	glViewport(0,0, screenInfo.WINDOW_WIDTH, screenInfo.WINDOW_HEIGHT);    // resize window
	screenInfo.aspectRatio = GLfloat(screenInfo.WINDOW_WIDTH)/GLfloat(screenInfo.WINDOW_HEIGHT); // redefine aspect ratio
	glMatrixMode(GL_PROJECTION);    // Switch to projection matrix to manipulate view
	gluPerspective(screenInfo.fov, screenInfo.aspectRatio, screenInfo.zNear, screenInfo.zFar); // reset how it all looks
	glMatrixMode(GL_MODELVIEW);     // switch back to Modelview matrix
}

void Game::InputHandler(){
	sf::Event Event;
	static const sf::Input& Input = App->GetInput();
	while (App->GetEvent(Event)){
		if (Event.Type == sf::Event::Closed)
			App->Close();
		if (Event.Type == sf::Event::Resized)
		{
			screenInfo.WINDOW_WIDTH = Event.Size.Width;     // Set new width
			screenInfo.WINDOW_HEIGHT = Event.Size.Height;     // Set new height
			resizeScreen();
		}
		// Button event, occurs one time based on key press
		if (Event.Type == sf::Event::KeyPressed && Input.IsKeyDown(sf::Key::Escape))
			this->App->Close();

		//keyInputs
		if (Input.IsKeyDown(sf::Key::Left)){
			player->velocity.setX (10);
			if (player->acceleration.getX() < 5)
				player->acceleration.setX(player->acceleration.getX() + 0.1);
		}else if (Input.IsKeyDown(sf::Key::Right)){
			player->velocity.setX (-10);
			if (player->acceleration.getX() < 5)
				player->acceleration.setX(player->acceleration.getX() - 0.1);
		}else{
			player->velocity.setX (0);
			player->acceleration.setX(0);
		}
		
		if (Input.IsKeyDown(sf::Key::Up)){
			player->velocity.setZ (10);
			if (player->acceleration.getZ() < 5)
				player->acceleration.setZ(player->acceleration.getZ() + 0.1);
		}else if (Input.IsKeyDown(sf::Key::Down)){
			player->velocity.setZ (-10);
			if (player->acceleration.getZ() < 5)
				player->acceleration.setZ(player->acceleration.getZ() - 0.1);
		}else{
			player->velocity.setZ (0);
			player->acceleration.setZ(0);
		}
	}//while
}

void Game::drawFloor(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_QUADS);
		glColor4f(1.0f,1.0f,1.0f,1.0f);
		glVertex3f(-1000.0f, 10.0f,-1000.0f);
		glVertex3f(-1000.0f, 10.0f, 1000.0f);
		glVertex3f( 1000.0f, 10.0f, 1000.0f);
		glVertex3f( 1000.0f, 10.0f,-1000.0f);
	glEnd();
}
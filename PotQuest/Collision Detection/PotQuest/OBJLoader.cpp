#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <GL\GL.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/String.hpp>

using namespace std;

GLfloat AmbientLightValues[] = {1.0f,1.0f,1.0f,1.0f};

GLfloat LightAmbient[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]=	{ 0.0f, 0.0f, 10.0f, 1.0f };

GLfloat xspeed = 0.0f;
GLfloat yspeed = 0.0f;

int attackTimer = 0;

bool MoveLeft = false;
bool MoveRight = false;
bool MoveUp = false;
bool MoveDown = false;

int colliders = 0;

std::string player = "nachoman.obj";
std::string enemy = "PlaceholderEnemy.obj";

#pragma region MODEL_SECTIONS
class Vertex
{
public:
	//similar to normals class
	//makes a vector
	float x,y,z;
	float magnitude;
	float distance;
	Vertex()
	{
		x=y=z=0;
	}
	~Vertex(){}
	//literally an empty class
	float Magnitude()
	{
		return sqrtf(x*x+y*y+z*z);
	}


	Vertex(float x1, float y1, float z1)
	{
		this->x =x1;
		this->y = y1;
		this->z = z1;
	}

	void Normalize()
	{
		magnitude = this->Magnitude();
		x/=magnitude;
		y/=magnitude;
		z/=magnitude;
	}

	float Distance(float _x, float _y, float _z)
	{

		return sqrtf(powf(_x-this->x,2) - powf(_y-this->y,2) - powf(_z - this->z,2));
	}

};
class Face
{
public:
	std::vector<int> texture,normals,vertices, boundingfaces;

	Face(){}; //does  :nothing
	~Face(){}

};
class Texture
	//holds the texture co-ordinates of the object
{
public:
	float u,v;
	Texture (float x, float y)
	{
		this->u = x;
		this->v =y;
	}

	Texture()
	{
		u=v=0;
	}
};
class Normals
{
public:
	//Normals file
	//used for lighting
	//very important
	float x,y,z; //nearly all of these will have this
	//is a normal vector
	Normals(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Normals()
	{
		x=y=z=0;
	}
};
#pragma endregion

class Model
{
public:


	std::vector<Vertex> vertices;
	std::vector<Normals> normals;
	std::vector<Texture> texture;
	std::vector<Face> faces;
	std::vector<Model*> keyframes;
	std::vector<Vertex> TargetModel;
	float xhigh,xlow,zhigh,zlow,yhigh,ylow;
	float xPos, yPos, zPos;//I have no idea where this thing is being drawn
	float hitLeft, hitRight, hitUp, hitDown;
	std::vector<Vertex> OriginalVertices;
	GLuint Texture;
	int health;
	bool canDamage, canDie;
	
	Model(float x,float y,float z, float size, bool destructible, bool doesDamage, int setHealth)
	{
		xPos = x;
		yPos = y;
		zPos = z;
		hitLeft = xPos + size/2;
		hitRight = xPos - size/2;
		hitUp = yPos + size;//(too much)
		hitDown = yPos;//minor intersect, is fine
		health = setHealth;
		canDamage = doesDamage;
		canDie = destructible;
	}
	~Model()
	{
		this->vertices.clear();
		this->normals.clear();
		this->texture.clear();
		this->keyframes.clear();
		this->TargetModel.clear();
		std::cout<<"Object Deleted"<<std::endl;
		//move hit box off screen because it will still collide
		this->hitDown = -10000;
		this->hitLeft = -10000;
		this->hitUp = -10000;
		this->hitRight = -10000;
		this->canDamage = false;
		this->canDie = false;
	}

	//Model must be loaded in prior to adding keyframe in
	void AddkeyFrame(Model *M)
	{
		this->keyframes.push_back(M);
	}

	//Draws the Model And Textures it
	void Draw()
	{
		int unsigned i = 0;
		glBegin(GL_TRIANGLES);
		glBindTexture(GL_TEXTURE_2D, Texture);
		//Draw anything that has 3 vertices
		while (i < this->faces.size() && this->faces[i].vertices.size() ==3)
		{
			for (int j=0; j!=3; j++)
			{
				glColor3f(0.5f,0.5f,0.5f);
				glTexCoord2f(this->texture[this->faces[i].texture[j]].u, this->texture[this->faces[i].texture[j]].v);
				glMatrixMode(GL_MODELVIEW);
				glNormal3f(this->normals[this->faces[i].normals[j]].x,
						   this->normals[this->faces[i].normals[j]].y,
						   this->normals[this->faces[i].normals[j]].z);

				glVertex3f(this->vertices[this->faces[i].vertices[j]].x,
						   this->vertices[this->faces[i].vertices[j]].y,
						   this->vertices[this->faces[i].vertices[j]].z);
			}
			i++;
		}
		
		glEnd();
	}

	//Scale the Model
	//Does not actually work
	void Scale(float size)
	{
		for (int i=0; i!= vertices.size(); i++)
		{
			vertices[i].x/=size;
			vertices[i].y/=size;
			vertices[i].z/=size;

			OriginalVertices[i].x/=size;
			OriginalVertices[i].y/=size;
			OriginalVertices[i].z/=size;
		}

		xhigh /=size;
		xlow  /=size;
		zhigh /=size;
		zlow  /=size;
		yhigh /=size;
		ylow  /=size;
	}

	//Loads in a Texture using DevIL
	void AddTexture(char *FileName)
	{
		static GLubyte Texture;
		/*Texture = ilutGLLoadImage(FileName);
		glBindTexture(GL_TEXTURE_2D,Texture);*/
		this->Texture = Texture;
	}


};


class ObjectLoader
{
	std::clock_t start;

public:

	ObjectLoader()
	{

	}

	inline void LoadObject(std::string file, Model *m)
	{
		start = clock();
		/*ifstream input (file.c_str());
		string buffer;*/
		//loading prompt

		std::cout << "loading: " << file << std::endl;

		ifstream input (file);

		if (!input)
		{
			std::cout<<"File invalid"<<std::endl;
			return;
		}

		short f = 0;
		char buf [256];


		while (input.getline(buf,256))
		{
			switch (buf[0]){
			case 'v':
				static float x,y,z,u,v;
				switch (buf[1]){
				case' ':
					sscanf(buf, "v  %f %f %f", &x,&y,&z);
					if(x>=m->xhigh)	m->xhigh = x;
					if(y>=m->yhigh)	m->yhigh = y;
					if(z>=m->zhigh)	m->zhigh = z;

					if(x<=m->xlow) m->xlow = x;
					if(y<=m->ylow) m->ylow = y;
					if(z<=m->zlow)	m->zlow = z;
					m->vertices.push_back(Vertex(x,y,z));
					break;
				case 't':
					sscanf(buf, "vt %f &f", &u,&v);
					m->texture.push_back(Texture(u,v));
					break;
				case'n':
					sscanf(buf, "vn %f %f %f", &x,&y,&z);
					m->normals.push_back(Normals(x,y,z));
					break;
				}
				break;
			case 'f':
				static short vertexIndex[3],uvIndex[3],normalIndex[3];
				static short matches;
				matches = sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d",
					&vertexIndex[0], &uvIndex[0], &normalIndex[0],
					&vertexIndex[1], &uvIndex[1], &normalIndex[1],
					&vertexIndex[2], &uvIndex[2], &normalIndex[2]);

				if (matches != 9){
					std::cout << "ERROR: Could not open file: " << file << std::endl;
					
				}

				m->faces.push_back(Face());
				//faces.push_back(triangle());
				m->faces[f].vertices.push_back(vertexIndex[0]-1);
				m->faces[f].vertices.push_back(vertexIndex[1]-1);
				m->faces[f].vertices.push_back(vertexIndex[2]-1);
				m->faces[f].texture.push_back(uvIndex[0]-1);
				m->faces[f].texture.push_back(uvIndex[1]-1);
				m->faces[f].texture.push_back(uvIndex[2]-1);
				m->faces[f].normals.push_back(normalIndex[0]-1);
				m->faces[f].normals.push_back(normalIndex[1]-1);
				m->faces[f].normals.push_back(normalIndex[2]-1);
				f++;

				break;

			}
		}
		cout<<"Object successfully loaded"<<endl;
		cout<<( (clock() - start) / (double)CLOCKS_PER_SEC)<<endl;
		m->OriginalVertices = m->vertices;
	}//End of object loader method
};

void init()
{
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLightValues);
	glEnable(GL_LIGHTING);
	//set up first red light
	glLightfv(GL_LIGHT1,GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1,GL_POSITION, LightPosition);
	glEnable(GL_LIGHT1);// Enable Light One

	//glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
}

bool collide(Model *player, Model *enemy)
{
	if (player->hitLeft > enemy->hitRight && player->hitRight < enemy->hitLeft)//colliding from left
	{
		//check if y intersect
		if (player->hitUp > enemy->hitDown && player->hitDown < enemy->hitUp)//colliding from below
			return true;
		else if (player->hitDown < enemy->hitUp && player->hitUp > enemy->hitDown)//colliding from above
			return true;
		else
			return false;
	}
	else if (player->hitRight < enemy->hitLeft && player->hitLeft > enemy->hitRight)//colliding from right
		if (player->hitUp > enemy->hitDown && player->hitDown < enemy->hitUp)//colliding from below
			return true;
		else if (player->hitDown < enemy->hitUp && player->hitUp > enemy->hitDown)//colliding from above
			return true;
		else
			return false;
	else
		return false;
}
void attack(Model *player, Model *target)
{
	int attackRadius = 2;

	//temporarily up hit box
	player->hitDown += attackRadius;
	player->hitUp += attackRadius;
	player->hitLeft += attackRadius;
	player->hitRight += attackRadius;

	if (collide(player,target))
	{
		target->health -= 1;
		cout<<"target health: "<<target->health<<"\n";
	}

	//reduce hit box
	player->hitDown -= attackRadius;
	player->hitUp -= attackRadius;
	player->hitLeft -= attackRadius;
	player->hitRight -= attackRadius;

	if (target->health == 0)
		target->~Model();
}

int main()
{

	ObjectLoader *c = new ObjectLoader();
	Model *p = new Model(0,0,0,7,false,false,10);//Size = magic number, and broken
	Model *e = new Model(10,10,0,7,true,true,10);
	//Model *b = new Model();
	//Model *l = new Model();

	c->LoadObject(player,p);
	c->LoadObject(player,e);
	colliders ++;
	//m->AddTexture("balloonTexture.bmp");

	// Create the main window
	sf::Window App(sf::VideoMode(800, 800, 32), "Pot Quest",2);//, sf::Style::Fullscreen, 2); // 2 levels of antialiasing
	init(); //Init OpenGL states 

	sf::Event Event;

	// Get a reference to the input manager
	const sf::Input& Input = App.GetInput();


	///// MAIN LOOP /////
	while (App.IsOpened())
	{
		//Move on arrow keys
		if (Input.IsKeyDown(sf::Key::Left))
			MoveLeft = true;
		if (Input.IsKeyDown(sf::Key::Right))
			MoveRight = true;
		if (Input.IsKeyDown(sf::Key::Up))
			MoveUp = true;
		if (Input.IsKeyDown(sf::Key::Down))
			MoveDown = true;

		//Attack on Mouse Click
		if (Input.IsMouseButtonDown(sf::Mouse::Left))
		{
			//cannot move while attacking
			MoveUp = false;
			MoveDown = false;
			MoveLeft = false;
			MoveRight = false;

			if (e->canDie == true && attackTimer > 10)
			{
				attack(p,e);//must find way to automatically run for all models where canDie == true
				attackTimer=0;
			}
		}
		//Stop moving when arrow key released
		if (!Input.IsKeyDown(sf::Key::Left))
			MoveLeft = false;
		if (!Input.IsKeyDown(sf::Key::Right))
			MoveRight = false;
		if (!Input.IsKeyDown(sf::Key::Up))
			MoveUp = false;
		if (!Input.IsKeyDown(sf::Key::Down))
			MoveDown = false;

		while (App.GetEvent(Event))
		{
			// Close window : exit
			if (Event.Type == sf::Event::Closed)
				App.Close();

			// Escape key : exit
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
				App.Close();

			// Resize event : adjust viewport
			if (Event.Type == sf::Event::Resized) {
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glViewport(0, 0, Event.Size.Width, Event.Size.Height);
				gluPerspective(90.f, (GLfloat)Event.Size.Width/(GLfloat)Event.Size.Height, 1.f, 500.f);
			}

		}

		App.SetActive();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Setup a perspective projection
		glViewport(0, 0, 800, 800);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		gluPerspective(45.f, 1.f, 1.f, 1000.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		

		//gluLookAt(0,4,-10,0,4,0,0,1,0);//Baseline (camera too close)
		gluLookAt(0,4,-100,0,4,0,0,1,0);

		if (MoveLeft == true)
		{
			p->xPos+=1;
			p->hitLeft+=1;
			p->hitRight+=1;
		}
		else if (MoveRight == true)
		{
			p->xPos-=1;
			p->hitLeft-=1;
			p->hitRight-=1;
		}
		if (MoveUp == true)
		{
			p->yPos+=1;
			p->hitUp+=1;
			p->hitDown+=1;
		}
		else if (MoveDown == true)
		{
			p->yPos-=1;
			p->hitUp-=1;
			p->hitDown-=1;
		}

		if (!collide(p,e))
		{
			glPushMatrix();//Player
				glTranslatef(p->xPos, p->yPos, 0.f);
				p->Draw();
			glPopMatrix();
		}else
		{
			//combat!!
			cout<<"collision detected\n";
			//undo overlap
			if (e->canDamage == true)
			{
				p->health -= 1;
				cout<<"Player Health: "<<p->health<<"\n";
				if(p->health == 0)
					exit(0);
			}
			if (MoveLeft == true)
			{
				p->xPos-=1;
				p->hitLeft-=1;
				p->hitRight-=1;
			}
			else if (MoveRight == true)
			{
				p->xPos+=1;
				p->hitLeft+=1;
				p->hitRight+=1;
			}
			if (MoveUp == true)
			{
				p->yPos-=1;
				p->hitUp-=1;
				p->hitDown-=1;
			}
			else if (MoveDown == true)
			{
				p->yPos+=1;
				p->hitUp+=1;
				p->hitDown+=1;
			}
			glPushMatrix();//Player
				glTranslatef(p->xPos, p->yPos, 0.f);
				p->Draw();
			glPopMatrix();
		}

		glPushMatrix();//Enemy
			glTranslatef(e->xPos, e->yPos, 0.f);
			e->Draw();
		glPopMatrix();
		


		// Finally, display rendered frame on screen
		App.Display();
		attackTimer++;
		cout<<attackTimer<<endl;
		if(attackTimer > 1000)
			attackTimer = 10;
	}

	return EXIT_SUCCESS;


	//getchar();

}

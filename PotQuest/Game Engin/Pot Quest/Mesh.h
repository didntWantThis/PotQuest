#pragma once
#include "Includes.h"
#include "Properties.h"

class Mesh
{
public:
	Mesh(void);
	~Mesh(void);


	//Model must be loaded in prior to adding keyframe in
	void AddkeyFrame(Mesh *M);
	void Draw();
	void Scale(float size);
	void AddTexture(char *FileName);
	void LoadObject(std::string file);


	//vars
	std::vector<Vertex> vertices;
	std::vector<Normals> normals;
	std::vector<Texture> texture;
	std::vector<Face> faces;
	std::vector<Mesh*> keyframes;
	std::vector<Vertex> TargetModel;
	float xhigh,xlow,zhigh,zlow,yhigh,ylow;
	std::vector<Vertex> OriginalVertices;
	GLuint TextureInt;
};


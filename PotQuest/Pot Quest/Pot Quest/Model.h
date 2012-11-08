#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Mesh.h"
#include "Properties.h"
#include "Quaternion.h"

class Model
{
public:
	Model(void);
	Model(std::string file);
	~Model(void);

	void Draw();
	void update(float deltaT);
	void LoadObject(std::string file);

	Vector3 position;
	Vector3 velocity, acceleration, force;
	Quaternion orentation;

	Vector3 u,d,p,e;

	std::vector<Mesh*> KeyframeList;
	Mesh *currentMesh;
	int currentMeshIndex;
};
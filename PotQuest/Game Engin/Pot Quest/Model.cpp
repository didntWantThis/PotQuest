#include "Model.h"

Model::Model(void){
}

Model::Model(std::string file){
	currentMesh = new Mesh();
	currentMesh->LoadObject(file);
	KeyframeList.push_back(currentMesh);
	currentMeshIndex = 0;
}

Model::~Model(void)
{
}
void Model::LoadObject(std::string file){
	currentMesh->LoadObject(file);
}

void Model::Draw(){
	glPushMatrix();
		//glTranslatef (position.getX(),position.getY(), position.getZ());
		glTranslatef(position.x, position.y, position.z); //less function calls the better
		KeyframeList[currentMeshIndex]->Draw();
	glPopMatrix();
	//std::cout << position.getX() << " " << position.getY() << " " << position.getZ() << std::endl;
}

void Model::update(float deltaT){
	//physics
	velocity = velocity + acceleration * deltaT;
	position = position + velocity * deltaT;
	//collision
	//floor
	//hibox update
}

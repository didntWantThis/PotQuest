#include "Model.h"

const Vector3 constUp(0,1,0);

Model::Model(void){
}

Model::Model(std::string file){
	currentMesh = new Mesh();
	currentMesh->LoadObject(file);
	KeyframeList.push_back(currentMesh);
	currentMeshIndex = 0;
	d.set(0,0,1);

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
		//KeyframeList[currentMeshIndex]->Draw();
		currentMesh->Draw();
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

void Model::addKeyFrame(std::string file){
	Mesh *m = new Mesh ();
	m->LoadObject(file);
	KeyframeList.push_back(m);
}

void Model::lerp(Mesh *previous, Mesh *current, float deltaT){
for (int i = 0 ; i < previous->vertices.size() ; i++){
	 currentMesh->vertices[i].x = (previous->vertices[i].x*(1-deltaT)) + (current->vertices[i].x*deltaT);
	 currentMesh->vertices[i].y = (previous->vertices[i].y*(1-deltaT)) + (current->vertices[i].y*deltaT);
	 currentMesh->vertices[i].z = (previous->vertices[i].z*(1-deltaT)) + (current->vertices[i].z*deltaT);
 }
}

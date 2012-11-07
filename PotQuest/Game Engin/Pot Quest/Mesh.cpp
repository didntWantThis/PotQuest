#include "Mesh.h"


Mesh::Mesh(void)
{
}


Mesh::~Mesh(void)
{
	this->vertices.clear();
	this->normals.clear();
	this->texture.clear();
	this->keyframes.clear();
	this->TargetModel.clear();
	std::cout<<"Object Deleted"<<std::endl;
}

void Mesh::AddkeyFrame(Mesh *M)
{

	this->keyframes.push_back(M);
}

void Mesh::Draw()
{
	glMatrixMode(GL_MODELVIEW);
	glBegin(GL_TRIANGLES);
	//glBegin(GL_LINES);
	//glBindTexture(GL_TEXTURE_2D, TextureInt);
	//Draw anything that has 3 vertices
	for (unsigned int i = 0, n = faces.size(); i < n; i++)
	{
		for (int j=0; j!=3; j++){
			glColor3f(0.5f,0.5f,0.5f);

			//here you're reading a lot from the vectors and stuff.
			//
			
			glNormal3f(this->normals[this->faces[i].normals[j]].x, this->normals[this->faces[i].normals[j]].y, this->normals[this->faces[i].normals[j]].z);
			
			glTexCoord2f(this->texture[this->faces[i].texture[j]].u, this->texture[this->faces[i].texture[j]].v);
			
			glVertex3f(this->vertices[this->faces[i].vertices[j]].x, this->vertices[this->faces[i].vertices[j]].y, this->vertices[this->faces[i].vertices[j]].z);
		}
	}
	glEnd();
}

//Scale the Model
void Mesh::Scale(float size)
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
void Mesh::AddTexture(char *FileName)
{
	//static GLubyte Texture;
	/*Texture = ilutGLLoadImage(FileName);
	glBindTexture(GL_TEXTURE_2D,Texture);*/
	//this->Texture = Texture;
}

void Mesh::LoadObject(std::string file){
	std::clock_t start;
	start = clock();

	std::cout << "loading: " << file << std::endl;

	std::ifstream input (file);

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
				if(x>=this->xhigh)	this->xhigh = x;
				if(y>=this->yhigh)	this->yhigh = y;
				if(z>=this->zhigh)	this->zhigh = z;

				if(x<=this->xlow) this->xlow = x;
				if(y<=this->ylow) this->ylow = y;
				if(z<=this->zlow)	this->zlow = z;
				this->vertices.push_back(Vertex(x,y,z));
				break;
			case 't':
				sscanf(buf, "vt %f &f", &u,&v);
				this->texture.push_back(Texture(u,v));
				break;
			case'n':
				sscanf(buf, "vn %f %f %f", &x,&y,&z);
				this->normals.push_back(Normals(x,y,z));
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

			this->faces.push_back(Face());
			//faces.push_back(triangle());
			this->faces[f].vertices.push_back(vertexIndex[0]-1);
			this->faces[f].vertices.push_back(vertexIndex[1]-1);
			this->faces[f].vertices.push_back(vertexIndex[2]-1);
			this->faces[f].texture.push_back(uvIndex[0]-1);
			this->faces[f].texture.push_back(uvIndex[1]-1);
			this->faces[f].texture.push_back(uvIndex[2]-1);
			this->faces[f].normals.push_back(normalIndex[0]-1);
			this->faces[f].normals.push_back(normalIndex[1]-1);
			this->faces[f].normals.push_back(normalIndex[2]-1);
			f++;

			break;

		}
	}
	std::cout<<"Object successfully loaded"<<std::endl;
	std::cout<<( (clock() - start) / (double)CLOCKS_PER_SEC)<<std::endl;
	this->OriginalVertices = this->vertices;

	input.close();
}
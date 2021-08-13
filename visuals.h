#ifndef VISUALS_H
#define VISUALS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <random>

static float lerandfunc(float i1, float i2);
static int lerandfunc(int i1, int i2);


class graphics
{
public:
	GLuint pVBO, pVAO; //create vertex buffer and vertex array objects
	GLuint VSOID, FSOID; //vertex shader ID, fragment shader ID
	GLuint programID;

	graphics();

	void installshaders();
	
	bool checkshaderandprogramstatus(GLuint shaderID, GLuint shaderID2, GLuint programID);


	std::string readshadercode(const char* filename);
	

};


class galaxy {
private:

	int numvertexattributes = 3;
	static const unsigned int sizeOfArray = 30000;

public:

	galaxy();

	float r, g, b;

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 col;
	};

	Vertex* pCloud = new Vertex[sizeOfArray];

	void setprimarycolor();

	int getSOA();

	void makegalaxy();

};


static float lerandfunc(float i1, float i2)
{


	const float MIN_RAND = i1, MAX_RAND = i2;
	const float range = MAX_RAND - MIN_RAND;
	float random = range * ((((float)rand()) / (float)RAND_MAX)) + MIN_RAND;

	return random;
}

static int lerandfunc(int i1, int i2)
{

	const int MIN_RAND = i1, MAX_RAND = i2;
	const int range = MAX_RAND - MIN_RAND;
	int random = range * ((((float)rand()) / (int)RAND_MAX)) + MIN_RAND;

	return random;
}

#endif

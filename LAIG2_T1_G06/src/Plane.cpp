#include "Plane.h"

void Plane::draw(float texS, float texT)
{
	float div = v.at(0);

	GLfloat ctrlpoints[4][3] = { {-0.5, 0.0, 0.5},
								 {-0.5, 0.0 ,-0.5}, 
								 {0.5, 0.0, 0.5},
								 {0.5, 0.0, -0.5}};

	GLfloat normalpoints[4][3] = {{0.0, 0.0, 1.0},
								  {0.0, 0.0, 1.0}, 
								  {0.0, 0.0, 1.0},
								  {0.0, 0.0, 1.0}};

	GLfloat texturepoints[4][2] = {{0.0, 0.0},
								   {0.0, 1.0/texT}, 
								   {1.0/texS, 0.0},
	                               {1.0/texS, 1.0/texT}};

	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2, 0.0, 1.0, 2 * 3, 2, &ctrlpoints[0][0]);
	glMap2f(GL_MAP2_NORMAL,  0.0, 1.0, 3, 2, 0.0, 1.0, 2 * 3, 2, &normalpoints[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 2 * 2, 2, &texturepoints[0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	glMapGrid2f(div, 0.0, 1.0, div, 0.0, 1.0);
	glEvalMesh2(GL_FILL,0, div, 0, div);  
}
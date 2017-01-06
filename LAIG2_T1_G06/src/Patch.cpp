#include "Patch.h"

void Patch::draw(float texS, float texT)
{
	/*NEEDED BECAUSE OF AUTO NORMALS*/
	glFrontFace(GL_CW);
	int order = (int)this->getOrder()+1;

	int size = this->getNumControlPoints();
	for(int i = 0; i < size; i++)
	{
		for(int k = 0; k < 3; k++)
		{
			ctrlpoints[i][k] = this->getCtrlPoints().at(i)[k];
		}
	}

	GLfloat texturepoints[4][2] = {{0.0, 0.0},
								   {0.0, 1.0/texT}, 
								   {1.0/texS, 0.0},
	                               {1.0/texS, 1.0/texT}};

	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, order, 0.0, 1.0, 3 * order, order, &ctrlpoints[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 2 * 2, 2, &texturepoints[0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	glMapGrid2f(this->getPartsU(), 0.0, 1.0, this->getPartsV(), 0.0, 1.0);
	glEvalMesh2(this->getCompute(), 0, this->getPartsU(), 0, this->getPartsV());

	glFrontFace(GL_CCW);
}
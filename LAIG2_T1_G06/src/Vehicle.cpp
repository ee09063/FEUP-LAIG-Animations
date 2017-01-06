#include "Vehicle.h"

Vehicle::Vehicle() : Primitive("vehicle")
{
	this->plane = new Plane();
	vector<float>f;
	f.push_back(10);
	this->plane->setValues(f);

	this->patch = new Patch();
		vector<float> v;
		v.push_back(2); // order
		v.push_back(10); // parts U
		v.push_back(10); // parts V
		v.push_back(0); // GL_FILL
		this->patch->setValues(v);
		
		float* ctrlpoint1 = (float*)malloc(sizeof(float)*3);
		float* ctrlpoint2 = (float*)malloc(sizeof(float)*3);
		float* ctrlpoint3 = (float*)malloc(sizeof(float)*3);
		float* ctrlpoint4 = (float*)malloc(sizeof(float)*3);
		float* ctrlpoint5 = (float*)malloc(sizeof(float)*3);
		float* ctrlpoint6 = (float*)malloc(sizeof(float)*3);
		float* ctrlpoint7 = (float*)malloc(sizeof(float)*3);
		float* ctrlpoint8 = (float*)malloc(sizeof(float)*3);
		float* ctrlpoint9 = (float*)malloc(sizeof(float)*3);
		ctrlpoint1[0] = -0.25; ctrlpoint1[1] = 0.0; ctrlpoint1[2] = 2.0;
		ctrlpoint2[0] = -1; ctrlpoint2[1] = 0.0; ctrlpoint2[2] = 1.0;
		ctrlpoint3[0] = -0.5; ctrlpoint3[1] = 0.0; ctrlpoint3[2] = 0.0;
		ctrlpoint4[0] = 0;  ctrlpoint4[1] = 0.0; ctrlpoint4[2] = 2.0;
		ctrlpoint5[0] = 0;  ctrlpoint5[1] = 1.5; ctrlpoint5[2] = 1.0;
		ctrlpoint6[0] = 0;  ctrlpoint6[1] = 0.0; ctrlpoint6[2] = 0.0;
		ctrlpoint7[0] = 0.25;  ctrlpoint7[1] = 0.0; ctrlpoint7[2] = 2.0;
		ctrlpoint8[0] = 1;  ctrlpoint8[1] = 0.0; ctrlpoint8[2] = 1.0;
		ctrlpoint9[0] = 0.5;  ctrlpoint9[1] = 0.0; ctrlpoint9[2] = 0.0;
		this->patch->addCtrlPoint(ctrlpoint3);
		this->patch->addCtrlPoint(ctrlpoint2);
		this->patch->addCtrlPoint(ctrlpoint1);
		this->patch->addCtrlPoint(ctrlpoint6);
		this->patch->addCtrlPoint(ctrlpoint5);
		this->patch->addCtrlPoint(ctrlpoint4);
		this->patch->addCtrlPoint(ctrlpoint9);
		this->patch->addCtrlPoint(ctrlpoint8);
		this->patch->addCtrlPoint(ctrlpoint7);
}

void Vehicle::draw(float texS, float texT)
{
	glPushMatrix();
		glTranslatef(0,0,-1);
		this->patch->draw(texS, texT);

		glRotatef(180.0, 0, 0, 1);
		this->patch->draw(texS, texT);
	glPopMatrix();
}
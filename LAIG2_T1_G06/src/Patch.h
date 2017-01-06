#ifndef _PATCH_H_
#define _PATCH_H_

#include "SceneGraph.h"

class Patch : public Primitive, CGFobject
{
	float order;
	float partsU;
	float partsV;
	GLenum compute;
	vector<float> v;
	GLfloat ctrlpoints[16][3];
	GLfloat texturepoints[4][2];
public:
	Patch() : Primitive("patch"){};
	void draw(float texS, float texT);
	vector<float> getValues(){return this->v;}
	void setValues(vector<float>v)
	{
		this->v = v;
		this->order = v.at(0);
		this->partsU = v.at(1);
		this->partsV = v.at(2);
		if(v.at(3)==0) this->compute = GL_FILL;
		else if(v.at(3)==1) this->compute = GL_LINE;
		else if(v.at(3)==2) this->compute = GL_POINT;
	}
	float getOrder(){return this->order;}
	float getPartsU(){return this->partsU;}
	float getPartsV(){return this->partsV;}
	GLenum getCompute(){return this->compute;}
	void updateShaderTime(float time){}
	void updateShaderWind(float wind){}
};

#endif
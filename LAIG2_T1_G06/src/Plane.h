#ifndef _PLANE_H_
#define _PLANE_H_

#include "SceneGraph.h"

class Plane : public Primitive, CGFobject
{
    float numDiv;
	vector<float> v;

public:
	Plane() : Primitive("plane"){}
	void draw(float texS, float texT);
	vector<float> getValues(){return v;}
		void setValues(vector<float>v)
		{
			this->v=v;
			this->numDiv = v.at(0);
		}
		void updateShaderTime(float time){}
		void updateShaderWind(float wind){}
};

#endif
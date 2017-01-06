#ifndef _VEHICLE_H_
#define _VEHICLE_H_

#define SIZE 15

#include "Patch.h"
#include "Plane.h"

class Vehicle : public Primitive, CGFobject
{
public:
	Primitive* plane;
	Primitive* patch;
	Vehicle();
	void draw(float texS, float texT);
	vector<float> getValues(){return this->patch->getValues();}
	void setValues(vector<float>v){this->patch->setValues(v);}
	void updateShaderTime(float time){}
	void updateShaderWind(float wind){}
};

#endif
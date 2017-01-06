#ifndef _FLAG_H_
#define _FLAG_H_

#define SIZE 15

#include "Plane.h"
#include "Shader.h"

class Flag : public Primitive, CGFobject
{
public:
	Shader* shader;
	Primitive* plane;
	Flag(char* texture) : Primitive("flag")
	{
		this->shader = new Shader(texture);
		this->plane = new Plane();
		vector<float> v;
		v.push_back(100); // parts U
		plane->setValues(v);
	}
	void setValues(vector<float>f){this->plane->setValues(f);}
	vector<float> getValues(){return this->plane->getValues();}
	void draw(float a, float b)
	{
		glPushMatrix();
			this->shader->bind();
			glTranslatef(10.0, 0, 5);
			glScalef(20, 1, 10);
			this->plane->draw(a,b);
			this->shader->unbind();
		glPopMatrix();
	}

	void updateShaderTime(float time){this->shader->updateTime(time);}
	void updateShaderWind(float wind){this->shader->updateWind(wind);}


};

#endif
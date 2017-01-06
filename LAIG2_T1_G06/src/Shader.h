#ifndef _SHADER_H_
#define _SHADER_H_

#include "CGFshader.h"
#include "CGFtexture.h"

class Shader :	public CGFshader
{
public:
	Shader(char* textureFile);
	virtual void bind(void);
	void setScale(float s);
	float time;
	int wind;
	char* textureName;

	void updateTime(float time){this->time = time;}
	void updateWind(int wind){this->wind = wind;}

protected:
	CGFtexture* flagTexture;

	GLint flagImageLoc;

	GLint timeLoc;
	GLint windLoc;
};

#endif // _SHADER_H_
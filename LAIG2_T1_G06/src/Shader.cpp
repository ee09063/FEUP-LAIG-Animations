#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "Shader.h"



Shader::Shader(char* textureFile)
{
	//init("../data/vertShader.vert", "../data/fragShader.frag");
	init("../bin/vertexShader.vert", "../bin/fragShader.frag");
	CGFshader::bind();

	time = 1;
	wind = 10.0;
	
	// Store Id for the uniform "normScale", new value will be stored on bind()
	timeLoc = glGetUniformLocation(id(), "time");
	windLoc = glGetUniformLocation(id(), "wind");

	//flagTexture=new CGFtexture("../bin/globe.jpg");
	flagTexture=new CGFtexture(textureFile);

	// get the uniform location for the sampler
	flagImageLoc = glGetUniformLocation(id(), "flagImage");

	// set the texture id for that sampler to match the GL_TEXTUREn that you 
	// will use later e.g. if using GL_TEXTURE0, set the uniform to 0
	glUniform1i(flagImageLoc, 0);
}

void Shader::bind(void)
{
	//printf("TIME AND WIND: %f %f\n", this->time, this->wind);
	CGFshader::bind();

	// update uniforms
	glUniform1f(timeLoc, time);
	glUniform1f(windLoc, wind);

	// make sure the correct texture unit is active
	glActiveTexture(GL_TEXTURE0);

	// apply/activate the texture you want, so that it is bound to GL_TEXTURE0
	flagTexture->apply();
}
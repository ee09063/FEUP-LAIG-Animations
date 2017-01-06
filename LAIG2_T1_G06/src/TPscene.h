#ifndef TPSCENE_H
#define TPSCENE_H

#include "CGFscene.h"
#include "SceneGraph.h"
#include "Shader.h"
#include <vector>

using std::vector;

void processGraph(Graph* g, Node* n);

class TPscene : public CGFscene
{
	Graph *g;
	InitVar *iv;
	vector<CGFlight*> lights;
	GLenum drawingMode;
	bool firstPass;
	
public:
	int drawMode;
	int cameraMode;
	int shaderWind;
	int* lightCheck;
	
	TPscene(Graph* g, InitVar *iv)
	{
		this->g=g;
		this->iv=iv;
		this->lightCheck = (int*)malloc(sizeof(int)*iv->getLights().size());
		this->cameraMode = 0;
		this->shaderWind = 1;
		this->firstPass = true;
	}
	void init();
	void display();
	void toggleLights();
	void letThereBeLight();
	void chooseActiveCamera();

	void processGraph(Graph* g, Node* n, Appearance* app);
	void processNode(Graph* g, Node* n, Appearance* app);

	void setDrawingMode(GLenum drawingMode){this->drawingMode = drawingMode;}
	void setFirstPass(bool firstPass){this->firstPass = firstPass;}
	bool getFirstPass(){return this->firstPass;}

	unsigned long time;
	virtual void update(unsigned long);
};

#endif
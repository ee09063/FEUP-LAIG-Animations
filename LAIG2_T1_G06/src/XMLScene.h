#pragma once
#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"
#include "string.h"
#include "SceneGraph.h"
#include "Plane.h"
#include "Patch.h"
#include "Flag.h"
#include "Vehicle.h"

using std::vector;

void postProcess(InitVar* iv, Graph* g);

bool checkRepeated(char* id, vector<char*> idList);

class XMLScene
{
public:
	XMLScene(char *filename, Graph* g, InitVar *iv);
	~XMLScene();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	
	vector<Camera*> cameras;
	vector<Light*> lights;
	vector<Texture*> textures;
	vector<Appearance*> appearances;
	vector<Animation*> animations;

	Texture* getTextureById(char* id);
	Appearance* getAppearanceById(char* id);
	Animation* getAnimationById(char* id);

	Global* registerGlobalVariables(TiXmlElement* globalElement);
	void registerCameras(TiXmlElement* cameraElement);
	void registerLights(TiXmlElement* lightElement);
	void registerTextures(TiXmlElement* textsElement);
	void registerApps(TiXmlElement* appElement);
	void registerAnimations(TiXmlElement* animationElement);

	Primitive* registerRectangle(TiXmlElement *prim, char*id);
	Primitive* registerTriangle(TiXmlElement *prim, char*id);
	Primitive* registerCylinder(TiXmlElement *prim, char*id);
	Primitive* registerSphere(TiXmlElement *prim, char*id);
	Primitive* registerTorus(TiXmlElement *prim, char*id);
	Primitive* registerPlane(TiXmlElement *prim, char*id);
	Primitive* registerPatch(TiXmlElement *prim, char* id);
	Primitive* registerFlag(TiXmlElement* prim, char* id);
	Primitive* registerVehicle(TiXmlElement* prim, char* id);

protected:

	TiXmlDocument* doc;

	TiXmlElement* globalElement; 
	TiXmlElement* appElement;
	TiXmlElement* textsElement;
	TiXmlElement* primElement;
	TiXmlElement* nodeElement;
	TiXmlElement* graphElement;
	TiXmlElement* cameraElement;
	TiXmlElement* lightElement;
	TiXmlElement* animationElement;
};

#endif
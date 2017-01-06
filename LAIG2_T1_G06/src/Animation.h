#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <GL/glut.h>
#include <stdlib.h>


#define M_PI 3.14159265358979323846

using std::vector;

class Animation
{
	char* id;
	char* type;
	float total_time;

public:
	unsigned long time_actual;
	bool ended;
	bool active;

	vector<float*> ctrlpoints;
	vector<float*> ctrlvectors;
	vector<float> ctrlangles;
	vector<float> distances;
	vector<float> distances2D;
	vector<float> angles;
	vector<float> velx;
	vector<float> vely;
	vector<float> velz;
	vector<float> timeFrag;
	vector<float> timeFragR;

	Animation(char* id, char* type, float span);
	
	char* getId(){return this->id;}
	char* getType(){return this->type;}
	float getSpan(){return this->total_time;}
	void addCtrlPoint(float* ctrlp){ctrlpoints.push_back(ctrlp);}
	void addCtrlVector(float* ctrlv){ctrlvectors.push_back(ctrlv);}
	void addAngle(float angle){angles.push_back(angle);}
	void addVelX(float vel){this->velx.push_back(vel);}
	void addVelY(float vel){this->vely.push_back(vel);}
	void addVelZ(float vel){this->velz.push_back(vel);}
	void addFrag(float timeFrag){this->timeFrag.push_back(timeFrag);}
	void addFragR(float timeFragR){this->timeFragR.push_back(timeFragR);}

	virtual vector<float> updateAnimation(float x, float y, float z, float alpha, unsigned long time, unsigned long delta) = 0;
	virtual void calculateControlVectors(){};
	virtual	void calculateDistances(){};
	virtual void calculateAngles(){};
	virtual void calculateTimeFrags(){};
	virtual void calculateVelocities(){};
};

class AnimationLinear : public Animation
{
	float trans_x, trans_y, trans_z, dir_angle;
	float total_distance;
	int STATE;
	
public:
	AnimationLinear(char* id, float timeSpan) : Animation(id, "linear", timeSpan){
		this->trans_x = 0;
		this->trans_y = 0;
		this->trans_z = 0;
		this->STATE = 0;
		this->total_distance = 0;
		dir_angle = 0;
	}
	vector<float> updateAnimation(float x, float y, float z, float alpha, unsigned long time , unsigned long delta);
	void calculateDistances();
	void calculateDistances2D();
	void calculateControlVectors();
	void calculateAngles();
	void calculateVelocities();
	void calculateTimeFrags();
};

class AnimationCircular : public Animation
{
	float initial_angle;
	float final_angle;
	float* center;
	float omega;
	float radius;
	float time_span;

public:
	AnimationCircular(char* id, float initial_angle, float final_angle, float* center, float radius, float time_span) : Animation(id, "circular", time_span){
		this->initial_angle = initial_angle;
		this->final_angle = final_angle;
		this->center = (float*)malloc(sizeof(float)*3);
		this->center = center;
		this->radius = radius;
		this->omega = (this->final_angle - this->initial_angle) / time_span;
		this->time_span = time_span;
	}
	float getStartAng(){return this->initial_angle;}
	float getRotAng(){return this->final_angle;}
	float getRadius(){return this->radius;}
	float* getCenter(){return this->center;}
	vector<float> updateAnimation(float x, float y, float z, float alpha, unsigned long time , unsigned long delta);
};
#endif
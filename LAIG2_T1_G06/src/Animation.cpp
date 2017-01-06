#include "Animation.h"

/*CONVERSIONS*/
float DtR(float degree)
{
	return (degree * M_PI) / 180.0;
}

float RtD(float rad)
{
	return (180.0 * rad) / M_PI;
}

float scalar_product(float* a, float* b)
{
    float product = 0;
    for (int i = 0; i <= 1; i++)
       product += (a[i])*(b[i]);
    return product;
}

Animation::Animation(char* id, char* type, float total_time)
{
		this->id = id;
		this->type = type;
		this->total_time = total_time;
		this->time_actual = 0;
		this->ended = false;
		this->active = false;
}

/*TAKES THE CONTROL POINTS AND CALCULATES CONTROL VECTORS*/
void AnimationLinear::calculateControlVectors()
{
	for(unsigned int i = 0; i < this->ctrlpoints.size()-1; i++)
	{
		float* ctrlvector = (float*)malloc(sizeof(float)*3);
		float* ctrlp1 = this->ctrlpoints.at(i);
		float* ctrlp2 = this->ctrlpoints.at(i+1);
		ctrlvector[0] = ctrlp2[0]-ctrlp1[0];
		ctrlvector[1] = ctrlp2[1]-ctrlp1[1];
		ctrlvector[2] = ctrlp2[2]-ctrlp1[2];
		this->addCtrlVector(ctrlvector);
	}
}

float getDistance(float p1x, float p1y, float p1z, float p2x, float p2y, float p2z)
{
	return sqrtf( powf(p2x-p1x,2) + powf(p2y-p1y,2) + powf(p2z-p1z,2));
}

float getDistance2(float px, float py, float pz)
{
	return sqrtf( powf(px,2) + powf(py,2) + powf(pz,2));
}

/*2D DISTANCE IS USED FOR SCALAR PRODUCT TO CALCULATE ANGLES*/
float getDistance2D(float px, float pz)
{
	return sqrtf( powf(px,2) + powf(pz,2));
}

/*CALCULATES THE DISTANCES OF EACH FRAGMENT*/
void AnimationLinear::calculateDistances()
{
	for(unsigned int i = 0; i < this->ctrlvectors.size(); i++)
	{
		float x = this->ctrlvectors.at(i)[0];
		float y = this->ctrlvectors.at(i)[1];
		float z = this->ctrlvectors.at(i)[2];
		float distance = getDistance2(x, y, z);
		float distance2D = getDistance2D(x,z);
		this->distances.push_back(distance);
		this->distances2D.push_back(distance2D);
		this->total_distance += distance;
	}
}

/*CALCULATES ANGLES FOR THE END OF EACH FRAGMENT*/
void AnimationLinear::calculateAngles()
{
	for(unsigned int i = 0; i < this->ctrlvectors.size(); i++)
	{
		float* zaxis = (float*)malloc(sizeof(float)*2);
		float* vector = (float*)malloc(sizeof(float)*2);
		
		zaxis[0] = 0; zaxis[1] = 1;
		vector[0] = this->ctrlvectors.at(i)[0];
		vector[1] = this->ctrlvectors.at(i)[2];
		
		float scalar = scalar_product(vector, zaxis);
		float modCtrl = this->distances2D.at(i);
		
		float rad;
		rad = acos( scalar / modCtrl);
		
		float angle;

		if(modCtrl != 0)
			angle = RtD(rad);
		else if(modCtrl == 0 && i > 0) // GOES UP -> ANGLE DOESN'T CHANGE
			angle = this->angles.at(i-1);
		else if(modCtrl == 0 && i == 0) // GOES UP IN THE FIRST FRAGMENT
			angle = 0;

		//CHECK IF VECTOR IS ON 3RD OR 4TH QUADRANT DUE TO SCALAR PRODUCT RESULT
		if(vector[0] < 0 && vector[1] < 0)
			angle += 90;
		else if(vector[0] < 0 && vector[1] > 0 || vector[0] < 0 && vector[1] == 0)
			angle *= -1;

		this->addAngle(angle);
	}
}

/*CALCULATE VELOCITY FOR EACH AXIS FOR EACH FRAGMENT*/
void AnimationLinear::calculateVelocities()
{
	for(unsigned int i = 0; i < this->ctrlpoints.size()-1; i++)
	{
		float time_fragment = this->timeFragR.at(i);

		float xi = this->ctrlpoints.at(i)[0];
		float xf = this->ctrlpoints.at(i+1)[0];
		float vel_x = (xf-xi)/time_fragment;
		this->addVelX(vel_x);

		float yi = this->ctrlpoints.at(i)[1];
		float yf = this->ctrlpoints.at(i+1)[1];
		float vel_y = (yf-yi)/time_fragment;
		this->addVelY(vel_y);

		float zi = this->ctrlpoints.at(i)[2];
		float zf = this->ctrlpoints.at(i+1)[2];
		float vel_z = (zf-zi)/time_fragment;
		this->addVelZ(vel_z);
	}
}

/*CALCULATES THE TIMEFRAGMENTS NEEDED TO KEEP TRACK OF THE ANIMATION*/
void AnimationLinear::calculateTimeFrags()
{
	for(unsigned int i = 0; i < this->distances.size(); i++)
	{
		float time_fragment = (this->getSpan() * this->distances.at(i))/this->total_distance;
		this->addFragR(time_fragment); /*RELATIVE FRAGMENT, USED TO CALCULATE SPEED OF EACH FRAGMENT*/
		float time;
		if(i == 0)//first
			time = time_fragment;
		else
			time = time_fragment + this->timeFrag.at(i-1);
		this->addFrag(time);/*ABSOLUTE FRAGMENT, USED TO CHECK WHAT FRAGMENT THE NODE IS ON*/
	}
}

/*UPDATES THE VARIABLES OF THE NODE*/
vector<float> AnimationLinear::updateAnimation(float x, float y, float z, float alpha, unsigned long time, unsigned long delta)//time between animations in milliseconds
{
	float timeSeconds = time/1000.0;
	vector<float>v;
	unsigned int fragment;
	/*CHECKING CURRENT PATH FRAGMENT, TO GET THE RIGHT SPEED*/
	for(fragment = 0; fragment < this->timeFrag.size(); fragment++)
	{
		if(timeSeconds <= this->timeFrag.at(fragment) && fragment == 0)//first
			break;
		else if(timeSeconds <= this->timeFrag.at(fragment) && timeSeconds >= this->timeFrag.at(fragment-1))
			break;
	}

	if(fragment < this->timeFrag.size())
	{
		x += (this->velx.at(fragment) * delta/1000.0);
		y += (this->vely.at(fragment) * delta/1000.0);
		z += (this->velz.at(fragment) * delta/1000.0);
		alpha = this->angles.at(fragment);
		v.push_back(x);
		v.push_back(y);
		v.push_back(z);
		v.push_back(alpha);
	}
	return v;
}

/*UPDATES THE VARIABLES OF THE NODES*/
vector<float> AnimationCircular::updateAnimation(float x, float y, float z, float alpha, unsigned long time, unsigned long delta)
{	
	vector<float> v;
	alpha = this->omega * time/1000.0;
	float a = DtR(alpha);
	x = this->center[0] + this->radius * sin(a);
	y = this->center[1];
	z = this->center[2] + this->radius * cos(a);
	v.push_back(x);
	v.push_back(y);
	v.push_back(z);
	v.push_back(alpha);
	return v;
}
#pragma  once

#include "cocos2d.h"
#include "Headfile.h"
#include"cocostudio/CocoStudio.h"

using namespace cocostudio;
USING_NS_CC;

class ArmPerson : public Armature
{
public:
	CREATE_FUNC(ArmPerson);
	virtual bool init();
	virtual void addRunAnimation();
	virtual void addPhysics();
	//	void addObserver();

	void setSpeed(float speed);
	float getSpeed();
	void setType(TYPE type);
	TYPE getType();
	int getDir();
	void setDir(int dir);

	void deadAnimation();
	void changeDir(); // �ı䷽��
	//float getHealth(){ return health; }
	//void setHealth(float h){ health = h; }
private:
	int _dir; //ָʾ����
	TYPE _type;
	float _speed;
};

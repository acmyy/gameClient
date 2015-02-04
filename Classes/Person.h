#pragma  once

#include "cocos2d.h"
#include "Headfile.h"
USING_NS_CC;

class Person : public Sprite
{
public:
	CREATE_FUNC(Person);
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

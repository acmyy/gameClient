#pragma  once

#include "cocos2d.h"
#include "Headfile.h"
USING_NS_CC;

class Person : public Sprite
{
public:
	CREATE_FUNC(Person);
	virtual bool init();
	void addRunAnimation();
	void addPhysics();
	//	void addObserver();
	void setSpeed(float speed){ _speed = speed; }
	float getSpeed(){ return _speed;}
	void deadAnimation();
	void changeDir(); // �ı䷽��
	//float getHealth(){ return health; }
	//void setHealth(float h){ health = h; }
private:
	int _dir; //ָʾ����
	TYPE _type;
	float _speed;
};

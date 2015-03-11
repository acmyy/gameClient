#pragma  once

#include "cocos2d.h"
#include "Headfile.h"
#include"cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocostudio;
USING_NS_CC;

class Person : public Sprite
{
public:
	static Person* create(int maxLife);
	virtual bool init(int maxLife);
	virtual void addRunAnimation();
	virtual void addPhysics();
	//	void addObserver();

	void setSpeed(float speed);
	float getSpeed();
	void setType(TYPE type);
	TYPE getType();
	int getDir();
	void setDir(int dir);
	virtual void beHit();
	void deadAnimation();
	void changeDir(); // �ı䷽��
	//float getHealth(){ return health; }
	//void setHealth(float h){ health = h; }
protected:
	bool _isDead;
	int _curLife;
	int _maxLife;
private:
	int _dir; //ָʾ����
	TYPE _type;
	float _speed;
};

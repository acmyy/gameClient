#pragma  once

#include "cocos2d.h"
USING_NS_CC;

class Monster : public Sprite
{
public:
	CREATE_FUNC(Monster);
	virtual bool init();
	void addRunAnimation();
	void addPhysics();
//	void addObserver();
	void setSpeed(float speed){ _speed = speed; }
	float getSpeed(){ return _speed;}
	void deadAnimation();
	void update(float dt);
	void changeDir(); // �ı䷽��
	//float getHealth(){ return health; }
	//void setHealth(float h){ health = h; }
private:
	int _dir; //ָʾ����
	int _type;
	float _speed;

};

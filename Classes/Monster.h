#pragma  once

#include "cocos2d.h"
#include "Person.h"
#include "Progress.h"
USING_NS_CC;

class Monster : public Person
{
public:
	CREATE_FUNC(Monster);
	bool init();
	void onEnter();
	void addRunAnimation();
	void updateBullet(float dt);
	//void deadAnimation();
	void update(float dt);
	void beHit() override;
	void removeThis(float dt);
	void atkToRun(float dt);
private:
	Sprite* _spHit;
	Progress* _progress;
	int _spHitTime;
	int _monsterType;
};

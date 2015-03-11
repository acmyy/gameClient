#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GameOver : public Layer
{
public:

	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	//   void replaceCloseCallback(float dt);
	// implement the "static create()" method manually
	CREATE_FUNC(GameOver);
};



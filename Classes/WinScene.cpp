#include "WinScene.h"
#include "LogInScene.h"
#include "ui/UIButton.h"
using namespace cocostudio;
cocos2d::Scene* WinScene::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = WinScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool WinScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	auto node = CSLoader::createNode("WinScene.csb");
	auto action = CSLoader::createTimeline("WinScene.csb");
	node->runAction(action);
	action->gotoFrameAndPlay(0, true);
	addChild(node);

	auto mBackBtn = dynamic_cast<ui::Button*>(node->getChildByName("Button_Back"));
	mBackBtn->addClickEventListener([&](Ref* sender)
	{
		auto nextScene = LogInScene::createScene();
		Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f,nextScene));
	});
	return true;
}
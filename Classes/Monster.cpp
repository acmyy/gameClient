#include "Monster.h"
#include "Headfile.h"
#include "Bullet.h"
bool Monster::init()
{
	_monsterType = rand() % 3;
	char txt[100];
	sprintf_s(txt, "boy%d_1_1.png", _monsterType + 1);
	if (!Sprite::initWithFile(txt)) {
		return false;
	}
	addRunAnimation();
	_maxLife = _monsterType + 1;
	_curLife = _monsterType + 1;
	auto size = this->getContentSize();
	_progress = Progress::create("small-enemy-progress-bg.png","small-enemy-progress-fill.png");
	_progress->setScaleY(0.6);
	_progress->setScaleX(0.8);
	_progress->setPosition( size.width*2/3, size.height + _progress->getContentSize().height/2);
	this->addChild(_progress);
//	if(_monsterType >= 2) this->setScale(0.25);
	this->setTag(TYPE::MONSTER);
	setType(TYPE::MONSTER);
	scheduleUpdate();
	_spHit = Sprite::create("hitBlode.png");
	addChild(_spHit, 1);
	_spHit->setVisible(false);
	_spHitTime = 0;
	_isdead = false;
	_spHit->setScale(0.5);
	schedule(schedule_selector(Monster::updateBullet),4);
	Person::init();
	return true;
}
void Monster::updateBullet(float dt)
{
	if(_isdead) return;
	auto bullet = Bullet::create(BULLETENEMY, Vec2(getDir(), 0), 100);
	bullet->setPosition(this->getPosition());
	getParent()->addChild(bullet, 2);
}
void Monster::addRunAnimation()
{
	if(_monsterType < 2)
	{
		Vector<SpriteFrame*> allFrames;
		char txt[100];
		for(int i = 1;i <= 5; i++)
		{
			sprintf_s(txt, "boy%d_1_%d.png",_monsterType + 1, i);
			SpriteFrame *sf = SpriteFrame::create(txt, Rect(0, 0, 43, 63));
			allFrames.pushBack(sf);
		}
		auto runAni = Animation::createWithSpriteFrames(allFrames, 0.1f);
		runAction(RepeatForever::create(Animate::create(runAni)));
	}
	else
	{
		ArmatureDataManager::getInstance()->addArmatureFileInfo("NewAnimation0.png","NewAnimation0.plist","NewAnimation.ExportJson");

		Armature *armature = Armature::create("NewAnimation");

		armature->setScale(100 / 671.0);
		armature->setAnchorPoint(Point(0,0));
	//	armature->setPosition(Point(5700, 320));
		
		this->addChild(armature);
		//���Ŷ���
		armature->getAnimation()->play("walk");
	}
}

void Monster::behit()
{
	SimpleAudioEngine::getInstance()->playEffect("hit.mp3");
	_curLife--;
	_progress->setProgress(_curLife * 1.0 / _maxLife * 100);
	_spHit->setVisible(true);
	_spHitTime = 0;
	if(_curLife <= 0)
	{
		_isdead = true;
		getParent()->removeChild(this, true);
		//NotificationCenter::getInstance()->postNotification(strWin);
	}

}
void Monster::update(float dt)
{
	if(_isdead) return;
	getPhysicsBody()->setVelocity(Vec2(getDir() * getSpeed(), getPhysicsBody()->getVelocity().y));
	if(_monsterType < 2)setScaleX(getDir() == 1 ? 1 : -1);
	else setScaleX(getDir() == 1 ? -1 : 1);
	_spHit->setPosition(Vec2(30, 30) );
	if(_spHit->isVisible())
	{
		_spHitTime++;
		if(_spHitTime >= 10) _spHit->setVisible(false);
	}
}

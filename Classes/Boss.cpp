#include "Boss.h"
#include "Headfile.h"
#include "MainScene.h"

Boss* Boss::create(int mhard)
{
	Boss* ret = new Boss();  
	if(ret&&ret->init(mhard)){  
		ret->autorelease();  
		return ret;  
	}  
	CC_SAFE_DELETE(ret);//��ȫɾ��  
	return nullptr;  
}
bool Boss::init(int mhard)
{	
	_monsterType = 2;
	_hard = mhard;
	if (!Sprite::initWithFile("boss1.png")) {
		return false;
	}
	//	if(_monsterType >= 2) this->setScale(0.25);
	this->setTag(TYPE::BOSS);
	setType(TYPE::BOSS);
	Person::init(1 * _hard);
	setSpeed(0);
	setDir(-1);
	_time = 0;
	_spWeak = Sprite::create();
	_spHitTime = 0;	
	scheduleUpdate();
	return true;
}

void Boss::onEnter()
{
	Person::onEnter();
	auto body = PhysicsBody::createCircle(36, PhysicsMaterial(0, 0, 0));
	body->setCategoryBitmask(TYPE::BOSSWEAKNESS);
	body->setCollisionBitmask(TYPE::BOSSWEAKNESS | TYPE::BULLET);
	body->setContactTestBitmask(TYPE::BOSSWEAKNESS | TYPE::BULLET);
	body->setLinearDamping(0.0f);
	body->setDynamic(false);

	_spWeak->setPhysicsBody(body);
	_spWeak->setTag(TYPE::BOSSWEAKNESS);
	addChild(_spWeak);
	_spHit = Sprite::create("hitBlode.png");
	addChild(_spHit, 1);
	_spHit->setVisible(false);
	_progress = Progress::create("small-enemy-progress-bg.png","small-enemy-progress-fill.png");
	auto size = this->getContentSize();
	_progress->setPosition( size.width*2/3, size.height + _progress->getContentSize().height/2 + 50);
	_progress->setScaleX(2);
	addChild(_progress);
//	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Boss::shoot), strEnemyShoot, NULL);
}

void Boss::addRunAnimation()
{
	/*if(_monsterType < 2)
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
	{*/
		

		_armature = Armature::create("NewAnimation");

	//	armature->setScale(600 / 671.0);
		_armature->setAnchorPoint(Point(0,0));
		//	armature->setPosition(Point(5700, 320));

		this->addChild(_armature);
		_armAnimation = _armature->getAnimation();
		//���Ŷ���
		_armAnimation->play("walk");
	//}
}

void Boss::beHit()
{
	Person::beHit();
	SimpleAudioEngine::getInstance()->playEffect("explode.wav");
	_spHit->setVisible(true);
	_progress->setProgress(_curLife * 1.0 / _maxLife * 100);
	_spHitTime = 0;
	if(_isDead)
	{
		heroScore += 1000*_hard;
		char s[10];
		sprintf(s,"%d",heroScore);
		NotificationCenter::getInstance()->postNotification(showScore,String::create(s));
		getParent()->removeChild(this, true);
		NotificationCenter::getInstance()->postNotification(strWin);
	}
}
void Boss::shoot(Object * object)
{
	if(_isDead) return;
	Point pos1 = this->getParent()->getChildByTag(TYPE::HERO)->getPosition();
	Point pos2 = this->getPosition();
	Vec2 dire = pos1 - pos2;
	dire.normalize();
	auto bullet = Bullet::create(BULLETENEMY, dire, 180, 4, false);
	bullet->setPosition(pos2);
	this->getParent()->addChild(bullet, 2);
}
void Boss::update(float dt)
{
	if(_isDead) return;
	Point pos1 = this->getParent()->getChildByTag(TYPE::HERO)->getPosition();
	Point pos2 = this->getPosition();
	if(fabs(pos2.x - pos1.x) <= 480 ) setSpeed(100);
	getPhysicsBody()->setVelocity(Vec2(getDir() * getSpeed(), getPhysicsBody()->getVelocity().y));
	if(_monsterType < 2)setScaleX(getDir() == 1 ? 1 : -1);
	else setScaleX(getDir() == 1 ? -1 : 1);
	switch(_hard){
	case 1: AIeasy();break;
	case 2: AImid();break;
	case 3: AIhard();break;
	default:break;
	}
	_spWeak->setPosition(Vec2(260, 410) );
	_spHit->setPosition(Vec2(260, 410) );
	if(_spHit->isVisible())
	{
		_spHitTime++;
		if(_spHitTime >= 10) _spHit->setVisible(false);
	}
}
void Boss::AIeasy(){
	_time = (_time + 1) % 180;
	if(_time == 0)	shoot(NULL);
}
void Boss::AImid(){
	_time = (_time + 1) % 90;
	if(_time == 0)	shoot(NULL);	
}
void Boss::AIhard(){
	_time = (_time + 1) % 60;
	if(_time == 0)	shoot(NULL);
		
}
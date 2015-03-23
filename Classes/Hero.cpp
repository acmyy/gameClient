#include"Hero.h"
#include "Headfile.h"
using namespace std;
bool Hero::init()
{
	_isJump = false;
	_leftDown  = false;
	_rightDown = false;
	_moveState = 0;
	bulletRate = 0;
	string txt = ("player_1_4.png");
	if (!Sprite::initWithFile(txt))	return false;
	setTag(TYPE::HERO);
	setType(TYPE::HERO);
	Person::init(100);
	scheduleUpdate();
	return true;
}

void Hero::onEnter()
{
	Person::onEnter();
	idle();
	addObserver();
	possLifeMsg();
}

void Hero::onExit()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
	Person::onExit();
}
void Hero::idle()
{    
	//removeAllChildren();
	stopAllActions();
	setSpriteFrame(SpriteFrame::create("player_1_4.png", Rect(0, 0, 57, 63)));
}
void Hero::possLifeMsg(){
	char s[10];
	sprintf(s," x %d",getLife());
	NotificationCenter::getInstance()->postNotification(showHeroLife,String::create(s));
}
void Hero::beHit() 
{
	Person::beHit();
	possLifeMsg();
	if(_isDead)
	{
		dead();
	}
}
void Hero::leftButtonDown(Object * object){
	setDir(-1);
	_leftDown = true;
}
void Hero::rightButtonDown(Object * object){
	setDir(1);
	_rightDown = true;
}
void Hero::jumpButtonDown(Object * object){
	if(_isDead) return;
	if(!_isJump){
		_isJump = true;
		getPhysicsBody()->setVelocity(Vec2(getPhysicsBody()->getVelocity().x, 503.0));
	}
}
void Hero::shoot(Object * object)
{
	if(_isDead||bulletRate>0)	return;
	bulletRate = BULLETRate;
	Point pos = getPosition();
	auto bullet = Bullet::create(BULLET,Vec2(getDir() == 1 ? 1 : -1, 0), 361, 10);
	bullet->setPosition(pos.x + getDir() * 10, pos.y);
	this->getParent()->addChild(bullet, 2);
}
void Hero::leftButtonUp(Object * object){
	_leftDown = false;
	setDir(_rightDown?1:-1);
}
void Hero::rightButtonUp(Object * object){
	_rightDown = false;
	setDir(_leftDown?-1:1);
}
void Hero::jumpButtonUp(Object * object){
	_isJump = false;
}
void Hero::runAnimation()
{
	log("hehe");
	Vector<SpriteFrame*> allFrames;
	char txt[100];
	for(int i = 1;i <= 6; i++)
	{
		sprintf_s(txt, "player_1_%d.png",i);
		SpriteFrame *sf = SpriteFrame::create(txt, Rect(0, 0, 57, 63));
		allFrames.pushBack(sf);
	}
	runAni = Animation::createWithSpriteFrames(allFrames, 0.1f);
	stopAllActions();
	runAction(RepeatForever::create(Animate::create(runAni)));
}

void Hero::addObserver()
{
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Hero::leftButtonDown), strLeftButtonDown, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Hero::rightButtonDown), strRightButtonDown, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Hero::jumpButtonDown), strJumpButtonDown, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Hero::shoot), strHeroShoot, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Hero::leftButtonUp), strLeftButtonUp, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Hero::rightButtonUp), strRightButtonUp, NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Hero::jumpButtonUp), strJumpButtonUp, NULL);
}
void Hero::update(float dt)
{
	if(_isDead) return;
	bulletRate-=dt;
	updateMoveState();	//��̬����
	if(_moveState&1){
		getPhysicsBody()->setVelocity(Vec2(getDir() * getSpeed(), getPhysicsBody()->getVelocity().y));
	}
}
void Hero::dead()
{
	stopAllActions();
	//	removeAllChildren();
	_isDead = true;
	_eventDispatcher->removeEventListener(_listen_key);
	setSpriteFrame(SpriteFrame::create("player_2.png", Rect(0, 0, 63, 63)));
}
void Hero::updateMoveState(){
	int tmpState = 0;
	if(_leftDown)	tmpState ^= 1;
	if(_rightDown)	tmpState ^= 3;
	if(_isJump)		tmpState ^= 4;
	if(_moveState == tmpState)	return;
	_moveState = tmpState;
	idle();
	if( (_moveState&1) && (!(_moveState&4)))	runAnimation();
	setScaleX(getDir() == 1 ? 1 : -1);
}
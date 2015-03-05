#pragma  once

#include "cocos2d.h"
#include "Headfile.h"
USING_NS_CC;

class MoveBody : public Sprite
{
public:
	
	static MoveBody* create(const char* imgname,Sprite* sp, float speed, int type, float mFloor, float mCeil); //small��ʾ�±߽磬 big��ʾ�ϱ߽�, type��ʾ�ƶ�ƽ̨�����ͣ�1��ʾ���ƶ���2��ʾ�����ƶ�,mFloor��ʾ�ƶ��½磬mCeil��ʾ�ƶ��Ͻ�
	bool init(const char* imgname,Sprite* sp, float speed, int type, float mFloor, float mCeil);  
	void update(float dt);
	inline void changeDir() { dir = -dir;}
private:
	float _floor,_ceil;
	float ox, oy;
	float _speed ;
	int _type; //type��ʾ�ƶ�ƽ̨�����ͣ�1��ʾ���£�2��ʾ����
	Sprite* _sp;
	Vec2 dir;
};
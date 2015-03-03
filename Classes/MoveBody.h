#pragma  once

#include "cocos2d.h"
#include "Headfile.h"
USING_NS_CC;

class MoveBody : public Sprite
{
public:
	
	static MoveBody* create(const char* imgname,Sprite* sp, float speed, int type); //small��ʾ�±߽磬 big��ʾ�ϱ߽�, type��ʾ�ƶ�ƽ̨�����ͣ�1��ʾ���£�2��ʾ����
	bool init(const char* imgname,Sprite* sp, float speed, int type);  
	void update(float dt);
	void changeDir()
	{
		dir = -dir;
	}
private:
	
	float _speed ;
	int _type; //type��ʾ�ƶ�ƽ̨�����ͣ�1��ʾ���£�2��ʾ����
	Sprite* _sp;
	Vec2 dir;
};
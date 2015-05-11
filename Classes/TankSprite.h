#ifndef TANKSPRITE_H
#define TANKSPRITE_H

#include "cocos2d.h"
#include "MapLayer.h"
using namespace cocos2d;

// 定义坦克级别
enum TankLevel
{
	StarOne = 1,
	StarTwo,
	StarThree,
	StarFour
};

// 坦克行为
enum TankAction
{
	UP = 1, // 上下左右
	LEFT,
	DOWN,
	RIGHT,
	STADY, // 停止移动
	FIRE   // 开火
};

// 坦克类
class TankSprite: public Sprite
{
public:
	static const int CollisionMod = 10; // 碰撞修正值
	virtual bool init();
	static TankSprite* initwithDelegate(int life, TankLevel level, MapLayer *mLayer);
	CREATE_FUNC(TankSprite);
	bool collisionCheck(Vec2 point);
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();

	void fireAction();

	int _speed; // 速度
	int _life;	// 生命个数
	TankLevel _level; //坦克等级
	TankAction _action;	//坦克的行动
	MapLayer *_maplayer;
private:

};

#endif
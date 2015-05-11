#include "ControlLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

bool ControlLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->addJoystick();
	// 更新函数
	this->scheduleUpdate();
	return true;
}

void ControlLayer::addJoystick()
{
	float joystickRadius = 140;
	_joystick = Joystick::create();
	//_joystick->init();
	_joystick->setJoystick(Vec2(100, 100));
	this->addChild(_joystick);
}

void ControlLayer::addPlayer(int life, int tlevel)
{
	_player = TankSprite::initwithDelegate(life, (TankLevel) tlevel, _mapLayer);
	Vec2 playerPoint = _mapLayer->getObjectPoint(_mapLayer->_object, "player");
	_player->setPosition(playerPoint.x, playerPoint.y);
	this->addChild(_player);
}
void ControlLayer::update(float t)
{
	if (_mapLayer == NULL)
	{
		return;
	}
	//TankSprite *player = _mapLayer->_player;

	if (_player == NULL)
	{
		return;
	}
	//移动坦克
	Vec2 dir = ccpMult(_joystick->getDirection(), 50);
	
	if (dir.x == 0 && dir.y == 0)
	{
		//不移动
		return ;
	}
	else if (dir.x > 0)
	{
		if (dir.y > 0 && dir.y > dir.y )
		{
			// 上移
			_player->moveUp();
		}
		else if(dir.y < 0 && dir.y < dir.x)
		{
			// 下移
			 _player->moveDown();
		}
		else
		{
			// 右移
			_player->moveRight();
		}
	}
	else
	{
		if (dir.y > 0 && dir.y > -dir.x)
		{
			_player->moveUp();
		}
		else if (dir.y < 0 && dir.y < -dir.x)
		{
			_player->moveDown();
		}
		else
		{
			_player->moveLeft();
		}
	}
}

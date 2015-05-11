#include "Joystick.h"
using namespace cocos2d;

bool Joystick::init()
{
	bool ret = false;
	do 
	{
		CC_BREAK_IF(!Sprite::init());
		_pJoystickBg =  Sprite::create("ui/joystickBg.png"); //背景
		_pJoystick = Sprite::create("ui/joystick.png"); //摇杆
		this->addChild(_pJoystickBg, 0);
		this->addChild(_pJoystick, 1);
		this->showJoystick();
		_pJoystickR = _pJoystickBg->getContentSize().width / 2;
		_pJoystickr = _pJoystick->getContentSize().width / 2;
		// 注册新的API
		auto listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(Joystick::onTouchesBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(Joystick::onTouchesMoved, this);
		listener->onTouchesEnded = CC_CALLBACK_2(Joystick::onTouchesEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		ret = true;
	} while (0);
	return ret;
}
// 显示摇杆
void Joystick::showJoystick()
{
	_pJoystickBg->setVisible(true);
	_pJoystick->setVisible(true);
}
// 隐藏摇杆
void Joystick::hideJoystick()
{
	_pJoystickBg->setVisible(false);
	_pJoystick->setVisible(false);
}
// 按击摇杆事件的处理
void Joystick::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	std::vector<Touch*>::const_iterator touchIter = touches.begin(); //向量迭代器
	Touch *touch = (Touch*)(*touchIter);
	if (_pJoystick->getBoundingBox().containsPoint(touch->getLocation()))
	{
		this->showJoystick();
		updateJoystick(touch);
		CCLOG("***************");
		CCLOG("update touch:%f %f",touch->getLocation().x, touch->getLocation().y);
		return;
	}
}
// 按击移动的处理
void Joystick::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
	std::vector<Touch*>::const_iterator touchIter = touches.begin(); 
	Touch *touch = (Touch*)(*touchIter);
	if (_pJoystick->isVisible())
	{
		updateJoystick(touch);
		return ;
	}
}
// 按击结束的处理
void Joystick::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
	std::vector<Touch*>::const_iterator touchIter = touches.begin();
	Touch *touch = (Touch*)(*touchIter);
	this->hideJoystick();
	_end = _start;
}
// 摇杆跟新坐标
void Joystick::setJoystick(Vec2 point)
{
	_start = point;
	_end = point;
	_pJoystickBg->setPosition(point);
	_pJoystick->setPosition(_pJoystickBg->getPosition());
}
// 更新摇杆状态
void Joystick::updateJoystick(Touch *touch)
{
	Vec2 hit = touch->getLocation(); //点击坐标
	_end = hit;
	float distance = _start.getDistance(hit); 
	Vec2 direction = (hit - _start).getNormalized(); //获得移动方向
	
	// 防止摇杆超出背景
	if (distance < _pJoystickr/2)
	{
		_pJoystick->setPosition(_start + (direction*distance));
	}
	else if(distance > _pJoystickr)
	{
		 _pJoystick->setPosition(_start + (direction*_pJoystickr));
	}
	else
	{
		_pJoystick->setPosition(_start + (direction*_pJoystickr/2));
	}
	
}

float Joystick::getVelocity()
{
	return ccpDistance(_start, _end);
}

Vec2 Joystick::getDirection()
{
	return ccpNormalize(ccpSub(_end, _start));
}
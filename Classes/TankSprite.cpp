#include "TankSprite.h"

bool TankSprite::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}
TankSprite* TankSprite::initwithDelegate(int life, TankLevel level, MapLayer *mLyer)
{
	TankSprite *tank;
	switch (level)
	{
	case TankLevel::StarOne:
		tank = (TankSprite *) Sprite::create("ui/tanks/player1_1.png");
		tank->_speed = 3;
		break;
	case TankLevel::StarTwo:

		break;
	case  TankLevel::StarThree:
		
		break;

	case  TankLevel::StarFour:
		break;

	default:
		break;
	}
	tank->_life = life;
	tank->_level = level;
	tank->_action = TankAction::UP;
	tank->_maplayer = mLyer;
	return tank;
}
// 检测对应坐标是否可碰撞
bool TankSprite::collisionCheck(Vec2 point)
{
	Vec2 tileCoord = _maplayer->tileCoordForPosition(point);
	int tileGid = _maplayer->_meta->getTileGIDAt(tileCoord);

	// 瓦片检测
	if (tileGid)
	{
		auto properties = _maplayer->_gameMap->getPropertiesForGID(tileGid).asValueMap();
		if (!properties.empty())
		{
			auto collision = properties["Collidable"].asString();
			if ("True" == collision)
			{
				return true;
			}
		}
	}
	return false;
}
void TankSprite::moveUp()
{
	this->setRotation(0);
	_action = TankAction::UP;

	Vec2 currentPoint = this->getPosition(); // 当前坦克坐标
	Size tankSize = this->boundingBox().size; // 坦克大小

	Size mapSzie = _maplayer->_gameMap->getContentSize();
	//地图边界检测
	if (currentPoint.y + tankSize.height/2 + _speed >  mapSzie.height)
	{
		return ;
	}

	Vec2 nextPointA = Vec2(currentPoint.x + tankSize.width/2 - CollisionMod, currentPoint.y + tankSize.height / 2 + _speed); //移动之后的坐标
	Vec2 nextPointB = Vec2(currentPoint.x - tankSize.width/2 + CollisionMod, currentPoint.y + tankSize.height / 2 + _speed);
	// 瓦片检测
	if (collisionCheck(nextPointA) || collisionCheck(nextPointB))
	{
		return ;
	}
	this->setPosition(Vec2(this->getPositionX(), this->getPositionY() + _speed));

}
void TankSprite::moveRight()
{
	this->setRotation(90);
	_action = TankAction::RIGHT;

	Vec2 currentPoint = this->getPosition(); // 当前坦克坐标
	Size tankSize = this->boundingBox().size; // 坦克大小
	Size mapSzie = _maplayer->_gameMap->getContentSize();

	//地图边界检测
	if (currentPoint.x + tankSize.width/2 + _speed+1 >  mapSzie.width)
	{
		return ;
	}

	Vec2 nextPointA = Vec2(currentPoint.x  + tankSize.width/2 + _speed, currentPoint.y + tankSize.height/2 - CollisionMod); //移动之后的坐标
	Vec2 nextPointB = Vec2(currentPoint.x  + tankSize.width/2 + _speed, currentPoint.y - tankSize.height/2 + CollisionMod); //移动之后的坐标
	// 瓦片检测
	if (collisionCheck(nextPointA) || collisionCheck(nextPointB))
	{
		return ;
	}
	this->setPosition(Vec2(this->getPositionX() + _speed, this->getPositionY()));
}
void TankSprite::moveLeft()
{
	this->setRotation(-90);
	_action = TankAction::LEFT;

	Vec2 currentPoint = this->getPosition(); // 当前坦克坐标
	Size tankSize = this->boundingBox().size; // 坦克大小
	Size mapSzie = _maplayer->_gameMap->getContentSize();
	// 地图边界检测
	if (currentPoint.x - tankSize.width/2 - _speed <  0)
	{
		return ;
	}
	Vec2 nextPointA = Vec2(currentPoint.x  - tankSize.width/2 - _speed, currentPoint.y + tankSize.height/2 - CollisionMod ); //移动之后的坐标
	Vec2 nextPointB = Vec2(currentPoint.x  - tankSize.width/2 - _speed, currentPoint.y - tankSize.height/2 + CollisionMod ); //移动之后的坐标
	if (collisionCheck(nextPointA) || collisionCheck(nextPointB))
	{
		return ;
	}
	this->setPosition(Vec2(this->getPositionX() - _speed, this->getPositionY()));
}
void TankSprite::moveDown()
{
	this->setRotation(180);
	_action = TankAction::LEFT;

	Vec2 currentPoint = this->getPosition(); // 当前坦克坐标
	Size tankSize = this->boundingBox().size; // 坦克大小
	Size mapSzie = _maplayer->_gameMap->getContentSize();

	// 地图边界检测
	if (currentPoint.y - tankSize.height/2 - _speed <  0)
	{
		return ;
	}
	Vec2 nextPointA = Vec2(currentPoint.x + tankSize.width/2 - CollisionMod, currentPoint.y  - tankSize.height/2 - _speed); //移动之后的坐标
	Vec2 nextPointB = Vec2(currentPoint.x - tankSize.width/2 + CollisionMod, currentPoint.y  - tankSize.height/2 - _speed);
	if (collisionCheck(nextPointA) || collisionCheck(nextPointB))
	{
		return ;
	}
	this->setPosition(Vec2(this->getPositionX(), this->getPositionY() - _speed));
}

void TankSprite::moveAction()
{
	//SpriteFrameCache *frameCache = SpriteFrameCache::sharedSpriteFrameCache();
	//frameCache->addSpriteFramesWithFile("")
	Animation *animation = Animation::create();
	for (int i = 1; i < 6; i++)
	{
		char szImageFileName[256] = {0};
		sprintf(szImageFileName, "ui/tanks/player_batter_1_up (1).png", i);
		animation->addSpriteFrameWithFileName(szImageFileName);
	}
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	Animate *action = Animate::create(animation);
	this->runAction(action);
	
}
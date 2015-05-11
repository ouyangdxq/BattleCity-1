#include "MapLayer.h"

using namespace cocos2d;
bool MapLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}
Vec2 MapLayer::getObjectPoint(TMXObjectGroup *group, const char *object)
{
	Vec2 point;
	auto ojPoint = _object->getObject(object);
	CCASSERT(!ojPoint.empty(), "playerPoint object not found");
	point.x = ojPoint["x"].asInt();
	point.y = ojPoint["y"].asInt();
	return point;
}
void MapLayer::initWithMap(int leve, int tlevel, int life)
{
	_leve = leve;
	_gameMap = TMXTiledMap::create(String::createWithFormat("map%d.tmx", leve)->getCString());
	_gameMap->setPosition(0, 0);
	this->addChild(_gameMap, -1);

	_background = _gameMap->layerNamed("Background");
	_meta = _gameMap->layerNamed("meta");
	_meta->setVisible(false);
	_brick = _gameMap->layerNamed("brick");

	//创建玩家坦克
	_object = _gameMap->getObjectGroup("Objects");
	CCASSERT(NULL != _object, "'Objects' object group not found!");
	//_player = TankSprite::initwithDelegate(leve, (TankLevel) tlevel);
	//Vec2 playerPoint = getObjectPoint(_object, "player");
	//_player->setPosition(playerPoint.x, playerPoint.y);
	//this->addChild(_player);

}
Vec2 MapLayer::tileCoordForPosition(Vec2 pos)
{
	int x = pos.x / _gameMap->getTileSize().width;
	int y = ((_gameMap->getMapSize().height * _gameMap->getTileSize().height) - pos.y) / _gameMap->getTileSize().height;
	return Vec2(x, y);
}
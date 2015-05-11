#include "GameScene.h"


using namespace cocos2d;


Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;

}
bool GameScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 使用瓦片地图
	//std::string file = "map.tmx";
	//auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	//_tileMap = TMXTiledMap::createWithXML(str->getCString(),"");
	//_background = _tileMap->layerNamed("Background");
	//_tileMap->setAnchorPoint(Vec2(0, 0));

	//addChild(_tileMap, -1);

	_tileMap = MapLayer::create();
	_tileMap->initWithMap(1, 1, 2); //关卡， 坦克等级， 坦克生命个数
	_tileMap->setPosition(Vec2(0, 0));
	addChild(_tileMap, -1);

	// 创建玩家的坦克
	//TMXObjectGroup *objects = _tileMap->getObjectGroup("Objects");
	//CCASSERT(NULL != objects, "'Objects' object group not found!");
	//auto playerPoint = objects->getObject("player");
	//CCASSERT(!playerPoint.empty(), "playerPoint object not found");
	//int x = playerPoint["x"].asInt();
	//int y = playerPoint["y"].asInt();
	//_player = TankSprite::initwithDelegate(2, TankLevel::StarOne);
	//_player->setPosition(x,y);
	//this->addChild(_player);

	//
	//_meta = _tileMap->getLayer("meta");
	//_meta->setVisible(false);

	_controlLayer = ControlLayer::create();
	_controlLayer->_mapLayer = _tileMap;
	_controlLayer->addPlayer(2, 1);
	this->addChild(_controlLayer, 1);

	return true;
}


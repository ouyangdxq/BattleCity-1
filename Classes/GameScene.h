#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__
#include "HelloWorldScene.h"
#include "MapLayer.h"
#include "ControlLayer.h"
#include "TankSprite.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

private:
	//cocos2d::TMXTiledMap *_tileMap;
	MapLayer* _tileMap;
	cocos2d::TMXLayer *_background;
	cocos2d::TMXLayer *_meta;
	cocos2d::Sprite *_player;
	ControlLayer *_controlLayer;
};

#endif 
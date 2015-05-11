#ifndef MAPLAYER_H
#define MAPLAYER_H

#include "cocos2d.h"

using namespace cocos2d;

class MapLayer: public Layer
{
public:
	virtual bool init();
	static Scene* scene();
	CREATE_FUNC(MapLayer);
	void initWithMap(int leve, int level, int life);
	Vec2 getObjectPoint(TMXObjectGroup *group, const char *object);
	Vec2 tileCoordForPosition(Vec2 pos);

	int _leve;
	TMXTiledMap *_gameMap;
	TMXLayer* _background;
	TMXLayer* _meta;
	TMXObjectGroup* _object;
	TMXLayer* _brick;

};

#endif // !MAPLAYER_H




#include "cocos2d.h"
#include "Joystick.h"
#include "TankSprite.h"
#include "MapLayer.h"
#include "TankSprite.h"

class ControlLayer: public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(ControlLayer);
	void addPlayer(int life, int tlevel);


	MapLayer* _mapLayer;
	Joystick* _joystick;
	TankSprite *_player;

private:
	void addJoystick();
	void update(float t);
	
};




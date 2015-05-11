#include "HelloWorldScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 开始菜单， 第一二个参数分别是未点击和点击时显示的图片
	auto startItem = MenuItemImage::create("ui/game_start.png",
											"ui/game_start.png",
											CC_CALLBACK_1(HelloWorld::menuStartCallback, this));
	startItem->setPosition(Vec2(origin.x + visibleSize.width/4,
								origin.y + visibleSize.height/3 * 2));

    auto closeItem = MenuItemImage::create(
                                           "ui/game_exit.png",
                                           "ui/game_exit.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width/4,
                                origin.y + visibleSize.height/3 * 2 - startItem->getContentSize().height - 30));
	// 
    auto menu = Menu::create(closeItem, startItem, NULL);
    // 将菜单加入当前层
	menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	// 开始背景
    auto startBackground = Sprite::create("ui/start_background.png");

	// 设置精灵相对于屏幕的位置（绝对坐标系）
    startBackground->setPosition(Vec2(visibleSize.width/2 + origin.x, 0));

	// 设置锚点
	startBackground->setAnchorPoint(Vec2(0.5, 0));
	// 设置精灵的Tag，之后可以通过标签找到这个精灵，并对这个精灵进行操作
	startBackground->setTag(START_BACKGROUD);
	// 将背景精灵添加到层中。其中第二个参数0是设置可见优先权，数值越小优先权越小，如果有其他的精灵的优先权比他大时，他会被遮挡住
    this->addChild(startBackground, 0);

    return true;
}
// 开始游戏
void HelloWorld::menuStartCallback(Ref* pSender)
{
	auto scene = GameScene::createScene();
	auto gameScene = TransitionFade::create(1.0f, scene);
	Director::getInstance()->replaceScene(gameScene);
}
// 结束游戏
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

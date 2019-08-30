#include"helpScene.h"
#include"MainMenu.h"
Scene* help::createScene()
{
	auto scene = Scene::create();
	auto layer = help::create();
	scene->addChild(layer);
	return scene;
}
bool help::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getWinSize();

	//添加背景
	auto spriteBK = Sprite::create("helpbg.png");
	spriteBK->setPosition(Point(size.width / 2, size.height / 2));
	this->addChild(spriteBK);
	
	//规则说明
	auto laber = Label::create("information", "arial.ttf", 25);
	
	//返回按钮
	auto menuItemBack = MenuItemImage::create("back1.png", "back1.png", CC_CALLBACK_1(help::menuCallBack, this));
	auto menu = Menu::create(menuItemBack, NULL);
	menu->setPosition(Point::ZERO);
	menuItemBack->setPosition(Point(330,40));
	this->addChild(menu);
	return true;
}
void help::menuCallBack(Ref * object)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}
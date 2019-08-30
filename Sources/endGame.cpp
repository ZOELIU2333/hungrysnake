#include"endGame.h"
#include"MainMenu.h"
#include"gameScene.h"
Scene* endGame::createScene()
{
	auto scene = Scene::create();
	auto layer = endGame::create();
	scene->addChild(layer);
	return scene;
}
bool endGame::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getWinSize();

	//Ìí¼Ó±³¾°
	auto spriteBK = Sprite::create("gamebg.png");
	spriteBK->setPosition(Point(size.width / 2, size.height / 2));
	spriteBK->setOpacity(100);
	this->addChild(spriteBK);

	//±³¾°×ÖÄ»
	

	Label* label = Label::create("YOU ARE DEAD", "arial.ttf", 50);
	label->setColor(ccc3(255,0,0));
	label->setPosition(Point(size.width - 240, size.height - 80));
	this->addChild(label);

	//·µ»Ø°´Å¥
	auto menuItemBack = MenuItemImage::create("back1.png", "back1.png", CC_CALLBACK_1(endGame::menuCallBack, this));
	menuItemBack->setTag(1);
	auto menuItemagain = MenuItemImage::create("again.png", "again.png", CC_CALLBACK_1(endGame::menuCallBack, this)); \
	menuItemagain->setTag(2);
	auto menu = Menu::create(menuItemagain,menuItemBack, NULL);
	menu->setPosition(Point::ZERO);
	menuItemBack->setPosition(Point(size.width / 2, size.height / 2-80));
	menuItemagain->setPosition(Point(size.width / 2, size.height / 2));
	this->addChild(menu);
	return true;
}
void endGame::menuCallBack(Ref * object)
{
	auto scene = MainMenu::createScene();
	auto target = (Node *)object;
	switch (target->getTag())
	{
	case 1:
		scene = MainMenu::createScene();
		break;
	case 2:
		scene = game::createScene();
		break;
	default:
		break;
	}
	Director::getInstance()->replaceScene(scene);
}
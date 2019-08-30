#include"MainMenu.h"
#include"gameScene.h"
#include"helpScene.h"
#include"endGame.h"
#include"HelloWorldScene.h"
Scene* MainMenu::createScene()
{
	auto scene = Scene::create();//��������
	auto layer = MainMenu::create();//���������ͼ��
	scene->addChild(layer);//�Ѹ�ͼ����ӽ�scene����
	return scene;
}

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//��ӱ���
	auto size = Director::getInstance()->getWinSize();
	auto sprite = Sprite::create("bg.png");
	sprite->setPosition(Point(size.width / 2, size.height / 2));
	this->addChild(sprite);
	//��Ӳ˵���Ŀ
	auto menuItemStart = MenuItemImage::create("start.png", "start.png", CC_CALLBACK_1(MainMenu::menuCallback, this));
	menuItemStart->setTag(1);
	auto menuItemHelp = MenuItemImage::create("help.png", "help.png", CC_CALLBACK_1(MainMenu::menuCallback, this));
	menuItemHelp->setTag(2);
	auto menu = Menu::create(menuItemStart,menuItemHelp,NULL);
	menu->setPosition(Point::ZERO);
	menuItemStart->setPosition(Point(size.width/2,
		size.height/2+10));
	menuItemHelp->setPosition(Point(size.width / 2,
		size.height / 2-55));
	this->addChild(menu);
	return true;
}

void MainMenu::menuCallback(Ref* object)
{

	auto target = (Node *)object;
	Scene *scene;
	switch (target->getTag())
	{
	case 1:
		scene = game::createScene();
		break;
	case 2:
		scene = help::createScene();
		break;
	default:
		break;
	}
	// �õ����á��滻�� ���ڵĳ�����ע�����滻��
	Director::getInstance()->replaceScene(scene);
}
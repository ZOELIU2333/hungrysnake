#include"gameScene.h"
#include"MainMenu.h"
#include"endGame.h"
Scene* game::createScene()
{
	auto scene = Scene::create();
	auto layer = game::create();
	scene->addChild(layer);
	return scene;
}

SnakeNode* SnakeNode::create(int type) {
	SnakeNode *pRet = new SnakeNode;
	if (pRet && pRet->init(type))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

void SnakeNode::setPositionRC(int row, int col)
{
	this->m_col = col;
	this->m_row = row;
	setPosition(Point(col * 10, row * 10));
}
//创建蛇头 身体 食物
bool SnakeNode::init(int type)
{
	if (!Sprite::init())
	{
		return false;
	}
	switch (type)
	{
	case 1://蛇头
	{
		auto spriteHead = Sprite::create("body.png");
		spriteHead->setAnchorPoint(Point::ZERO);
		this->addChild(spriteHead);
		m_dir = ENUM_DIR::DIR_RIGHT;
		break;
	}
	case 2://身体
	{
		auto spriteBody = Sprite::create("body.png");
		spriteBody->setAnchorPoint(Point::ZERO);
		this->addChild(spriteBody);
		break;
	}
	case 3://食物
	{
		auto spriteFood = Sprite::create("food.png");
		this->addChild(spriteFood);
		spriteFood->setAnchorPoint(Point::ZERO);
		m_dir = ENUM_DIR::DIR_STOP;
		break;
	}
	default:
		break;
	}
	return true;
}


bool game::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getWinSize();

	//添加背景
	auto spriteBK = Sprite::create("gamebg.png");
	spriteBK->setPosition(Point(size.width / 2, size.height / 2));
	spriteBK->setOpacity(100);
	this->addChild(spriteBK);

	//添加蛇头
	spHead = SnakeNode::create(1);
	spHead->m_col = 0;
	spHead->m_row = 0;
	this->addChild(spHead);

	//添加食物
	spFood = SnakeNode::create(3);
	int row = rand() % 32;
	int col = rand() % 32;	
	spFood->setPositionRC(row,col);
	this->addChild(spFood);

	//绘制地图
	auto draw = DrawNode::create();
	draw->setAnchorPoint(Point::ZERO);
	draw->drawSegment(Point(0, 0), Point(320, 0), 1, Color4F(1, 1, 1, 1));
	draw->drawSegment(Point(0, 320), Point(320, 320),1, Color4F(1, 1, 1, 1));
	draw->drawSegment(Point(0, 0), Point(0, 320), 1, Color4F(1, 1, 1, 1));
	draw->drawSegment(Point(320, 0), Point(320, 320), 1, Color4F(1, 1, 1, 1));;
	this->addChild(draw);

	//分数显示
	m_score = 0;
	auto labelScore = Label::create("SCORE:0", "arial.ttf", 25);
	labelScore->setTag(110);
	labelScore->setPosition(Point(size.width - 90, size.height - 50));
	this->addChild(labelScore);

	//返回按钮
	auto menuItemBack = MenuItemImage::create("back.png", "back.png", CC_CALLBACK_1(game::menuCallBack,this));
	auto menu = Menu::create(menuItemBack, NULL);
	menu->setPosition(Point::ZERO);
	menuItemBack->setPosition(Point(size.width-80, 25));
	this->addChild(menu);

	auto label = Label::create("选项", "宋体", 25);
	auto menuItemOptions = MenuItemLabel::create(label,CC_CALLBACK_1(game::menuCallBack, this));
	auto menu1 = Menu::create(menuItemOptions, NULL);
	menu->setPosition(Point::ZERO);
	menuItemOptions->setPosition(Point(size.width - 80, 50));
	this->addChild(menu1);


	//计划任务
	this->schedule(schedule_selector(game::gameLogic), 0.2);

	//加入触摸事件 加入事件侦听
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan=[&](Touch *t, Event *e) {
		//改变贪吃蛇移动的方向
		int col = t->getLocation().x / 10;
		int row = t->getLocation().y / 10;
		int spHeadCol = spHead->getPositionX() / 10;
		int spHeadRow = spHead->getPositionY() / 10;
		if (abs(spHeadCol - col) > abs(spHeadRow - row))
		{
			if (spHeadCol < col&&spHead->m_dir!= ENUM_DIR::DIR_LEFT)
			{
				spHead->m_dir = ENUM_DIR::DIR_RIGHT;
			}
			else if(spHeadCol >= col&&spHead->m_dir != ENUM_DIR::DIR_RIGHT)
			{
				spHead->m_dir = ENUM_DIR::DIR_LEFT;
			}
		}
		else
		{
			if (spHeadRow < row&&spHead->m_dir != ENUM_DIR::DIR_DOWN)
			{
				spHead->m_dir = ENUM_DIR::DIR_UP;
			}
			else if (spHeadRow >= row&& spHead->m_dir != ENUM_DIR::DIR_UP)
			{
				spHead->m_dir = ENUM_DIR::DIR_DOWN;
			}
		}
		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}


//游戏逻辑的实现
void game::gameLogic(float t)
{
	moveBody();
	switch (spHead->m_dir) {
	case ENUM_DIR::DIR_RIGHT:
		spHead->runAction(MoveBy::create(0.3, Point(10, 0)));
		spHead->m_col++;
		break;
	case ENUM_DIR::DIR_LEFT:
		spHead->runAction(MoveBy::create(0.3, Point(-10, 0)));
		spHead->m_col--;
		break;
	case ENUM_DIR::DIR_UP:
		spHead->runAction(MoveBy::create(0.3, Point(0, 10)));
		spHead->m_row++;
		break;
	case ENUM_DIR::DIR_DOWN:
		spHead->runAction(MoveBy::create(0.3, Point(0, -10)));
		spHead->m_row--;
		break;
	}
	//吃到食物碰撞检测
	if (spFood->m_col == spHead->m_col&&spFood->m_row == spHead->m_row)
	{ 

		//分数增加
		this->m_score += 100;
		Label *label = (Label *)this->getChildByTag(110);
		char strscore[20];
		sprintf(strscore, "SCORE:%d", m_score);
		label->setString(strscore);

		//食物产生新的位置
		int row = rand() % 32;
		int col = rand() % 32;
		spFood->setPositionRC(row, col);

		//添加身体节点
		newBody();
	}

	//撞墙检测
	if (spHead->m_col > 32 || spHead->m_row > 32 || spHead->m_col < 0 || spHead->m_row < 0)
	{
		auto scene = endGame::createScene();
		Director::getInstance()->replaceScene(scene);
	}

	//撞到自己的身体检测
	for (auto bodyNode : allBody)//遍历allbody中的所有元素
	{
		if (spHead->m_col == bodyNode->m_col&&spHead->m_row == bodyNode->m_row)
		{
			auto scene = endGame::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	}
}

//生成新的身体节点
void game::newBody()
{
	auto bodyNode = SnakeNode::create(2);

	//设置节点的方向
	if (allBody.size() > 0)
	{
		auto lastbody = allBody.at(allBody.size() - 1);
		bodyNode->m_dir = lastbody->m_dir;
		switch (bodyNode->m_dir)
		{
		case ENUM_DIR::DIR_UP:
			bodyNode->setPositionRC(lastbody->m_row - 1, lastbody->m_col);
			break;
		case ENUM_DIR::DIR_DOWN:
			bodyNode->setPositionRC(lastbody->m_row + 1, lastbody->m_col);
			break;
		case ENUM_DIR::DIR_LEFT:
			bodyNode->setPositionRC(lastbody->m_row, lastbody->m_col + 1);
			break;
		case ENUM_DIR::DIR_RIGHT:
			bodyNode->setPositionRC(lastbody->m_row, lastbody->m_col-1);
			break;
		default:
			break;
		}
	}
	//只有蛇头
	else
	{
		bodyNode->m_dir = spHead->m_dir;
		switch (bodyNode->m_dir)
		{
		case ENUM_DIR::DIR_UP:
			bodyNode->setPositionRC(spHead->m_row-1, spHead->m_col);
			break;
		case ENUM_DIR::DIR_DOWN:
			bodyNode->setPositionRC(spHead->m_row + 1, spHead->m_col);
			break;
		case ENUM_DIR::DIR_LEFT:
			bodyNode->setPositionRC(spHead->m_row , spHead->m_col+1);
			break;
		case ENUM_DIR::DIR_RIGHT:
			bodyNode->setPositionRC(spHead->m_row, spHead->m_col-1);
			break;
		default:
			break;
		}
	}
	//添加节点至当前图层
	this->addChild(bodyNode);
	//将新生成的节点加入集合
	allBody.pushBack(bodyNode);
}

//移动身体节点
void game::moveBody()
{
	//若只能头结点
	if (allBody.size() == 0)
	{
		return;
    }
	for (auto bodyNode : allBody)//遍历allbody中的所有元素
	{
		switch (bodyNode->m_dir)
		{
		case ENUM_DIR::DIR_UP:
			bodyNode->runAction(MoveBy::create(0.3, Point(0, 10)));
			bodyNode->m_row++;
			break;
		case ENUM_DIR::DIR_DOWN:
			bodyNode->runAction(MoveBy::create(0.3, Point(0, -10)));
			bodyNode->m_row--;
			break;
		case ENUM_DIR::DIR_LEFT:
			bodyNode->runAction(MoveBy::create(0.3, Point(-10, 0)));
			bodyNode->m_col--;
			break;
		case ENUM_DIR::DIR_RIGHT:
			bodyNode->runAction(MoveBy::create(0.3, Point(10, 0)));
			bodyNode->m_col++;
			break;
		default:
			break;
		}
	}
	//移动完之后 改变每一个身体节点的方向 与前一个节点的方向相等
	for (int i = allBody.size()-1; i > 0; i--)
	{
		allBody.at(i)->m_dir = allBody.at(i - 1)->m_dir;
	}
	allBody.at(0)->m_dir = spHead->m_dir;
}

void game::menuCallBack(Ref * object)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}
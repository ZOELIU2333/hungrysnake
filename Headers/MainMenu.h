#include"cocos2d.h"
USING_NS_CC;

class MainMenu:public Layer{
public:
	static Scene *createScene();
	CREATE_FUNC(MainMenu);
	virtual bool init();
	void menuCallback(Ref* object);
};

#include"cocos2d.h"
USING_NS_CC;

class help :public Layer {
public:
	static Scene *createScene();
	CREATE_FUNC(help);
	virtual bool init();
	void menuCallBack(Ref * object);
};
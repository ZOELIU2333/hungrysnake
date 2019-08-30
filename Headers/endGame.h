#include"cocos2d.h"
USING_NS_CC;

class endGame :public Layer {
public:
	static Scene *createScene();
	CREATE_FUNC(endGame);
	virtual bool init();
	void menuCallBack(Ref * object);
};
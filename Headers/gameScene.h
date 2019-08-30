#include"cocos2d.h"
USING_NS_CC;


//方向
enum class ENUM_DIR {
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_STOP
};

//定义蛇类
class SnakeNode :public Sprite
{
public:
	enum ENUM_DIR m_dir;//蛇的方向
	int nodetype;//1蛇头 2身体 3食物
	int m_row, m_col;//定义行列
	static SnakeNode* create(int type);//创造蛇节点，跟CREATE_FUNC类似
	virtual bool init(int type);//初始化
	void setPositionRC(int row, int col);//设定节点的坐标
};
class game :public Layer {
public:
	SnakeNode* spHead;//蛇头
	SnakeNode* spFood;//食物
	Vector<SnakeNode *> allBody;//记录身体节点个数
	int m_score;//总分	
	static Scene *createScene();
	CREATE_FUNC(game);
	virtual bool init();
	void gameLogic(float t);//游戏逻辑的实现
	void newBody();//添加一个新的身体节点
	void moveBody();//移动身体节点
	void menuCallBack(Ref * object);
};
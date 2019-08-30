#include"cocos2d.h"
USING_NS_CC;


//����
enum class ENUM_DIR {
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_STOP
};

//��������
class SnakeNode :public Sprite
{
public:
	enum ENUM_DIR m_dir;//�ߵķ���
	int nodetype;//1��ͷ 2���� 3ʳ��
	int m_row, m_col;//��������
	static SnakeNode* create(int type);//�����߽ڵ㣬��CREATE_FUNC����
	virtual bool init(int type);//��ʼ��
	void setPositionRC(int row, int col);//�趨�ڵ������
};
class game :public Layer {
public:
	SnakeNode* spHead;//��ͷ
	SnakeNode* spFood;//ʳ��
	Vector<SnakeNode *> allBody;//��¼����ڵ����
	int m_score;//�ܷ�	
	static Scene *createScene();
	CREATE_FUNC(game);
	virtual bool init();
	void gameLogic(float t);//��Ϸ�߼���ʵ��
	void newBody();//���һ���µ�����ڵ�
	void moveBody();//�ƶ�����ڵ�
	void menuCallBack(Ref * object);
};
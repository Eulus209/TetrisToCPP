#pragma once
#include<vector>
#include<graphics.h>
#include"Block.h"
using namespace std;
class Tetris
{

public:
	//���캯��
	Tetris(int rows,int cols,int left,int top,int block_size);//�������󲿱߽磬�ϲ��߽磬ÿ�������С
	//��ʼ��
	void init();
	//��ʼ��Ϸ
	void play();

private:
	//�û�����
	void keyEvent();
	//��Ⱦ
	void updateWindow();
	//��ȡ���ʱ��(ms)
	int getDelay();
	//����
	void drop();
	//�������һ�е�����
	void clearLine();
	//�����ƶ�
	void moveLeftRight(int offset);
	//��ת
	void rotate();
	//���Ƶ�ǰ����
	void drawScore();
	//�����Ϸ�Ƿ����
	void checkOver();
	//�������
	void saveScore();
	//������Ϸ����
	void displayOver();

private:
	//��ʱ����
	int delay;
	//ʱ�����
	bool update;

	vector<vector<int>> map;//0:û�з���,1~7:��1~7�ֶ���˹����
	int rows;
	int cols;
	int leftMargin;
	int topMargin;
	int blockSize;
	IMAGE imgBg;
	//��ǰ�����Ԥ�淽�飬���ݷ���
	Block* curBlock;
	Block* nextBlock;
	Block bakBlock;

	int score;//��ǰ����
	int highestScore;//��߷�
	int level;//��ǰ�ؿ�
	int lineCount;//��ǰ�Ѿ�����������
	bool gameOver;//��Ϸ�Ƿ��Ѿ�����

	IMAGE imgOver;
	IMAGE imgWin;
};


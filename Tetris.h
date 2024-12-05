#pragma once
#include<vector>
#include<graphics.h>
#include"Block.h"
using namespace std;
class Tetris
{

public:
	//构造函数
	Tetris(int rows,int cols,int left,int top,int block_size);//长，宽，左部边界，上部边界，每个方块大小
	//初始化
	void init();
	//开始游戏
	void play();

private:
	//用户输入
	void keyEvent();
	//渲染
	void updateWindow();
	//获取间隔时间(ms)
	int getDelay();
	//下移
	void drop();
	//清楚满足一行的条件
	void clearLine();
	//左右移动
	void moveLeftRight(int offset);
	//旋转
	void rotate();
	//绘制当前分数
	void drawScore();
	//检查游戏是否结束
	void checkOver();
	//保存分数
	void saveScore();
	//更新游戏画面
	void displayOver();

private:
	//延时毫秒
	int delay;
	//时候更新
	bool update;

	vector<vector<int>> map;//0:没有方块,1~7:第1~7种俄罗斯方块
	int rows;
	int cols;
	int leftMargin;
	int topMargin;
	int blockSize;
	IMAGE imgBg;
	//当前方块和预告方块，备份方块
	Block* curBlock;
	Block* nextBlock;
	Block bakBlock;

	int score;//当前分数
	int highestScore;//最高分
	int level;//当前关卡
	int lineCount;//当前已经消除多少行
	bool gameOver;//游戏是否已经结束

	IMAGE imgOver;
	IMAGE imgWin;
};


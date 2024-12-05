#pragma once
#include <graphics.h>//需要安装easyx图形库
#include <vector>
using namespace std;
struct Point {
	int row;
	int col;
};


class Block
{
public:
	//构造函数
	Block();
	//移动
	void drop();//下降
	void moveLeftRight(int offset);//左右移（正负左右）
	void rotate();//旋转
	void draw(int leftMargin,int topMargin);
	static IMAGE** getImages();
	Block& operator=(const Block& other);
	
	bool blockInMap(const vector<vector<int>> &map);
	//Point* getSmallBlocks();

	void solidify(vector<vector<int>>& map);
	int getBlockType();

private:
	int blockType;//方块类型
	Point smallBlocks[4];
	IMAGE* img;

	static IMAGE* imgs[7];//int data[7];//int** getdate()
	static int size;
};


#pragma once
#include <graphics.h>//��Ҫ��װeasyxͼ�ο�
#include <vector>
using namespace std;
struct Point {
	int row;
	int col;
};


class Block
{
public:
	//���캯��
	Block();
	//�ƶ�
	void drop();//�½�
	void moveLeftRight(int offset);//�����ƣ��������ң�
	void rotate();//��ת
	void draw(int leftMargin,int topMargin);
	static IMAGE** getImages();
	Block& operator=(const Block& other);
	
	bool blockInMap(const vector<vector<int>> &map);
	//Point* getSmallBlocks();

	void solidify(vector<vector<int>>& map);
	int getBlockType();

private:
	int blockType;//��������
	Point smallBlocks[4];
	IMAGE* img;

	static IMAGE* imgs[7];//int data[7];//int** getdate()
	static int size;
};


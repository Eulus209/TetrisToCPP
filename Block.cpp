#include "Block.h"
#include <stdlib.h>

IMAGE* Block::imgs[7] = { NULL };
int Block::size = 36;
Block::Block()
{
	if (imgs[0] == NULL)
	{
		//初始化
		//切割
		IMAGE imgTmp;
		loadimage(&imgTmp, "./res/tiles.png");
		SetWorkingImage(&imgTmp);
		for (int i = 0;i < 7;++i)
		{
			imgs[i] = new IMAGE;
			getimage(imgs[i],i*size,0,size,size);
		}
		SetWorkingImage();//恢复工作区
	}

	//俄罗斯方块存储方块类型
	int blocks[7][4] = {
		1,3,5,7, // I
		2,4,5,7, // Z 1型
		3,5,4,6, // Z 2型
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // 田
	};
	//随机生成一种俄罗斯方块
	blockType=1+rand() % 7;//1 + 0~7 = 1~7
	//初始化smallBlocks数组
	for (int i = 0;i < 4;++i)
	{
		int value = blocks[blockType - 1][i];
		smallBlocks[i].row = value / 2;
		smallBlocks[i].col = value % 2;
	}

	img = imgs[blockType - 1];

}

void Block::drop()
{
	for (int i = 0;i < 4;++i)
	{
		smallBlocks[i].row++;
	}
	//C++11
	/*for (auto &block : smallBlocks)
	{
		block.row++;
	}*/
}

void Block::moveLeftRight(int offset)
{
	for (int i = 0;i < 4;++i)
	{
		smallBlocks[i].col+= offset;
	}
}

void Block::rotate()
{
	Point p = smallBlocks[1];
	for (int i=0;i < 4;++i)
	{
		Point tmp = smallBlocks[i];
		smallBlocks[i].col = p.col - tmp.row + p.row;
		smallBlocks[i].row = p.row + tmp.col - p.col;
	}
}

void Block::draw(int leftMargin, int topMargin)
{
	for (int i = 0;i < 4;++i)
	{
		int x = leftMargin + smallBlocks[i].col*size;
		int y = topMargin + smallBlocks[i].row*size;
		putimage(x, y, img);
	}
}

IMAGE** Block::getImages()
{
	return imgs;
}

Block& Block::operator=(const Block& other)
{
	if (this == &other)return *this;
	this->blockType = other.blockType;

	for (int i = 0;i < 4;++i)
	{
		this->smallBlocks[i] = other.smallBlocks[i];
	}
	this->img = other.img; // 复制 img 指针
	return *this;
}

bool Block::blockInMap(const vector<vector<int>>& map)
{
	int rows = map.size();
	int cols = map[0].size();
	for (int i = 0;i < 4;++i)
	{
		if (smallBlocks[i].col < 0 || smallBlocks[i].col >= cols ||
			smallBlocks[i].row < 0 || smallBlocks[i].row >= rows ||
			map[smallBlocks[i].row][smallBlocks[i].col])
		{
			return false;
		}
	}
	return true;
}

void Block::solidify(vector<vector<int>>& map)
{
	for (int i = 0;i < 4;++i)
	{
		//设置标记，固化对应位置
		map[smallBlocks[i].row][smallBlocks[i].col] = blockType;
	}
}

int Block::getBlockType()
{
	return blockType;
}

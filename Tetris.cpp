#include "Tetris.h"
#include <stdlib.h>
#include <time.h>
#include "Block.h"
#include<conio.h>
#include<mmsystem.h>
#include<fstream>
#include<iostream>
#include<ostream>
#pragma comment(lib,"winmm.lib")

#define MAX_LEVEL 5
#define RECORD_FILE "recorder.txt"

const int SPPED_NORMAL[MAX_LEVEL] = {500,300,150,100,80};
const int SPEED_QUICK = 30;



Tetris::Tetris(int rows, int cols, int left, int top, int blockSize)
{
	this->rows = rows;
	this->cols = cols;
	leftMargin = left;
	topMargin = top;
	this->blockSize = blockSize;
	for (int i = 0;i < rows;++i)
	{
		vector<int> mapRow;
		for (int j = 0;j < cols;++j)
		{
			mapRow.push_back(0);
		}
		map.push_back(mapRow);
	}
}

void Tetris::init()
{
	mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
	delay = SPPED_NORMAL[0];
	//配置随机种子
	srand(time(NULL));

	initgraph(938,896);//创建游戏窗口

	loadimage(&imgBg, "./res/bg2.png");//加载背景图片
	
	loadimage(&imgWin, "./res/win.png");
	loadimage(&imgOver, "./res/over.png");
	//重新初始化游戏区数据
	for (int i = 0;i < rows;++i)
	{
		for (int j = 0;j < cols;++j)
		{
			map[i][j] = 0;
		}
	}
	score = 0;
	lineCount = 0;
	level = 1;

	//初始化最高分
	ifstream file(RECORD_FILE);
	if (!file.is_open())
	{
		std::cout << RECORD_FILE << "打开失败！" << std::endl;
		highestScore = 0;
	}
	else
	{
		file >> highestScore;
	}
	file.close();//关闭文件
	gameOver = false;
}

void Tetris::play()
{
	init();//初始化
	
	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;

	int timer = 0;
	while (true)
	{
		//接受用户输入
		keyEvent();
		timer += getDelay();//获取上一次循环的间隔时间,第一次调用返回0
		if(timer > delay){
			timer = 0;//保证再次渲染间隔30ms
			drop();
			update = true;//到达延时，渲染游戏画面
		}
		//判断是否开始渲染画面
		if (update)
		{
			update = false;//恢复标记
			updateWindow();//渲染（更新）游戏画面
			clearLine();//判断是否有一行，更新游戏相关数据
		}
		if (gameOver)
		{
			//保存分数
			saveScore();

			//更新游戏界面
			displayOver();

			system("pause");

			init();//重新开局

		}
	}
}

void Tetris::keyEvent()
{
	//char ch;//-128,127
	unsigned char ch;//0,255
	if (_kbhit())
	{
		ch=_getch();
		//如果按下方向键，会自动返回2个字符
		//up--224,72  down--224,80
		//left--224,75  right--224,77
		if (ch == 224)
		{
			ch = _getch();
			switch (ch)
			{
			case 72:
				rotate();
				update = true;
				break;
			case 80:
				delay = SPEED_QUICK;
				break;
			case 75:
				moveLeftRight(-1);
				update = true;
				break;
			case 77:
				moveLeftRight(1);
				update = true;
				break;
			default:
				break;
			}
		}

	}
}

void Tetris::updateWindow()
{
	putimage(0, 0, &imgBg);//绘制背景图片
	IMAGE** imgs = Block::getImages();
	BeginBatchDraw();
	for (int i = 0;i < rows;++i)
	{
		for (int j = 0;j < cols;++j)
		{
			if (map[i][j] == 0)continue;
			int x = j * blockSize + leftMargin;
			int y = i * blockSize + topMargin;
			putimage(x, y, imgs[map[i][j]-1]);
		}
	}
	curBlock->draw(leftMargin, topMargin);
	nextBlock->draw(689, 150);

	drawScore();//绘制分数

	EndBatchDraw();
	/*
	* //测试方块
	* Block block;
	* block.draw(leftMargin,topMargin);
	*/
}
//第一次调用返回0，其余返回距离上次调用的间隔
int Tetris::getDelay()
{
	static unsigned long long lastTime = 0;
	unsigned long long currentTime = GetTickCount();
	if (lastTime == 0)
	{
		lastTime = currentTime;
		return 0;
	}
	else
	{
		int ret = currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}
}

void Tetris::drop()
{
	bakBlock = *curBlock;
	curBlock->drop();

	//下降过程中，位置非法则回退
	if (!curBlock->blockInMap(map))
	{
		//固定方块
		bakBlock.solidify(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;

		//检查游戏是否结束
		checkOver();
	}
	delay = SPPED_NORMAL[level-1];
}

void Tetris::clearLine()
{
	int lines = 0;
	int k = rows - 1;//存储数据行数
	for (int i = rows - 1;i >= 0;--i)
	{
		//检查第i行时候满行
		int count= 0;
		for (int j = 0;j < cols;++j)
		{
			if (map[i][j])
			{
				count++;
			}
			map[k][j] = map[i][j];//一边扫描一边存储
		}
		if (count < cols)
		{
			//不是满行，要存储
			k--;
		}
		else
		{
			lines++;
			//lineCount++;
		}
		
	}
	if (lines > 0)
	{
		//计算得分
		int addScore[4] = { 10,30,60,80 };
		score += addScore[lines - 1];

		mciSendString("play res/xiaochu1.mp3",0,0,0);
		update = true;

		//每一百分一个关卡
		level=(score+99) / 100 ;
		if (level > MAX_LEVEL)
		{
			gameOver=true;
		}
		lineCount += lines;
	}
}

void Tetris::moveLeftRight(int offset)
{
	bakBlock = *curBlock;
	curBlock->moveLeftRight(offset);

	if (!curBlock->blockInMap(map))
	{
		*curBlock = bakBlock;
	}
}

void Tetris::rotate()
{
	if (curBlock->getBlockType() == 7)return;
	bakBlock = *curBlock;
	curBlock->rotate();

	if (!curBlock->blockInMap(map))
	{
		*curBlock = bakBlock;
	}
}

void Tetris::drawScore()
{
	char scoreText[32];
	sprintf_s(scoreText, sizeof(scoreText), "%d", score);

	setcolor(RGB(180, 180, 180));

	LOGFONT f;
	gettextstyle(&f);//获取当前字体
	f.lfHeight = 60;
	f.lfWeight = 30;
	f.lfQuality = ANTIALIASED_QUALITY;//抗锯齿效果
	strcpy_s(f.lfFaceName,sizeof(f.lfFaceName),_T("Segoe UI Black"));
	settextstyle(&f);
	setbkmode(TRANSPARENT);//设置字体为透明背景
	outtextxy(670, 727, scoreText);
	//绘制消除多少行
	sprintf_s(scoreText, sizeof(scoreText), "%d", lineCount);
	gettextstyle(&f);
	int xPos = 224 - f.lfWeight * strlen(scoreText);
	outtextxy(xPos,817, scoreText);
	//绘制当前第几关
	sprintf_s(scoreText, sizeof(scoreText), "%d", level);
	outtextxy(224-30,727, scoreText);

	//绘制最高分
	sprintf_s(scoreText, sizeof(scoreText), "%d", highestScore);
	outtextxy(670, 817, scoreText);

}

void Tetris::checkOver()
{
	gameOver=(curBlock->blockInMap(map) == false);
}

void Tetris::saveScore()
{
	if (score > highestScore)
	{
		highestScore = score;

		ofstream file(RECORD_FILE);
		file << highestScore;
		file.close();
	}
}

void Tetris::displayOver()
{
	mciSendString("stop res/bg.mp3", 0, 0, 0);

	//是胜利结束还是失败结束
	if (level <= MAX_LEVEL)
	{
		putimage(262, 361, &imgOver);
		mciSendString("play res/over.mp3", 0, 0, 0);
	}
	else
	{
		putimage(262, 361, &imgWin);
		mciSendString("play res/win.mp3", 0, 0, 0);
	}
}

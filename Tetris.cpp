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
	//�����������
	srand(time(NULL));

	initgraph(938,896);//������Ϸ����

	loadimage(&imgBg, "./res/bg2.png");//���ر���ͼƬ
	
	loadimage(&imgWin, "./res/win.png");
	loadimage(&imgOver, "./res/over.png");
	//���³�ʼ����Ϸ������
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

	//��ʼ����߷�
	ifstream file(RECORD_FILE);
	if (!file.is_open())
	{
		std::cout << RECORD_FILE << "��ʧ�ܣ�" << std::endl;
		highestScore = 0;
	}
	else
	{
		file >> highestScore;
	}
	file.close();//�ر��ļ�
	gameOver = false;
}

void Tetris::play()
{
	init();//��ʼ��
	
	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;

	int timer = 0;
	while (true)
	{
		//�����û�����
		keyEvent();
		timer += getDelay();//��ȡ��һ��ѭ���ļ��ʱ��,��һ�ε��÷���0
		if(timer > delay){
			timer = 0;//��֤�ٴ���Ⱦ���30ms
			drop();
			update = true;//������ʱ����Ⱦ��Ϸ����
		}
		//�ж��Ƿ�ʼ��Ⱦ����
		if (update)
		{
			update = false;//�ָ����
			updateWindow();//��Ⱦ�����£���Ϸ����
			clearLine();//�ж��Ƿ���һ�У�������Ϸ�������
		}
		if (gameOver)
		{
			//�������
			saveScore();

			//������Ϸ����
			displayOver();

			system("pause");

			init();//���¿���

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
		//������·���������Զ�����2���ַ�
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
	putimage(0, 0, &imgBg);//���Ʊ���ͼƬ
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

	drawScore();//���Ʒ���

	EndBatchDraw();
	/*
	* //���Է���
	* Block block;
	* block.draw(leftMargin,topMargin);
	*/
}
//��һ�ε��÷���0�����෵�ؾ����ϴε��õļ��
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

	//�½������У�λ�÷Ƿ������
	if (!curBlock->blockInMap(map))
	{
		//�̶�����
		bakBlock.solidify(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;

		//�����Ϸ�Ƿ����
		checkOver();
	}
	delay = SPPED_NORMAL[level-1];
}

void Tetris::clearLine()
{
	int lines = 0;
	int k = rows - 1;//�洢��������
	for (int i = rows - 1;i >= 0;--i)
	{
		//����i��ʱ������
		int count= 0;
		for (int j = 0;j < cols;++j)
		{
			if (map[i][j])
			{
				count++;
			}
			map[k][j] = map[i][j];//һ��ɨ��һ�ߴ洢
		}
		if (count < cols)
		{
			//�������У�Ҫ�洢
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
		//����÷�
		int addScore[4] = { 10,30,60,80 };
		score += addScore[lines - 1];

		mciSendString("play res/xiaochu1.mp3",0,0,0);
		update = true;

		//ÿһ�ٷ�һ���ؿ�
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
	gettextstyle(&f);//��ȡ��ǰ����
	f.lfHeight = 60;
	f.lfWeight = 30;
	f.lfQuality = ANTIALIASED_QUALITY;//�����Ч��
	strcpy_s(f.lfFaceName,sizeof(f.lfFaceName),_T("Segoe UI Black"));
	settextstyle(&f);
	setbkmode(TRANSPARENT);//��������Ϊ͸������
	outtextxy(670, 727, scoreText);
	//��������������
	sprintf_s(scoreText, sizeof(scoreText), "%d", lineCount);
	gettextstyle(&f);
	int xPos = 224 - f.lfWeight * strlen(scoreText);
	outtextxy(xPos,817, scoreText);
	//���Ƶ�ǰ�ڼ���
	sprintf_s(scoreText, sizeof(scoreText), "%d", level);
	outtextxy(224-30,727, scoreText);

	//������߷�
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

	//��ʤ����������ʧ�ܽ���
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

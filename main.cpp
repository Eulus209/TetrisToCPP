/*
1. ������Ŀ
2. �����ز�
3. C++����
4. ���C++��ģ�飨�ࣩ�����飨Block������Ϸ��Tetris���ࡿ
5. ��Ƹ���ģ�����Ҫ�ӿ�
6. ������Ϸ

*/
#include "Tetris.h"

int main(void)
{
	Tetris game(20,10,263,133,36);//���������󲿱߽磬�ϲ��߽磬ÿ�������С
	game.play();
	return 0;
}
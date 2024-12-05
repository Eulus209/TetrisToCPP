/*
1. 创建项目
2. 导入素材
3. C++开发
4. 设计C++的模块（类）【方块（Block）和游戏（Tetris）类】
5. 设计各个模块的主要接口
6. 启动游戏

*/
#include "Tetris.h"

int main(void)
{
	Tetris game(20,10,263,133,36);//长，宽，左部边界，上部边界，每个方块大小
	game.play();
	return 0;
}

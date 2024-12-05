# 项目是使用EasyX图形库开发的经典俄罗斯方块游戏的C++实现。该游戏提供了一个图形界面和多种功能，以增强游戏体验。

## 功能

- **随机生成方块**：每个方块均随机生成，以模拟经典的俄罗斯方块体验。
- **方块移动**：实现了方块下降、左右移动和旋转的功能。
- **消除行**：填满的行将被清除，分数会相应更新。
- **关卡进阶**：游戏包括关卡进阶，随着玩家分数的增加，游戏难度逐渐增加。
- **分数管理**：追踪当前分数和保存在文件中的最高分，并在屏幕上显示当前分数等级。
- **游戏结束检测**：自动检测游戏结束，提供相应的图形和声音效果。
- **音效**：包括背景音乐和消除行及游戏结束的音效。
- **图形界面**：利用EasyX进行图形操作，提供视觉上吸引人的游戏窗口。

## 文件概览

- `Block.h` 和 `Block.cpp`：实现了`Block`类，负责管理俄罗斯方块（Tetromino）的属性和行为。
- `Tetris.h` 和 `Tetris.cpp`：实现了`Tetris`类，用于协调游戏流程、管理游戏状态以及处理输入/输出。
- `main.cpp`：包含`main`函数，用于初始化并启动游戏。

## 依赖项

- **EasyX图形库**：本游戏依赖EasyX进行图形操作，确保在开发环境中正确安装并链接了EasyX。

## 运行步骤

1. **克隆仓库**：将此仓库克隆至本地机器。
2. **安装依赖**：确保已安装EasyX图形库。
3. **构建项目**：使用支持C++11或以上版本的C++编译器。
4. **运行可执行文件**：通过运行编译后的可执行文件开始游戏。

## 游戏说明

- **开始游戏**：执行编译程序开始游戏。
- **移动方块**：
  - 使用箭头键左移、右移或下移方块。
  - 使用上方向键旋转方块。
- **游戏目标**：尽可能多地清除行以获得最高分数。
- **结束游戏**：当方块到达屏幕顶部无法继续移动时，游戏结束。


# Game

This project is a C++ implementation of the classic Tetris game using the EasyX graphics library for rendering. The game provides a graphical interface and a variety of features to enhance the gaming experience.

## Features

- **Random Tetromino Generation**: Each block is randomly generated to simulate the classic Tetris experience.
- **Block Movement**: Implementations for dropping blocks, moving them left or right, and rotating them.
- **Line Clearing**: Lines are cleared when filled, and scores are updated accordingly.
- **Level Progression**: The game includes level progression with increasing difficulty as the player's score increases.
- **Score Management**: Tracks the current score, highest score saved to a file, and draws the current score level on the screen.
- **Game Over Detection**: Automatically detects when the game is over and provides corresponding graphics and sounds.
- **Sound Effects**: Includes background music and sound effects for line clear and game end.
- **Graphical Interface**: Utilizes EasyX for graphics, providing a visually appealing game window.

## Files Overview

- `Block.h` and `Block.cpp`: Implements the `Block` class responsible for managing the properties and behaviors of the Tetris blocks (Tetrominoes).
- `Tetris.h` and `Tetris.cpp`: Implements the `Tetris` class which orchestrates the game flow, manages the game state, and handles input/output.
- `main.cpp`: Contains the `main` function which initializes and starts the game.
  
## Dependencies

- **EasyX Graphics Library**: This game relies on the EasyX library for graphical operations. Ensure that EasyX is correctly installed and linked in your development environment.
  
## How to Run

1. **Clone the Repository**: Clone this repository to your local machine.
2. **Install Dependencies**: Ensure you have EasyX graphics library installed.
3. **Build the Project**: Use a C++ compiler that supports C++11 or above.
4. **Run the Executable**: Start the game by running the compiled executable.

## Gameplay Instructions

- **Start the Game**: Execute the compiled program to start playing.
- **Move the Blocks**:
  - Use arrow keys to move blocks left, right or down.
  - Rotate blocks using the up arrow key.
- **Objective**: Clear as many lines as possible for the highest score.
- **End Game**: The game ends when blocks reach the top of the screen without any possible moves.


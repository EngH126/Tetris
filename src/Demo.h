#pragma once

#pragma region 头文件引用

// 平台版本头文件
#include "targetver.h"

// Windows 头文件
#define WIN32_LEAN_AND_MEAN // 从 Windows 头文件中排除极少使用的内容
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <stdio.h>
#include <Mmsystem.h>
#include <wchar.h>
// 资源头文件
#include "resource.h"
#pragma comment(lib, "Msimg32.lib") // 解决报错：无法解析的外部符号 __imp_TransparentBlt
#pragma comment(lib,"winmm.lib")
#pragma warning(disable:4996)
// TODO: 在此处引用程序需要的其他头文件
#include <cmath>
#include <vector>

#pragma endregion

#pragma region 宏定义

// 窗体
#define WINDOW_TITLEBARHEIGHT 32 // 标题栏高度
#define WINDOW_WIDTH 1216        // 游戏窗口宽度
#define WINDOW_HEIGHT 824        // 游戏窗口高度

// 计时器
#define TIMER_GAMETIMER 1          // 游戏的默认计时器ID
#define TIMER_GAMETIMER_ELAPSE 50  // 默认计时器刷新间隔的毫秒数
#define TIMER_PAINTTIMER 2          // 砖块的下落计时器ID
#define TIMER_PAINTTIMER_ELAPSE 20  // 砖块下落刷新间隔的毫秒数

// 游戏阶段
#define STAGE_START 0 // 开始画面的ID
#define STAGE_GAME 1  // 第一个游戏场景的ID
#define STAGE_OVER 2  //游戏结束的ID
#define STAGE_HELP 3  //帮助界面的ID
#define STAGE_TIMEOUT 4 //暂停界面的ID
#define STAGE_SETTING 5 //设置界面的ID

// 背景
#define BG_CELL_WIDTH 25                       // 背景单格宽度
#define BG_CELL_HEIGHT 25                      // 背景单格高度
#define BG_COLUMNS WINDOW_WIDTH / BG_CELL_WIDTH // 背景沿X方向的单元个数
#define BG_ROWS WINDOW_HEIGHT / BG_CELL_HEIGHT  // 背景沿Y方向的单元个数

// 砖块
#define BRICK_CELL_WIDTH 25                          // 砖块单格宽度
#define BRICK_CELL_HEIGHT 25                         // 砖块单格高度
#define BRICK_COLUMNS WINDOW_WIDTH / BRICK_CELL_WIDTH // 砖块沿X方向的单元个数
#define BRICK_ROWS WINDOW_HEIGHT / BRICK_CELL_HEIGHT  // 砖块沿Y方向的单元个数
#define BRICK_FRAME_SIZE 4                            // 砖块动画帧序列的大小

// 开始游戏按钮
#define BUTTON_STARTGAME_ID 1001                                              // 开始游戏按钮ID
#define BUTTON_STARTGAME_WIDTH 300                                            // 开始游戏按钮宽度
#define BUTTON_STARTGAME_HEIGHT 200                                           // 开始游戏按钮高度
#define BUTTON_STARTGAME_X (WINDOW_WIDTH - BUTTON_STARTGAME_WIDTH) / 2        // 开始游戏按钮X坐标
#define BUTTON_STARTGAME_Y (WINDOW_HEIGHT - BUTTON_STARTGAME_HEIGHT) / 2 - 50 // 开始游戏按钮Y坐标

// 帮助游戏按钮
#define BUTTON_HELP_ID 1002                                                   // 帮助游戏按钮ID
#define BUTTON_STARTHELP_WIDTH 296                                            // 帮助游戏按钮宽度
#define BUTTON_STARTHELP_HEIGHT 146                                           // 帮助游戏按钮高度
#define BUTTON_STARTHELP_X (WINDOW_WIDTH - BUTTON_STARTHELP_WIDTH) / 2        // 帮助游戏按钮X坐标
#define BUTTON_STARTHELP_Y (WINDOW_HEIGHT - BUTTON_STARTHELP_HEIGHT) / 2 + 125// 帮助游戏按钮Y坐标

// 返回按钮
#define BUTTON_FANHUI_ID 1003                                                   // 返回按钮ID
#define BUTTON_STARTFANHUI_WIDTH 165                                            // 返回钮宽度
#define BUTTON_STARTFANHUI_HEIGHT 130                                           // 返回钮高度
#define BUTTON_STARTFANHUI_X (WINDOW_WIDTH - BUTTON_STARTFANHUI_WIDTH) / 2        // 返回按钮X坐标
#define BUTTON_STARTFANHUI_Y (WINDOW_HEIGHT - BUTTON_STARTFANHUI_HEIGHT) / 2 + 250// 返回按钮Y坐标

//回到游戏按钮
#define BUTTON_CONTINUE_ID 1004                                                   // 返回按钮ID
#define BUTTON_CONTINUE_WIDTH 280                                            // 返回钮宽度
#define BUTTON_CONTINUE_HEIGHT 120                                           // 返回钮高度
#define BUTTON_CONTINUE_X (WINDOW_WIDTH - BUTTON_CONTINUE_WIDTH) / 2 - 5     // 返回按钮X坐标
#define BUTTON_CONTINUE_Y (WINDOW_HEIGHT - BUTTON_CONTINUE_HEIGHT) / 2 - 150 // 返回按钮Y坐标

//重新开始按钮
#define BUTTON_RESTART_ID 1005                                                   // 返回按钮ID
#define BUTTON_RESTART_WIDTH 280                                            // 返回钮宽度
#define BUTTON_RESTART_HEIGHT 120                                           // 返回钮高度
#define BUTTON_RESTART_X (WINDOW_WIDTH - BUTTON_RESTART_WIDTH) / 2 - 5     // 返回按钮X坐标
#define BUTTON_RESTART_Y (WINDOW_HEIGHT - BUTTON_RESTART_HEIGHT) / 2 - 50 // 返回按钮Y坐标

//回到主页按钮
#define BUTTON_BACKTOMAIN_ID 1006                                              // 返回按钮ID
#define BUTTON_BACKTOMAIN_WIDTH 280                                            // 返回钮宽度
#define BUTTON_BACKTOMAIN_HEIGHT 120                                           // 返回钮高度
#define BUTTON_BACKTOMAIN_X (WINDOW_WIDTH - BUTTON_BACKTOMAIN_WIDTH) / 2 - 5     // 返回按钮X坐标
#define BUTTON_BACKTOMAIN_Y (WINDOW_HEIGHT - BUTTON_BACKTOMAIN_HEIGHT) / 2 + 50 // 返回按钮Y坐标

//设置按钮
#define BUTTON_SETTING_ID 1007                                              // 返回按钮ID
#define BUTTON_SETTING_WIDTH 375                                            // 返回钮宽度
#define BUTTON_SETTING_HEIGHT 120                                           // 返回钮高度
#define BUTTON_SETTING_X (WINDOW_WIDTH - BUTTON_SETTING_WIDTH) / 2 + 6      // 返回按钮X坐标
#define BUTTON_SETTING_Y (WINDOW_HEIGHT - BUTTON_SETTING_HEIGHT) / 2 + 225  // 返回按钮Y坐标

//快按钮
#define BUTTON_FAST_ID 1008                                              // 返回按钮ID
#define BUTTON_FAST_WIDTH 150                                            // 返回钮宽度
#define BUTTON_FAST_HEIGHT 100                                           // 返回钮高度
#define BUTTON_FAST_X (WINDOW_WIDTH - BUTTON_FAST_WIDTH) / 2 - 300     // 返回按钮X坐标
#define BUTTON_FAST_Y (WINDOW_HEIGHT - BUTTON_FAST_HEIGHT) / 2 - 175     // 返回按钮Y坐标

//中按钮
#define BUTTON_MID_ID 1009                                              // 返回按钮ID
#define BUTTON_MID_WIDTH 150                                            // 返回钮宽度
#define BUTTON_MID_HEIGHT 100                                           // 返回钮高度
#define BUTTON_MID_X (WINDOW_WIDTH - BUTTON_MID_WIDTH) / 2 - 300     // 返回按钮X坐标
#define BUTTON_MID_Y (WINDOW_HEIGHT - BUTTON_MID_HEIGHT) / 2 - 75     // 返回按钮Y坐标

//慢按钮
#define BUTTON_SLOW_ID 1010                                              // 返回按钮ID
#define BUTTON_SLOW_WIDTH 150                                            // 返回钮宽度
#define BUTTON_SLOW_HEIGHT 100                                           // 返回钮高度
#define BUTTON_SLOW_X (WINDOW_WIDTH - BUTTON_SLOW_WIDTH) / 2 - 300     // 返回按钮X坐标
#define BUTTON_SLOW_Y (WINDOW_HEIGHT - BUTTON_SLOW_HEIGHT) / 2 + 25     // 返回按钮Y坐标

//上按钮
#define BUTTON_UP_ID 1011                                              // 返回按钮ID
#define BUTTON_UP_WIDTH 120                                            // 返回钮宽度
#define BUTTON_UP_HEIGHT 120                                           // 返回钮高度
#define BUTTON_UP_X (WINDOW_WIDTH - BUTTON_UP_WIDTH) / 2   + 400  // 返回按钮X坐标
#define BUTTON_UP_Y (WINDOW_HEIGHT - BUTTON_UP_HEIGHT) / 2  + 100    // 返回按钮Y坐标

//下按钮
#define BUTTON_DOWN_ID 1012                                              // 返回按钮ID
#define BUTTON_DOWN_WIDTH 120                                            // 返回钮宽度
#define BUTTON_DOWN_HEIGHT 120                                           // 返回钮高度
#define BUTTON_DOWN_X (WINDOW_WIDTH - BUTTON_DOWN_WIDTH) / 2 + 400     // 返回按钮X坐标
#define BUTTON_DOWN_Y (WINDOW_HEIGHT - BUTTON_DOWN_HEIGHT) / 2 + 200     // 返回按钮Y坐标

//左按钮
#define BUTTON_LEFT_ID 1013                                              // 返回按钮ID
#define BUTTON_LEFT_WIDTH 120                                            // 返回钮宽度
#define BUTTON_LEFT_HEIGHT 120                                           // 返回钮高度
#define BUTTON_LEFT_X (WINDOW_WIDTH - BUTTON_LEFT_WIDTH) / 2 + 300     // 返回按钮X坐标
#define BUTTON_LEFT_Y (WINDOW_HEIGHT - BUTTON_LEFT_HEIGHT) / 2 + 200     // 返回按钮Y坐标

//右按钮
#define BUTTON_RIGHT_ID 1014                                              // 返回按钮ID
#define BUTTON_RIGHT_WIDTH 120                                            // 返回钮宽度
#define BUTTON_RIGHT_HEIGHT 120                                           // 返回钮高度
#define BUTTON_RIGHT_X (WINDOW_WIDTH - BUTTON_RIGHT_WIDTH) / 2 + 500     // 返回按钮X坐标
#define BUTTON_RIGHT_Y (WINDOW_HEIGHT - BUTTON_RIGHT_HEIGHT) / 2 + 200     // 返回按钮Y坐标

//经典模式按钮
#define BUTTON_CLASSIC_ID 1015                                              // 返回按钮ID
#define BUTTON_CLASSIC_WIDTH 240                                            // 返回钮宽度
#define BUTTON_CLASSIC_HEIGHT 90                                           // 返回钮高度
#define BUTTON_CLASSIC_X (WINDOW_WIDTH - BUTTON_CLASSIC_WIDTH) / 2           // 返回按钮X坐标
#define BUTTON_CLASSIC_Y (WINDOW_HEIGHT - BUTTON_CLASSIC_HEIGHT) / 2 - 175    // 返回按钮Y坐标

//盲打模式按钮
#define BUTTON_BLIND_ID 1016                                              // 返回按钮ID
#define BUTTON_BLIND_WIDTH 240                                            // 返回钮宽度
#define BUTTON_BLIND_HEIGHT 90                                           // 返回钮高度
#define BUTTON_BLIND_X (WINDOW_WIDTH - BUTTON_BLIND_WIDTH) / 2           // 返回按钮X坐标
#define BUTTON_BLIND_Y (WINDOW_HEIGHT - BUTTON_BLIND_HEIGHT) / 2   -75    // 返回按钮Y坐标

//大按钮
#define BUTTON_BIG_ID 1017                                              // 返回按钮ID
#define BUTTON_BIG_WIDTH 100                                            // 返回钮宽度
#define BUTTON_BIG_HEIGHT 100                                           // 返回钮高度
#define BUTTON_BIG_X (WINDOW_WIDTH - BUTTON_BIG_WIDTH) / 2 + 300      // 返回按钮X坐标
#define BUTTON_BIG_Y (WINDOW_HEIGHT - BUTTON_BIG_HEIGHT) / 2 - 175    // 返回按钮Y坐标

//小按钮
#define BUTTON_SMALL_ID 1018                                              // 返回按钮ID
#define BUTTON_SMALL_WIDTH 100                                            // 返回钮宽度
#define BUTTON_SMALL_HEIGHT 100                                           // 返回钮高度
#define BUTTON_SMALL_X (WINDOW_WIDTH - BUTTON_SMALL_WIDTH) / 2  + 300    // 返回按钮X坐标
#define BUTTON_SMALL_Y (WINDOW_HEIGHT - BUTTON_SMALL_HEIGHT) / 2  - 75    // 返回按钮Y坐标

//关按钮
#define BUTTON_CLOSE_ID 1019                                              // 返回按钮ID
#define BUTTON_CLOSE_WIDTH 100                                            // 返回钮宽度
#define BUTTON_CLOSE_HEIGHT 100                                           // 返回钮高度
#define BUTTON_CLOSE_X (WINDOW_WIDTH - BUTTON_CLOSE_WIDTH) / 2  + 300     // 返回按钮X坐标
#define BUTTON_CLOSE_Y (WINDOW_HEIGHT - BUTTON_CLOSE_HEIGHT) / 2  + 25   // 返回按钮Y坐标

//空格按钮
#define BUTTON_BLANK_ID 1020                                              // 返回按钮ID
#define BUTTON_BLANK_WIDTH 200                                            // 返回钮宽度
#define BUTTON_BLANK_HEIGHT 100                                           // 返回钮高度
#define BUTTON_BLANK_X (WINDOW_WIDTH - BUTTON_BLANK_WIDTH) / 2  + 400     // 返回按钮X坐标
#define BUTTON_BLANK_Y (WINDOW_HEIGHT - BUTTON_BLANK_HEIGHT) / 2  + 275   // 返回按钮Y坐标

//ESC按钮
#define BUTTON_ESC_ID 1021                                              // 返回按钮ID
#define BUTTON_ESC_WIDTH 180                                            // 返回钮宽度
#define BUTTON_ESC_HEIGHT 100                                           // 返回钮高度
#define BUTTON_ESC_X (WINDOW_WIDTH - BUTTON_ESC_WIDTH) / 2  - 400     // 返回按钮X坐标
#define BUTTON_ESC_Y (WINDOW_HEIGHT - BUTTON_ESC_HEIGHT) / 2  - 350   // 返回按钮Y坐标

//重置按钮
#define BUTTON_RESET_ID 1022                                              // 返回按钮ID
#define BUTTON_RESET_WIDTH 150                                            // 返回钮宽度
#define BUTTON_RESET_HEIGHT 90                                           // 返回钮高度
#define BUTTON_RESET_X (WINDOW_WIDTH - BUTTON_RESET_WIDTH) / 2  + 400     // 返回按钮X坐标
#define BUTTON_RESET_Y (WINDOW_HEIGHT - BUTTON_RESET_HEIGHT) / 2  + 125   // 返回按钮Y坐标
// TODO: 添加游戏需要的更多宏定义

#pragma endregion

#pragma region 结构体声明

// 场景结构体
struct Stage
{
    int stageID; // 场景编号
    HBITMAP bg;  // 背景图片
    bool pause;  // 游戏是否被暂停（计时器是否运行）

    // TODO: 其他需要记录的信息
};

// 按钮结构体
struct Button
{
    int buttonID; // 按钮编号
    HBITMAP img;  // 图片
    int x;        // 坐标x
    int y;        // 坐标y
    int width;    // 宽度
    int height;   // 高度
};

// 砖块结构体
struct Brick
{
    HBITMAP img;     // 图片
    int frame_index; // 当前显示的是帧序列的第几个
    int cell_x;      // 单元坐标x
    int cell_y;      // 单元坐标y
};

struct Block {
    HBITMAP img;     // 图片
    int x;      // 单元坐标x
    int y;      // 单元坐标y
    int shape[4][4];
    int shape_type;
    int shape_id;
};

// TODO: 添加游戏需要的更多结构体

#pragma endregion

#pragma region 事件处理函数声明

// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);
void PaintUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

// TODO: 添加游戏需要的更多处事件理函数

#pragma endregion

#pragma region 其它游戏状态处理函数声明

// 初始化场景函数
void InitStage(HWND hWnd, int stageID);

// 添加按钮函数
Button *CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y);

// 添加砖块函数
Brick *CreateBrick(HBITMAP img);

// 刷新砖块状态函数
void UpdateBrick(HWND hWnd);
void UpdateBlock(HWND hWnd);
//游戏结束判断函数
void Gameover(HWND hWnd);
//消除函数
void eliminate(HWND hWnd);
//创建地基函数
void createbase();
//暂停函数
void TimeOut(HWND hWnd);
//清除砖块函数
void clearblock();
//播放音乐函数
void playmusic();
//读取历史分数函数
void readhistory();
//写入历史分数函数
void writehistory();
//比较历史分数函数
void comparent();
//重置历史分数函数
void reset();
// TODO: 添加游戏需要的更多函数

#pragma endregion

#pragma region 绘图函数声明

// 绘图函数
void Paint(HWND hWnd);

// 创建纯白背景图像
HBITMAP CreateWhiteBackground(HWND hWnd);

// 创建游戏背景资源
HBITMAP CreateGameBackground(HWND hWnd);
// TODO: 添加游戏需要的更多绘图函数

#pragma endregion

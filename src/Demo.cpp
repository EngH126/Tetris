// Demo.cpp : 定义应用程序的入口点。
#include "Demo.h"

using namespace std;

#pragma region 全局变量

#define MAX_LOADSTRING 100

// 全局变量：
HINSTANCE hInst;                     // 当前实例
WCHAR szTitle[MAX_LOADSTRING];       // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING]; // 主窗口类名

// 位图资源：
HBITMAP bmp_StartButton;     // 开始按钮图像资源
HBITMAP bmp_Rock;            // 石头图像资源
HBITMAP bmp_Brick;           // 砖块图像资源
HBITMAP bmp_Side;
HBITMAP bmp_Stone;
HBITMAP bmp_Base;
HBITMAP bmp_Help;
HBITMAP bmp_fanhui;
HBITMAP bmp_continue;
HBITMAP bmp_restart;
HBITMAP bmp_backtomain;
HBITMAP bmp_setting;
HBITMAP bmp_fast;
HBITMAP bmp_mid;
HBITMAP bmp_slow;
HBITMAP bmp_preview;
HBITMAP bmp_up;
HBITMAP bmp_down;
HBITMAP bmp_left;
HBITMAP bmp_right;
HBITMAP bmp_classic;
HBITMAP bmp_blind;
HBITMAP bmp_big;
HBITMAP bmp_small;
HBITMAP bmp_close;
HBITMAP bmp_transparent;
HBITMAP bmp_blank;
HBITMAP bmp_esc;
HBITMAP bmp_reset;
HBITMAP bmp_WhiteBackground; // 生成的纯白色背景图像
HBITMAP bmp_GameBackground;  // 生成的游戏背景图像

// 游戏状态：
Stage *currentStage = NULL; // 当前场景状态
vector<Button *> buttons;   // 按钮
Brick *brick = NULL;        // 砖块
Block *block = NULL;
Block *nextblock = NULL;
Block* previewblock = NULL;
std::vector<Brick*>base;

// 键盘：
bool keyUpDown = false;    // 上
bool keyDownDown = false;  // 下
bool keyLeftDown = false;  // 左
bool keyRightDown = false; // 右
bool blankspace = false;
bool ESC = false;          //ESC键

// 鼠标：
int mouseX = 0;         // 鼠标X坐标
int mouseY = 0;         // 鼠标Y坐标
bool mouseDown = false; // 鼠标按下

//砖块形状
const int shape[7][4][4][4] = {
    {//凸形
    {{0,0,0,0},
    {1,1,1,0},
    {0,1,0,0},
    {0,0,0,0}},

    {{0,1,0,0},
    {1,1,0,0},
    {0,1,0,0},
    {0,0,0,0}},

    {{0,1,0,0},
    {1,1,1,0},
    {0,0,0,0},
    {0,0,0,0}},

    {{0,1,0,0},
    {0,1,1,0},
    {0,1,0,0},
    {0,0,0,0}}
    },
    {//长条形
    {{0,1,0,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0}},

    {{0,0,0,0},
    {1,1,1,1},
    {0,0,0,0},
    {0,0,0,0}},

    {{0,1,0,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0}},

    {{0,0,0,0},
    {1,1,1,1},
    {0,0,0,0},
    {0,0,0,0}}
    },
    {//方形
    {{1,1,0,0},
    {1,1,0,0},
    {0,0,0,0},
    {0,0,0,0}},

    {{1,1,0,0},
    {1,1,0,0},
    {0,0,0,0},
    {0,0,0,0}},

    {{1,1,0,0},
    {1,1,0,0},
    {0,0,0,0},
    {0,0,0,0}},

    {{1,1,0,0},
    {1,1,0,0},
    {0,0,0,0},
    {0,0,0,0}}
    },
    {//左z形
    {{0,0,1,0},
    {0,1,1,0},
    {0,1,0,0},
    {0,0,0,0}},

    {{0,0,0,0},
    {1,1,0,0},
    {0,1,1,0},
    {0,0,0,0}},

    {{0,0,1,0},
    {0,1,1,0},
    {0,1,0,0},
    {0,0,0,0}},

    {{0,0,0,0},
    {1,1,0,0},
    {0,1,1,0},
    {0,0,0,0}}
    },
    {//右z形
    {{0,1,0,0},
    {0,1,1,0},
    {0,0,1,0},
    {0,0,0,0}},

    {{0,0,0,0},
    {0,1,1,0},
    {1,1,0,0},
    {0,0,0,0}},

    {{0,1,0,0},
    {0,1,1,0},
    {0,0,1,0},
    {0,0,0,0}},

    {{0,0,0,0},
    {0,1,1,0},
    {1,1,0,0},
    {0,0,0,0}}
    },
    {//左l形
    {{1,0,0,0},
    {1,1,1,0},
    {0,0,0,0},
    {0,0,0,0}},

    {{0,1,1,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,0,0,0}},

    {{0,0,0,0},
    {1,1,1,0},
    {0,0,1,0},
    {0,0,0,0}},

    {{0,1,0,0},
    {0,1,0,0},
    {1,1,0,0},
    {0,0,0,0}}
    },
    {//右l形
    {{0,0,1,0},
    {1,1,1,0},
    {0,0,0,0},
    {0,0,0,0}},

    {{0,1,0,0},
    {0,1,0,0},
    {0,1,1,0},
    {0,0,0,0}},

    {{0,0,0,0},
    {1,1,1,0},
    {1,0,0,0},
    {0,0,0,0}},

    {{1,1,0,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,0,0,0}}
    },
};
//地基
int bottom[BG_ROWS][BG_COLUMNS] = {};
int grade = 0;
int cnt = 0;
int speed = 10;
int mark = 10;
int speedstate = 1;
int gamemode = 0;
int volumestate = 0;
int histotrymarks[3] = {0,0,0};
#pragma endregion

#pragma region Win32程序框架

// 此代码模块中包含的函数的前向声明:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEMO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEMO));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex{};

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEMO));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DEMO);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 将实例句柄存储在全局变量中

    HWND hWnd = CreateWindowW(
        szWindowClass, szTitle,
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // 设置窗口样式，不可改变大小，不可最大化
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        WINDOW_WIDTH,
        WINDOW_HEIGHT + WINDOW_TITLEBARHEIGHT,
        nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_CREATE   - 处理窗口创建事件
//  WM_TIMER    - 处理定时器TimeOut事件
//  WM_PAINT    - 绘制主窗口
//  WM_COMMAND  - 处理应用程序菜单
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // 初始化游戏窗体
        InitGame(hWnd, wParam, lParam);
    }
    break;
    case WM_KEYDOWN:
    {
        // 键盘按下事件
        KeyDown(hWnd, wParam, lParam);
    }
    break;
    case WM_KEYUP:
    {
        // 键盘松开事件
        KeyUp(hWnd, wParam, lParam);
    }
    break;
    case WM_MOUSEMOVE:
    {
        // 鼠标移动事件
        MouseMove(hWnd, wParam, lParam);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        // 鼠标左键按下事件
        LButtonDown(hWnd, wParam, lParam);
    }
    break;
    case WM_LBUTTONUP:
    {
        // 鼠标左键松开事件
        LButtonUp(hWnd, wParam, lParam);
    }
    break;
    case WM_TIMER:
    {
        if(wParam == TIMER_GAMETIMER){
            // 判断游戏是否暂停
            if (currentStage != NULL && !currentStage->pause)
            {
                TimerUpdate(hWnd, wParam, lParam);
            }
        }
        else if (wParam == TIMER_PAINTTIMER) {
            if (currentStage != NULL && !currentStage->pause)
            {
                PaintUpdate(hWnd, wParam, lParam);
            }
        }
    }
    break;
    case WM_PAINT:
    {
        // 绘图
        Paint(hWnd);
    }
    break;

    // TODO：其他消息
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析菜单选择:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_DESTROY:
    {
        // 窗口退出
        PostQuitMessage(0);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

#pragma endregion

#pragma region 事件处理函数

// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    // 加载图像资源
    bmp_StartButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_START));
    bmp_Rock = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_ROCK));
    bmp_Brick = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BRICK));
    bmp_Side = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP2));
    bmp_Stone = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
    bmp_Base = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP3));
    bmp_Help = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(help));
    bmp_fanhui = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(fanhui));
    bmp_continue = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP4));
    bmp_restart = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP5));
    bmp_backtomain = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP6));
    bmp_setting = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP7));
    bmp_fast = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP8));
    bmp_mid = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP9));
    bmp_slow = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP10));
    bmp_up = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP11));
    bmp_down = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP12));
    bmp_left = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP13));
    bmp_right = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP14));
    bmp_classic = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP15));
    bmp_blind = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP16));
    bmp_big = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP17));
    bmp_small = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP18));
    bmp_close = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP19));
    bmp_transparent = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP20));
    bmp_blank = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP21));
    bmp_esc = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP22));
    bmp_reset = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP23));
    bmp_WhiteBackground = CreateWhiteBackground(hWnd);
    bmp_GameBackground = CreateGameBackground(hWnd);

    // 初始化开始场景
    InitStage(hWnd, STAGE_START);
    readhistory();

    // 初始化主计时器
    SetTimer(hWnd, TIMER_GAMETIMER, TIMER_GAMETIMER_ELAPSE, NULL);
    SetTimer(hWnd, TIMER_PAINTTIMER, TIMER_PAINTTIMER_ELAPSE, NULL);
    playmusic();
}

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
    case 0x57:  // W
    case VK_UP: // 方向键上
        keyUpDown = true;
        break;
    case 0x53:    // S
    case VK_DOWN: // 方向键下
        keyDownDown = true;
        break;
    case 0x41:    // A
    case VK_LEFT: // 方向键左
        keyLeftDown = true;
        break;
    case 0x44:     // D
    case VK_RIGHT: // 方向键右
        keyRightDown = true;
        break;
    case 27:       //ESC键
        ESC = true;
    case 32:
        blankspace = true;
    // TODO：其他按键
    default:
        break;
    }
}

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
    case 0x57:  // W
    case VK_UP: // 方向键上
        keyUpDown = false;
        break;
    case 0x53:    // S
    case VK_DOWN: // 方向键下
        keyDownDown = false;
        break;
    case 0x41:    // A
    case VK_LEFT: // 方向键左
        keyLeftDown = false;
        break;
    case 0x44:     // D
    case VK_RIGHT: // 方向键右
        keyRightDown = false;
        break;
    case 27:
        ESC = false;
    case 32:
        blankspace = false;
    // TODO：其他按键
    default:
        break;
    }
}

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseX = LOWORD(lParam);
    mouseY = HIWORD(lParam);
}
bool flag = false;
// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseX = LOWORD(lParam);
    mouseY = HIWORD(lParam);
    mouseDown = true;
    // 判断鼠标是否点击按钮
    for (int i = 0; i < buttons.size(); i++)
    {
        Button *button = buttons[i];
        if (button->x <= mouseX && button->x + button->width >= mouseX && button->y  <= mouseY && button->y + button->height >= mouseY)
        {
            switch (button->buttonID)
            {
            case BUTTON_STARTGAME_ID:
                clearblock();
                InitStage(hWnd, STAGE_GAME);
                flag = true;
                break;
            case BUTTON_HELP_ID:
                InitStage(hWnd, STAGE_HELP);
                flag = true;
                break;
            case BUTTON_FANHUI_ID:
                InitStage(hWnd, STAGE_START);
                break;
            case BUTTON_CONTINUE_ID:
                InitStage(hWnd, STAGE_GAME);
                flag = true;
                break;
            case BUTTON_RESTART_ID:
                comparent();
                writehistory();
                clearblock();
                flag = true;
                InitStage(hWnd, STAGE_GAME);
                break;
            case BUTTON_BACKTOMAIN_ID:
                comparent();
                writehistory();
                InitStage(hWnd, STAGE_START);
                flag = true;
                break;
            case BUTTON_SETTING_ID:
                InitStage(hWnd, STAGE_SETTING);
                flag = true;
                break;
            case BUTTON_FAST_ID:
                speedstate = 0;
                speed = 3;
                mark = 20;
                flag = true;
                break;
            case BUTTON_MID_ID:
                speedstate = 1;
                speed = 10;
                mark = 10;
                flag = true;
                break;
            case BUTTON_SLOW_ID:
                speedstate = 2;
                speed = 15;
                mark = 5;
                flag = true;
                break;
            case BUTTON_UP_ID:
            {
                flag = true;
                int tempid = block->shape_id;
                bool fal = false;
                block->shape_id = (block->shape_id + 1) % 4;
                memcpy(block->shape, shape[block->shape_type][block->shape_id], sizeof(block->shape));
                for (int i = 3; i >= 0; i--) {
                    for (int j = 3; j >= 0; j--) {
                        if (block->shape[i][j]) {
                            if (bottom[block->y + i][block->x + j]) {
                                memcpy(block->shape, shape[block->shape_type][tempid], sizeof(block->shape));
                                fal = true;
                                break;
                            }
                        }
                    }
                    if (fal) { break; }
                }
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        if (block->shape[i][j]) {
                            if (block->x + j <= (BRICK_COLUMNS - 1) / 3) {
                                block->x = (BRICK_COLUMNS - 1) / 3 + 1 - j;
                            }
                        }
                    }
                }
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        if (block->shape[i][j]) {
                            if (block->x + j >= 2 * (BRICK_COLUMNS - 1) / 3) {
                                block->x = 2 * (BRICK_COLUMNS - 1) / 3 - 1 - j;
                            }
                        }
                    }
                }
            }
                break;
            case BUTTON_DOWN_ID:
            {
                block->y++;
                bool sig = false;
                for (int i = 3; i >= 0; i--) {
                    for (int j = 3; j >= 0; j--) {
                        if (block->shape[i][j]) {
                            if (bottom[block->y + i][block->x + j]) {
                                block->y--;
                                sig = true;
                                break;
                            }
                        }
                    }
                    if (sig) { break; }
                }
                flag = true;
                break;
            }
            case BUTTON_LEFT_ID:
                block->x--;
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        if (block->shape[i][j]) {
                            if (block->x + j <= (BRICK_COLUMNS - 1) / 3) {
                                block->x = (BRICK_COLUMNS - 1) / 3 + 1 - j;
                            }
                        }
                    }
                }
                flag = true;
                break;
            case BUTTON_RIGHT_ID:
                block->x++;
                flag = true;
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        if (block->shape[i][j]) {
                            if (block->x + j >= 2 * (BRICK_COLUMNS - 1) / 3) {
                                block->x = 2 * (BRICK_COLUMNS - 1) / 3 - 1 - j;
                            }
                        }
                    }
                }
                break;
            case BUTTON_CLASSIC_ID:
                gamemode = 0;
                flag = true;
                break;
            case BUTTON_BLIND_ID:
                gamemode = 1;
                flag = true;
                break;
            case BUTTON_BIG_ID:
                volumestate = 0;
                flag = true;
                mciSendString(TEXT("setaudio BGM9.mp3 volume to 800"), NULL, 0, NULL);
                break;
            case BUTTON_SMALL_ID:
                volumestate = 1;
                flag = true;
                mciSendString(TEXT("setaudio BGM9.mp3 volume to 400"), NULL, 0, NULL);
                break;
            case BUTTON_CLOSE_ID:
                volumestate = 2;
                flag = true;
                mciSendString(TEXT("setaudio BGM9.mp3 volume to 0"), NULL, 0, NULL);
                break;
            case BUTTON_BLANK_ID:
            {
                bool si = false;
                while (si == false) {
                    for (int i = 3; i >= 0; i--) {
                        for (int j = 3; j >= 0; j--) {
                            if (block->shape[i][j]) {
                                if (bottom[block->y + i][block->x + j] == 1) {
                                    si = true;
                                    block->y -= 2;
                                    break;
                                }
                            }
                        }
                    }
                    block->y++;
                }
                flag = true;
            }
                break;
            case BUTTON_ESC_ID:
                InitStage(hWnd, STAGE_TIMEOUT);
                flag = true;
                break;
            case BUTTON_RESET_ID:
                reset();
                flag = true;
                break;
            // TODO: 其他按钮
            default:
                break;
               
            }
            if (flag) { break; }
        }
        
    }
}

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    mouseX = LOWORD(lParam);
    mouseY = HIWORD(lParam);
    mouseDown = false;
}

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    // 状态更新
    switch (currentStage->stageID)
    {
    case STAGE_START:
        break;
    case STAGE_GAME:
    {
        createbase();
        UpdateBrick(hWnd);
        UpdateBlock(hWnd);
        Gameover(hWnd);
        eliminate(hWnd);
        TimeOut(hWnd);
        
    }
    break;

    // TODO：添加多个游戏场景
    default:
        break;
    }

    // 刷新显示
    //InvalidateRect(hWnd, NULL, FALSE);
}

void PaintUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam){
    InvalidateRect(hWnd, NULL, FALSE);
}

#pragma endregion

#pragma region 其它游戏状态处理函数

// 初始化游戏场景函数
void InitStage(HWND hWnd, int stageID)
{
    // 初始化场景实例
    if (currentStage != NULL)
        delete currentStage;
    currentStage = new Stage();
    currentStage->stageID = stageID;

    switch (stageID)
    {
    case STAGE_START:
    {
        currentStage->bg = bmp_WhiteBackground;
        currentStage->pause = false;

        // 删除旧的按钮
        for (size_t i = 0; i < buttons.size(); i++)
        {
            Button *button = buttons[i];
            delete button;
        }
        buttons.clear();

        // 添加新的开始按钮
        Button *startButton = CreateButton(
            BUTTON_STARTGAME_ID, bmp_StartButton,
            BUTTON_STARTGAME_X, BUTTON_STARTGAME_Y,
            BUTTON_STARTGAME_WIDTH, BUTTON_STARTGAME_HEIGHT);
        buttons.push_back(startButton);
        
        Button* helpButton = CreateButton(
            BUTTON_HELP_ID, bmp_Help,
            BUTTON_STARTHELP_X, BUTTON_STARTHELP_Y,
            BUTTON_STARTHELP_WIDTH, BUTTON_STARTHELP_HEIGHT);
        buttons.push_back(helpButton);

        Button* settingButton = CreateButton(
            BUTTON_SETTING_ID, bmp_setting,
            BUTTON_SETTING_X, BUTTON_SETTING_Y,
            BUTTON_SETTING_WIDTH, BUTTON_SETTING_HEIGHT);
        buttons.push_back(settingButton);

        Button* resetButton = CreateButton(
            BUTTON_RESET_ID, bmp_reset,
            BUTTON_RESET_X, BUTTON_RESET_Y,
            BUTTON_RESET_WIDTH, BUTTON_RESET_HEIGHT);
        buttons.push_back(resetButton);
        
    }
    break;
    case STAGE_HELP:
    {
        currentStage->bg = bmp_WhiteBackground;
        currentStage->pause = false;

        for (size_t i = 0; i < buttons.size(); i++)
        {
            Button* button = buttons[i];
            delete button;
        }
        buttons.clear();
        
         Button* fanhuiButton = CreateButton(
            BUTTON_FANHUI_ID, bmp_fanhui,
            BUTTON_STARTFANHUI_X, BUTTON_STARTFANHUI_Y,
            BUTTON_STARTFANHUI_WIDTH, BUTTON_STARTFANHUI_HEIGHT);
        buttons.push_back(fanhuiButton);
    }
    break;
    case STAGE_GAME:
    {
        currentStage->bg = bmp_GameBackground;
        currentStage->pause = false;

        // 删除旧的按钮
        for (size_t i = 0; i < buttons.size(); i++)
        {
            Button *button = buttons[i];
            delete button;
        }
        buttons.clear();

        // 删除旧的砖块，创建新的砖块
        if (brick != NULL)
            delete brick;
        brick = CreateBrick(bmp_Brick);

        Button* upButton = CreateButton(
            BUTTON_UP_ID, bmp_up,
            BUTTON_UP_X, BUTTON_UP_Y,
            BUTTON_UP_WIDTH, BUTTON_UP_HEIGHT);
        buttons.push_back(upButton);

        Button* downButton = CreateButton(
            BUTTON_DOWN_ID, bmp_down,
            BUTTON_DOWN_X, BUTTON_DOWN_Y,
            BUTTON_DOWN_WIDTH, BUTTON_DOWN_HEIGHT);
        buttons.push_back(downButton);

        Button* leftButton = CreateButton(
            BUTTON_LEFT_ID, bmp_left,
            BUTTON_LEFT_X, BUTTON_LEFT_Y,
            BUTTON_LEFT_WIDTH, BUTTON_LEFT_HEIGHT);
        buttons.push_back(leftButton);

        Button* rightButton = CreateButton(
            BUTTON_RIGHT_ID, bmp_right,
            BUTTON_RIGHT_X, BUTTON_RIGHT_Y,
            BUTTON_RIGHT_WIDTH, BUTTON_RIGHT_HEIGHT);
        buttons.push_back(rightButton);

        Button* blankButton = CreateButton(
            BUTTON_BLANK_ID, bmp_blank,
            BUTTON_BLANK_X, BUTTON_BLANK_Y,
            BUTTON_BLANK_WIDTH, BUTTON_BLANK_HEIGHT);
        buttons.push_back(blankButton);

        Button* escButton = CreateButton(
            BUTTON_ESC_ID, bmp_esc,
            BUTTON_ESC_X, BUTTON_ESC_Y,
            BUTTON_ESC_WIDTH, BUTTON_ESC_HEIGHT);
        buttons.push_back(escButton);
    }
    break;
    case STAGE_OVER:
    {
        for (size_t i = 0; i < buttons.size(); i++)
        {
            Button* button = buttons[i];
            delete button;
        }
        buttons.clear();

        currentStage->bg = bmp_WhiteBackground;
        currentStage->pause = false;

        Button* backtomainButton = CreateButton(
            BUTTON_BACKTOMAIN_ID, bmp_backtomain,
            BUTTON_BACKTOMAIN_X, BUTTON_BACKTOMAIN_Y,
            BUTTON_BACKTOMAIN_WIDTH, BUTTON_BACKTOMAIN_HEIGHT);
        buttons.push_back(backtomainButton);

        comparent();
        writehistory();
    }
    break;
    case STAGE_TIMEOUT:
    {
        currentStage->bg = bmp_WhiteBackground;
        currentStage->pause = false;
        
        // 删除旧的按钮
        for (size_t i = 0; i < buttons.size(); i++)
        {
            Button* button = buttons[i];
            delete button;
        }
        buttons.clear();

        Button* continueButton = CreateButton(
            BUTTON_CONTINUE_ID, bmp_continue,
            BUTTON_CONTINUE_X, BUTTON_CONTINUE_Y,
            BUTTON_CONTINUE_WIDTH, BUTTON_CONTINUE_HEIGHT);
        buttons.push_back(continueButton);

        Button* restartButton = CreateButton(
            BUTTON_RESTART_ID, bmp_restart,
            BUTTON_RESTART_X, BUTTON_RESTART_Y,
            BUTTON_RESTART_WIDTH, BUTTON_RESTART_HEIGHT);
        buttons.push_back(restartButton);

        Button* backtomainButton = CreateButton(
            BUTTON_BACKTOMAIN_ID, bmp_backtomain,
            BUTTON_BACKTOMAIN_X, BUTTON_BACKTOMAIN_Y,
            BUTTON_BACKTOMAIN_WIDTH, BUTTON_BACKTOMAIN_HEIGHT);
        buttons.push_back(backtomainButton);
    }
    break;
    case STAGE_SETTING: 
    {
        currentStage->bg = bmp_WhiteBackground;
        currentStage->pause = false;
        
        // 删除旧的按钮
        for (size_t i = 0; i < buttons.size(); i++)
        {
            Button* button = buttons[i];
            delete button;
        }
        buttons.clear();
        
        Button* fanhuiButton = CreateButton(
            BUTTON_FANHUI_ID, bmp_fanhui,
            BUTTON_STARTFANHUI_X, BUTTON_STARTFANHUI_Y,
            BUTTON_STARTFANHUI_WIDTH, BUTTON_STARTFANHUI_HEIGHT);
        buttons.push_back(fanhuiButton);

        Button* fastButton = CreateButton(
            BUTTON_FAST_ID, bmp_fast,
            BUTTON_FAST_X, BUTTON_FAST_Y,
            BUTTON_FAST_WIDTH, BUTTON_FAST_HEIGHT);
        buttons.push_back(fastButton);

        Button* midButton = CreateButton(
            BUTTON_MID_ID, bmp_mid,
            BUTTON_MID_X, BUTTON_MID_Y,
            BUTTON_MID_WIDTH, BUTTON_MID_HEIGHT);
        buttons.push_back(midButton);
        
        Button* slowButton = CreateButton(
            BUTTON_SLOW_ID, bmp_slow,
            BUTTON_SLOW_X, BUTTON_SLOW_Y,
            BUTTON_SLOW_WIDTH, BUTTON_SLOW_HEIGHT);
        buttons.push_back(slowButton);

        Button* classicButton = CreateButton(
            BUTTON_CLASSIC_ID, bmp_classic,
            BUTTON_CLASSIC_X, BUTTON_CLASSIC_Y,
            BUTTON_CLASSIC_WIDTH, BUTTON_CLASSIC_HEIGHT);
        buttons.push_back(classicButton);

        Button* blindButton = CreateButton(
            BUTTON_BLIND_ID, bmp_blind,
            BUTTON_BLIND_X, BUTTON_BLIND_Y,
            BUTTON_BLIND_WIDTH, BUTTON_BLIND_HEIGHT);
        buttons.push_back(blindButton);

        Button* bigButton = CreateButton(
            BUTTON_BIG_ID, bmp_big,
            BUTTON_BIG_X, BUTTON_BIG_Y,
            BUTTON_BIG_WIDTH, BUTTON_BIG_HEIGHT);
        buttons.push_back(bigButton);

        Button* smallButton = CreateButton(
            BUTTON_SMALL_ID, bmp_small,
            BUTTON_SMALL_X, BUTTON_SMALL_Y,
            BUTTON_SMALL_WIDTH, BUTTON_SMALL_HEIGHT);
        buttons.push_back(smallButton);

        Button* closeButton = CreateButton(
            BUTTON_CLOSE_ID, bmp_close,
            BUTTON_CLOSE_X, BUTTON_CLOSE_Y,
            BUTTON_CLOSE_WIDTH, BUTTON_CLOSE_HEIGHT);
        buttons.push_back(closeButton);
   }
    break;
    // TODO：添加多个游戏场景
    default:
        break;
    }

    // 刷新显示
    InvalidateRect(hWnd, NULL, FALSE);
}
//设置地基函数
void createbase() {
    for (int i = (BG_COLUMNS) / 3; i <= 2 * (BG_COLUMNS) / 3; i++) {
        bottom[BG_ROWS - 1][i] = 1;
    }
}

// 添加按钮函数
Button *CreateButton(int buttonID, HBITMAP img, int x, int y, int width, int height)
{
    Button *button = new Button();
    button->buttonID = buttonID;
    button->img = img;
    button->x = x;
    button->y = y;
    button->width = width;
    button->height = height;
    return button;
}

// 添加砖块函数
Brick *CreateBrick(HBITMAP img)
{
    Brick *brick = new Brick();
    brick->img = img;
    brick->frame_index = 0;
    brick->cell_x = BRICK_COLUMNS / 2;
    brick->cell_y = BRICK_ROWS / 2;
    return brick;
}

// 刷新砖块状态函数
void UpdateBrick(HWND hWnd)
{
}

// 创建砖块函数
Block* CreateBlock(HBITMAP img, int type = 1)
{
    Block* b = NULL;
    if (type == 1){
        b = new Block();
        b->img = img;
        b->x = (BRICK_COLUMNS-1)/2;
        b->y = 0;
        b->shape_id = 0;
        srand((unsigned int)time(NULL));
        b->shape_type = rand() % 7;
        memcpy(b->shape, shape[b->shape_type][b->shape_id], sizeof(b->shape));
    }
    return b;
}

// 更新砖块函数
void UpdateBlock(HWND hWnd){
    if (nextblock == NULL) {
        nextblock = CreateBlock(bmp_Stone);
    }
    if (block == NULL) {
        block = nextblock;
        nextblock->x = (BRICK_COLUMNS - 1) / 2;
        nextblock->y = 0;
        nextblock = NULL;
        nextblock = CreateBlock(bmp_Stone);
    }
    nextblock->x = 5 * (BRICK_COLUMNS - 2) / 6;
    nextblock->y = 4;
    previewblock = new Block();
    memcpy(previewblock, block, sizeof(Block));
    bool signal = false;
    while (signal == false) {
        for (int i = 3; i >= 0; i--) {
            for (int j = 3; j >= 0; j--) {
                if (previewblock->shape[i][j]) {
                    if (bottom[previewblock->y + i][previewblock->x + j] == 1) {
                        signal = true;
                        previewblock->y -= 2;
                        break;
                    }
                }
            }
        }
        previewblock->y++;
    }
    if (++cnt >= speed) {
        block->y++;
        cnt = 0;
    }
    int temp_x = block->x;
    // 位置更新
    if (keyUpDown)
    {
        int tempid = block->shape_id;
        bool fal = false;
        block->shape_id = (block->shape_id + 1) % 4;
        memcpy(block->shape, shape[block->shape_type][block->shape_id], sizeof(block->shape));
        for (int i = 3; i >= 0; i--) {
            for (int j = 3; j >= 0; j--) {
                if (block->shape[i][j]) {
                    if (bottom[block->y + i][block->x + j]) {
                        memcpy(block->shape, shape[block->shape_type][tempid], sizeof(block->shape));
                        fal = true;
                        break;
                    }
                }
            }
            if (fal) { break; }
        }
    }
    if (keyDownDown)
    {
        bool sig = false;
        block->y++;
        for (int i = 3; i >= 0; i--) {
            for (int j = 3; j >= 0; j--) {
                if (block->shape[i][j]) {
                    if (bottom[block->y + i][block->x + j]) {
                        block->y--;
                        sig = true;
                        break;
                    }
                }
            }
            if (sig) { break; }
        }
    }
    if (keyLeftDown)
    {
        block->x--;
    }
    if (keyRightDown)
    {
        block->x++;
    }
    /* if (blankspace) {
        bool si = false;
        while (si == false) {
            for (int i = 3; i >= 0; i--) {
                for (int j = 3; j >= 0; j--) {
                    if (block->shape[i][j]) {
                        if (bottom[block->y + i][block->x + j] == 1) {
                            si = true;
                            block->y -= 2;
                            break;
                        }
                    }
                }
            }
            block->y++;
        }
    }*/
    // 防止超出屏幕
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block->shape[i][j]) {
                if (block->x + j <= 0) {
                    block->x = 1 - j;
                }
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block->shape[i][j]) {
                if (block->x + j >= 2*(BRICK_COLUMNS - 1)/3) {
                    block->x = 2 * (BRICK_COLUMNS - 1) / 3 - 1 - j;
                }
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block->shape[i][j]) {
                if (block->x + j <= (BRICK_COLUMNS - 1) / 3) {
                    block->x = (BRICK_COLUMNS - 1) / 3 + 1 - j;
                }
            }
        }
    }
    bool crash = false;
    bool flag = false;
    bool sidecrash = false;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block->shape[i][j]) {
                if (bottom[block->y + i][block->x + j] == 1) {
                    sidecrash = true;
                }
            }
        }
    }
    if (sidecrash) {
        block->x = temp_x;
    }
    for (int i = 3; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
            if (block->shape[i][j]) {
                if (bottom[block->y + i][block->x + j]) {
                    block->y--;
                    crash = true;
                    flag = true;
                    //mciSendString(TEXT("play 固定音效.mp3"), NULL, 0, NULL);
                }
            }
        }
    }
    if (crash) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (block->shape[i][j]) {
                    bottom[block->y + i][block->x + j] = 1;
                    bottom[block->y + i][0]++;
                }
            }
        }
    }
    if (flag) {
        grade += mark;
        delete block;
        block = NULL;
    }
}

// 结束判定函数
void Gameover(HWND hWnd) {
    for (int i = 1; i < 2 * (BRICK_COLUMNS - 1) / 3; i++) {
        if (bottom[0][i]) {
            InitStage(hWnd, STAGE_OVER);
            break;
        }
    }
}

// 消行判定函数
void eliminate(HWND hWnd) {
    for (int k = BG_ROWS - 2; k >= 1; k--) {
        if (bottom[k][0] == 15) {
            //mciSendString(TEXT("play 消行音效.mp3"), NULL, 0, NULL);
            grade += 10 * mark;
            int j = k - 1, sum = 0;
            do {
                sum = 0;
                bottom[j + 1][0] = bottom[j][0];
                for (int i = (BG_COLUMNS - 1) / 3; i < 2 * (BG_COLUMNS - 1) / 3; i++) {
                    bottom[j + 1][i] = bottom[j][i];
                    if (bottom[j][i]) {
                        sum++;
                    }
                }
                j--;
            } while (sum != 0);
        }
   }
}

// 暂停函数
void TimeOut(HWND hWnd) {
    if (ESC) {
        InitStage(hWnd, STAGE_TIMEOUT);
    }
}

// 清除砖块函数
void clearblock() {
    delete nextblock;
    delete block;
    nextblock = NULL;
    block = NULL;
    grade = 0;
    for (int i = 0; i < BG_ROWS - 1; i++) {
        for (int j = 0; j < 2 * (BG_COLUMNS - 1) / 3; j++) {
            bottom[i][j] = 0;
        }
    }

}

// 播放音乐函数
void playmusic() {
    mciSendString(TEXT("open BGM9.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("play BGM9.mp3 repeat"), NULL, 0, NULL);
    //mciSendString(TEXT("open 固定音效.mp3"), NULL, 0, NULL);
    //mciSendString(TEXT("open 消行音效.mp3"), NULL, 0, NULL);
}

// 读取历史分数函数
void readhistory() {
    FILE* fp;
    fp = fopen("历史高分.txt", "r");
    if (fp == NULL) {
        return;
    }
    int temp;
    for (int i = 0; i < 3; i++) {
        fscanf(fp, "%d", &temp);
        histotrymarks[i] = temp;
    }
    fclose(fp);
    fp = NULL;
}

// 比较历史分数函数
void comparent() {
    int temp1 = histotrymarks[0], temp2 = histotrymarks[1], temp3 = histotrymarks[2];
    if (grade == histotrymarks[0]) {
        return;
    }
    if (grade == histotrymarks[1]) {
        return;
    }
    if (grade == histotrymarks[2]) {
        return;
    }
    if (grade > histotrymarks[0]) {
        histotrymarks[2] = histotrymarks[1];
        histotrymarks[1] = histotrymarks[0];
        histotrymarks[0] = grade;
    }
    if (grade < histotrymarks[0] && grade > histotrymarks[1]) {
        histotrymarks[2] = histotrymarks[1];
        histotrymarks[1] = grade;
    }
    if (grade < histotrymarks[1] && grade > histotrymarks[2]) {
        histotrymarks[2] = grade;
    }
    return;
}

// 写入历史分数函数
void writehistory() {
    FILE* fp;
    fp = fopen("历史高分.txt", "w");
    if (fp == NULL) {
        return;
    }
    for (int i = 0; i < 3; i++) {
        fprintf(fp, "%d\n", histotrymarks[i]);
    }
    fclose(fp);
    fp = NULL;
}

// 显示历史分数函数
void reset() {
    for (int i = 0; i < 3; i++) {
        histotrymarks[i] = 0;
    }
    FILE* fp;
    fp = fopen("历史高分.txt", "w");
    for (int i = 0; i < 3; i++) {
        fprintf(fp, "%d\n", histotrymarks[i]);
    }
    fclose(fp);
    fp = NULL;
}
#pragma endregion

#pragma region 绘图函数

// 绘图函数
void Paint(HWND hWnd)
{
    // 开始绘制
    PAINTSTRUCT ps;
    HDC hdc_window = BeginPaint(hWnd, &ps);

    // 创建缓存
    HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
    HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);

    // 初始化缓存
    HBITMAP blankBmp = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
    SelectObject(hdc_memBuffer, blankBmp);

    // 绘制背景到缓存
    SelectObject(hdc_loadBmp, currentStage->bg);
    BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);

    // 按场景分类绘制内容到缓存
    switch (currentStage->stageID)
    {
    case STAGE_START:
    {
        // 绘制开始界面提示文字

        // 创建一个字体，设置高度为 30（单位是逻辑单元）
        HFONT hFont = CreateFont(
            125,                       // 字体高度
            0,                        // 字体宽度（0 表示自动计算）
            0,                        // 字体的倾斜角度
            0,                        // 字体的基线倾斜角度
            FW_NORMAL,                // 字体的粗细
            FALSE,                    // 是否斜体
            FALSE,                    // 是否下划线
            FALSE,                    // 是否删除线
            DEFAULT_CHARSET,          // 字符集
            OUT_DEFAULT_PRECIS,       // 输出精度
            CLIP_DEFAULT_PRECIS,      // 剪裁精度
            DEFAULT_QUALITY,          // 输出质量
            DEFAULT_PITCH | FF_SWISS, // 字体家族和间距
            TEXT("微软雅黑")          // 字体名称
        );
        // 选择自定义字体到设备上下文
        HFONT hOldFont = (HFONT)SelectObject(hdc_memBuffer, hFont);
        // 设置字体区域
        RECT rect = {
            210,
            150,
            1000,
            600};
        // 绘制
        DrawText(hdc_memBuffer, TEXT("俄罗斯方块"), -1, &rect, DT_CENTER);
        // 恢复原来的字体
        SelectObject(hdc_memBuffer, hOldFont);
        // 删除自定义字体以释放资源
        DeleteObject(hFont);

        HFONT hFont1 = CreateFont(
            50,                       // 字体高度
            0,                        // 字体宽度（0 表示自动计算）
            0,                        // 字体的倾斜角度
            0,                        // 字体的基线倾斜角度
            FW_NORMAL,                // 字体的粗细
            FALSE,                    // 是否斜体
            FALSE,                    // 是否下划线
            FALSE,                    // 是否删除线
            DEFAULT_CHARSET,          // 字符集
            OUT_DEFAULT_PRECIS,       // 输出精度
            CLIP_DEFAULT_PRECIS,      // 剪裁精度
            DEFAULT_QUALITY,          // 输出质量
            DEFAULT_PITCH | FF_SWISS, // 字体家族和间距
            TEXT("微软雅黑")          // 字体名称
        );
        // 选择自定义字体到设备上下文
        HFONT hOldFont1 = (HFONT)SelectObject(hdc_memBuffer, hFont1);
        // 设置字体区域
        RECT rect1 = {
            800,
            250,
            1216,
            600 };
        RECT rect2 = {
            900,
            325,
            1216,
            600 };
        RECT rect3 = {
            900,
            400,
            1216,
            600 };
        RECT rect4 = {
            900,
            475,
            1216,
            600 };
        RECT rect5 = {
            700,
            325,
            1216,
            600 };
        RECT rect6 = {
            700,
            400,
            1216,
            600 };
        RECT rect7 = {
            700,
            475,
            1216,
            600 };
        // 绘制
        DrawText(hdc_memBuffer, TEXT("历史分数排行"), -1, &rect1, DT_CENTER);
        DrawText(hdc_memBuffer, TEXT("NO.1"), -1, &rect5, DT_CENTER);
        DrawText(hdc_memBuffer, TEXT("NO.2"), -1, &rect6, DT_CENTER);
        DrawText(hdc_memBuffer, TEXT("NO.3"), -1, &rect7, DT_CENTER);
        wchar_t tmp1[100], tmp2[100], tmp3[100];
        int temp1, temp2, temp3;
        temp1 = histotrymarks[0];
        temp2 = histotrymarks[1];
        temp3 = histotrymarks[2];
        wsprintf(tmp1, _T("%d"), temp1);
        DrawText(hdc_memBuffer, tmp1, -1, &rect2, DT_CENTER);
        wsprintf(tmp2, _T("%d"), temp2);
        DrawText(hdc_memBuffer, tmp2, -1, &rect3, DT_CENTER);
        wsprintf(tmp3, _T("%d"), temp3);
        DrawText(hdc_memBuffer, tmp3, -1, &rect4, DT_CENTER);
        // 恢复原来的字体
        SelectObject(hdc_memBuffer, hOldFont);
        // 删除自定义字体以释放资源
        DeleteObject(hFont);
    }
    break;
    case STAGE_HELP:
    {
        HFONT hFont = CreateFont(
            100,                       // 字体高度
            0,                        // 字体宽度（0 表示自动计算）
            0,                        // 字体的倾斜角度
            0,                        // 字体的基线倾斜角度
            FW_NORMAL,                // 字体的粗细
            FALSE,                    // 是否斜体
            FALSE,                    // 是否下划线
            FALSE,                    // 是否删除线
            DEFAULT_CHARSET,          // 字符集
            OUT_DEFAULT_PRECIS,       // 输出精度
            CLIP_DEFAULT_PRECIS,      // 剪裁精度
            DEFAULT_QUALITY,          // 输出质量
            DEFAULT_PITCH | FF_SWISS, // 字体家族和间距
            TEXT("微软雅黑")          // 字体名称
        );
        // 选择自定义字体到设备上下文
        HFONT hOldFont = (HFONT)SelectObject(hdc_memBuffer, hFont);
        // 设置字体区域
        RECT rect = {
            200,
            75,
            1000,
            600 };
        // 绘制
        DrawText(hdc_memBuffer, TEXT("游戏教程"), -1, &rect, DT_CENTER);
        // 恢复原来的字体
        SelectObject(hdc_memBuffer, hOldFont);
        // 删除自定义字体以释放资源
        DeleteObject(hFont);

        HFONT hFont1 = CreateFont(
            40,                       // 字体高度
            0,                        // 字体宽度（0 表示自动计算）
            0,                        // 字体的倾斜角度
            0,                        // 字体的基线倾斜角度
            FW_NORMAL,                // 字体的粗细
            FALSE,                    // 是否斜体
            FALSE,                    // 是否下划线
            FALSE,                    // 是否删除线
            DEFAULT_CHARSET,          // 字符集
            OUT_DEFAULT_PRECIS,       // 输出精度
            CLIP_DEFAULT_PRECIS,      // 剪裁精度
            DEFAULT_QUALITY,          // 输出质量
            DEFAULT_PITCH | FF_SWISS, // 字体家族和间距
            TEXT("微软雅黑")          // 字体名称
        );
        // 选择自定义字体到设备上下文
        HFONT hOldFont1 = (HFONT)SelectObject(hdc_memBuffer, hFont1);
        // 设置字体区域
        RECT rect1 = {
            0,
            200,
            1216,
            600 };
        RECT rect2 = {
            0,
            250,
            1216,
            600 };
        RECT rect3 = {
            0,
            300,
            1216,
            600 };
        RECT rect4 = {
            0,
            350,
            1216,
            600 };
        RECT rect5 = {
           0,
           400,
           1216,
           600 };
        RECT rect6 = {
           0,
           450,
           1216,
           600 };
        RECT rect7 = {
           0,
           500,
           1216,
           600 };
        RECT rect8 = {
           0,
           550,
           1216,
           600 };
        RECT rect9 = {
           0,
           600,
           1216,
           800 };
        // 绘制
        DrawText(hdc_memBuffer, TEXT("游戏中共有七种方块，方块以一定速率自动下落，碰到底部或者其他方块则固定"), -1, &rect1, DT_CENTER);
        DrawText(hdc_memBuffer, TEXT("玩家控制方块下落，拼成完整的行，一行满后即会消失并获得100分"), -1, &rect2, DT_CENTER);
        DrawText(hdc_memBuffer, TEXT("方块超出游戏界面上边界后，游戏结束，所得分数即为最终得分"), -1, &rect3, DT_CENTER);
        DrawText(hdc_memBuffer, TEXT("按下“W”或者“↑”可使方块顺时针翻转"), -1, &rect4, DT_CENTER);
        DrawText(hdc_memBuffer, TEXT("按下“S”或者“↓”可使方块加速下落，按下空格可使方块直接到达底部"), -1, &rect5, DT_CENTER);
        DrawText(hdc_memBuffer, TEXT("按下“A”或者“←”/“D”或者“→”可以左/右移动方块"), -1, &rect6, DT_CENTER);
        DrawText(hdc_memBuffer, TEXT("本游戏设有经典模式和盲打模式（不显示已下落的方块）"), -1, &rect7, DT_CENTER);
        DrawText(hdc_memBuffer, TEXT("您可以在设置页面中调整方块下落速率、游戏模式和游戏音量"), -1, &rect8, DT_CENTER);
        DrawText(hdc_memBuffer, TEXT("游戏中可通过点击右下角的按钮实现纯鼠标游玩，祝您游戏愉快！"), -1, &rect9, DT_CENTER);
        // 恢复原来的字体
        SelectObject(hdc_memBuffer, hOldFont);
        // 删除自定义字体以释放资源
        DeleteObject(hFont);
    }
    break;
    case STAGE_GAME:
    {
        // 创建一个字体，设置高度为 30（单位是逻辑单元）
        HFONT hFont = CreateFont(
            50,                       // 字体高度
            0,                        // 字体宽度（0 表示自动计算）
            0,                        // 字体的倾斜角度
            0,                        // 字体的基线倾斜角度
            FW_NORMAL,                // 字体的粗细
            FALSE,                    // 是否斜体
            FALSE,                    // 是否下划线
            FALSE,                    // 是否删除线
            DEFAULT_CHARSET,          // 字符集
            OUT_DEFAULT_PRECIS,       // 输出精度
            CLIP_DEFAULT_PRECIS,      // 剪裁精度
            DEFAULT_QUALITY,          // 输出质量
            DEFAULT_PITCH | FF_SWISS, // 字体家族和间距
            TEXT("微软雅黑")          // 字体名称
        );
        // 选择自定义字体到设备上下文
        HFONT hOldFont = (HFONT)SelectObject(hdc_memBuffer, hFont);
        // 设置字体区域
        RECT rect = {
            845,
            10,
            845 + BUTTON_STARTGAME_WIDTH,
            310 };
        // 绘制
        RECT rect1 = {
            920,
            233,
            920 + BUTTON_STARTGAME_WIDTH,
            433 };
        RECT rect2 = {
            800,
            230,
            810 + BUTTON_STARTGAME_WIDTH,
            430 };
        RECT rect3 = {
            -700,
            10,
            810 + BUTTON_STARTGAME_WIDTH,
            430 };
        DrawText(hdc_memBuffer, TEXT("下一个方块"), -1, &rect, DT_CENTER);
        DrawText(hdc_memBuffer, TEXT("当前分数："), -1, &rect2, DT_CENTER);
        DrawText(hdc_memBuffer, TEXT("按下ESC键可暂停"), -1, &rect3, DT_CENTER);
        wchar_t tmp[100];
        wsprintf(tmp, _T("%d"), grade);
        DrawText(hdc_memBuffer, tmp, -1, &rect1, DT_CENTER);
        // 恢复原来的字体
        SelectObject(hdc_memBuffer, hOldFont);
        // 删除自定义字体以释放资源
        DeleteObject(hFont);

        if (previewblock != NULL) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (previewblock->shape[i][j] == 1) {
                        SelectObject(hdc_loadBmp, bmp_transparent);
                        TransparentBlt(
                            hdc_memBuffer, (previewblock->x + j) * BRICK_CELL_WIDTH, (previewblock->y + i) * BRICK_CELL_HEIGHT,
                            BRICK_CELL_WIDTH, BRICK_CELL_HEIGHT,
                            hdc_loadBmp, 0, 0, 35, 35,
                            RGB(255, 255, 255));
                    }
                }
            }
        }
        if (block != NULL) {
            for(int i = 0 ;i < 4; i++){
                for (int j = 0; j < 4; j++) {
                    if(block->shape[i][j]==1){
                        SelectObject(hdc_loadBmp, bmp_Stone);
                        TransparentBlt(
                            hdc_memBuffer, (block->x + j) * BRICK_CELL_WIDTH, (block->y + i) * BRICK_CELL_HEIGHT,
                            BRICK_CELL_WIDTH, BRICK_CELL_HEIGHT,
                            hdc_loadBmp, 0, 0, 35, 35,
                            RGB(255, 255, 255));
                    }
                }
            }
        }
        if (nextblock != NULL) {
            SelectObject(hdc_loadBmp, bmp_Stone);
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (nextblock->shape[i][j] == 1) {
                        TransparentBlt(
                            hdc_memBuffer, (nextblock->x + j) * BRICK_CELL_WIDTH, (nextblock->y + i) * BRICK_CELL_HEIGHT,
                            BRICK_CELL_WIDTH, BRICK_CELL_HEIGHT,
                            hdc_loadBmp, 0, 0, 35, 35,
                            RGB(255, 255, 255));
                    }
                }
            }
        }
        if (gamemode == 0) {
            SelectObject(hdc_loadBmp, bmp_Base);
            for (int i = 0; i < BG_ROWS - 1; i++) {
                for (int j = 1; j < 2 * (BG_COLUMNS - 1) / 3; j++) {
                    if (bottom[i][j] == 1) {
                        TransparentBlt(
                            hdc_memBuffer, j * BRICK_CELL_WIDTH, i * BRICK_CELL_HEIGHT,
                            BRICK_CELL_WIDTH, BRICK_CELL_HEIGHT,
                            hdc_loadBmp, 0, 0, 159, 159,
                            RGB(255, 255, 255));
                    }
                }
            }
        }
    }
    break;
    case STAGE_OVER:
    {
        
        HFONT hFont = CreateFont(
            75,                       // 字体高度
            0,                        // 字体宽度（0 表示自动计算）
            0,                        // 字体的倾斜角度
            0,                        // 字体的基线倾斜角度
            FW_NORMAL,                // 字体的粗细
            FALSE,                    // 是否斜体
            FALSE,                    // 是否下划线
            FALSE,                    // 是否删除线
            DEFAULT_CHARSET,          // 字符集
            OUT_DEFAULT_PRECIS,       // 输出精度
            CLIP_DEFAULT_PRECIS,      // 剪裁精度
            DEFAULT_QUALITY,          // 输出质量
            DEFAULT_PITCH | FF_SWISS, // 字体家族和间距
            TEXT("微软雅黑")          // 字体名称
        );
        // 选择自定义字体到设备上下文
        HFONT hOldFont = (HFONT)SelectObject(hdc_memBuffer, hFont);
        // 设置字体区域
        RECT rect = {
            BUTTON_STARTGAME_X,
            BUTTON_STARTGAME_Y - 50,
            BUTTON_STARTGAME_X + BUTTON_STARTGAME_WIDTH,
            BUTTON_STARTGAME_Y + 150 };
        RECT rect1 = {
            BUTTON_STARTGAME_X - 400,
            BUTTON_STARTGAME_Y + 75,
            BUTTON_STARTGAME_X + BUTTON_STARTGAME_WIDTH + 200,
            BUTTON_STARTGAME_Y + 300 };
        RECT rect2 = {
            BUTTON_STARTGAME_X + 100,
            BUTTON_STARTGAME_Y + 75,
            BUTTON_STARTGAME_X + BUTTON_STARTGAME_WIDTH + 200,
            BUTTON_STARTGAME_Y + 300 };
        // 绘制
        DrawText(hdc_memBuffer, TEXT("Game Over"), -1, &rect, DT_CENTER);
        DrawText(hdc_memBuffer, TEXT("您的最终得分："), -1, &rect1, DT_CENTER);
        wchar_t tmp[100];
        wsprintf(tmp, _T("%d"), grade);
        DrawText(hdc_memBuffer, tmp, -1, &rect2, DT_CENTER);
        // 恢复原来的字体
        // 恢复原来的字体
        SelectObject(hdc_memBuffer, hOldFont);
        // 删除自定义字体以释放资源
        DeleteObject(hFont);
    }
    break;

    case STAGE_TIMEOUT:
    {
        HFONT hFont = CreateFont(
            125,                       // 字体高度
            0,                        // 字体宽度（0 表示自动计算）
            0,                        // 字体的倾斜角度
            0,                        // 字体的基线倾斜角度
            FW_NORMAL,                // 字体的粗细
            FALSE,                    // 是否斜体
            FALSE,                    // 是否下划线
            FALSE,                    // 是否删除线
            DEFAULT_CHARSET,          // 字符集
            OUT_DEFAULT_PRECIS,       // 输出精度
            CLIP_DEFAULT_PRECIS,      // 剪裁精度
            DEFAULT_QUALITY,          // 输出质量
            DEFAULT_PITCH | FF_SWISS, // 字体家族和间距
            TEXT("微软雅黑")          // 字体名称
        );
        // 选择自定义字体到设备上下文
        HFONT hOldFont = (HFONT)SelectObject(hdc_memBuffer, hFont);
        // 设置字体区域
        RECT rect = {
            200,
            125,
            1000,
            600 };
        // 绘制
        DrawText(hdc_memBuffer, TEXT("暂停"), -1, &rect, DT_CENTER);
        // 恢复原来的字体
        SelectObject(hdc_memBuffer, hOldFont);
        // 删除自定义字体以释放资源
        DeleteObject(hFont);
    }
    break;

    case STAGE_SETTING:
    {
        HFONT hFont = CreateFont(
            75,                       // 字体高度
            0,                        // 字体宽度（0 表示自动计算）
            0,                        // 字体的倾斜角度
            0,                        // 字体的基线倾斜角度
            FW_NORMAL,                // 字体的粗细
            FALSE,                    // 是否斜体
            FALSE,                    // 是否下划线
            FALSE,                    // 是否删除线
            DEFAULT_CHARSET,          // 字符集
            OUT_DEFAULT_PRECIS,       // 输出精度
            CLIP_DEFAULT_PRECIS,      // 剪裁精度
            DEFAULT_QUALITY,          // 输出质量
            DEFAULT_PITCH | FF_SWISS, // 字体家族和间距
            TEXT("微软雅黑")          // 字体名称
        );
        // 选择自定义字体到设备上下文
        HFONT hOldFont = (HFONT)SelectObject(hdc_memBuffer, hFont);
        // 设置字体区域
        RECT rect = {
            200,
            75,
            1000,
            600 };
        // 绘制
        DrawText(hdc_memBuffer, TEXT("设置"), -1, &rect, DT_CENTER);
        // 恢复原来的字体
        SelectObject(hdc_memBuffer, hOldFont);
        // 删除自定义字体以释放资源
        DeleteObject(hFont);

        HFONT hFont1 = CreateFont(
            40,                       // 字体高度
            0,                        // 字体宽度（0 表示自动计算）
            0,                        // 字体的倾斜角度
            0,                        // 字体的基线倾斜角度
            FW_NORMAL,                // 字体的粗细
            FALSE,                    // 是否斜体
            FALSE,                    // 是否下划线
            FALSE,                    // 是否删除线
            DEFAULT_CHARSET,          // 字符集
            OUT_DEFAULT_PRECIS,       // 输出精度
            CLIP_DEFAULT_PRECIS,      // 剪裁精度
            DEFAULT_QUALITY,          // 输出质量
            DEFAULT_PITCH | FF_SWISS, // 字体家族和间距
            TEXT("微软雅黑")          // 字体名称
        );
        
        HFONT hOldFont1 = (HFONT)SelectObject(hdc_memBuffer, hFont1);
        // 设置字体区域
        RECT rect1 = {
            -600,
            200,
            1216,
            600 };
        RECT rect2 = {
            -650,
            550,
            1216,
            1000 };
        RECT rect3 = {
            -650,
            600,
            1216,
            1000 };
        RECT rect4 = {
            0,
            200,
            1216,
            600 };
        RECT rect5 = {
            0,
            550,
            1216,
            1000 };
        RECT rect6 = {
            600,
            200,
            1216,
            600 };
        RECT rect7 = {
            600,
            550,
            1216,
            1000 };
        // 绘制
        DrawText(hdc_memBuffer, TEXT("方块下落速度"), -1, &rect1, DT_CENTER);
        DrawText(hdc_memBuffer, TEXT("游戏模式"), -1, &rect4, DT_CENTER);
        DrawText(hdc_memBuffer, TEXT("游戏音量"), -1, &rect6, DT_CENTER);
        if (speedstate == 0) {
            DrawText(hdc_memBuffer, TEXT("当前速度：快"), -1, &rect2, DT_CENTER);
            DrawText(hdc_memBuffer, TEXT("得分倍率：20"), -1, &rect3, DT_CENTER);
        }
        if (speedstate == 1) {
            DrawText(hdc_memBuffer, TEXT("当前速度：中"), -1, &rect2, DT_CENTER);
            DrawText(hdc_memBuffer, TEXT("得分倍率：10"), -1, &rect3, DT_CENTER);
        }
        if (speedstate == 2) {
            DrawText(hdc_memBuffer, TEXT("当前速度：慢"), -1, &rect2, DT_CENTER);
            DrawText(hdc_memBuffer, TEXT("得分倍率：5"), -1, &rect3, DT_CENTER);
        }
        if (gamemode == 0) {
            DrawText(hdc_memBuffer, TEXT("当前模式：经典"), -1, &rect5, DT_CENTER);
        }
        if (gamemode == 1) {
            DrawText(hdc_memBuffer, TEXT("当前模式：盲打"), -1, &rect5, DT_CENTER);
        }
        if (volumestate == 0) {
            DrawText(hdc_memBuffer, TEXT("当前音量：大"), -1, &rect7, DT_CENTER);
        }
        if (volumestate == 1) {
            DrawText(hdc_memBuffer, TEXT("当前音量：小"), -1, &rect7, DT_CENTER);
        }
        if (volumestate == 2) {
            DrawText(hdc_memBuffer, TEXT("当前音量：关"), -1, &rect7, DT_CENTER);
        }
        // 恢复原来的字体
        SelectObject(hdc_memBuffer, hOldFont);
        // 删除自定义字体以释放资源
        DeleteObject(hFont);
    }
    break;
    // TODO：添加多个游戏场景
    default:
        break;
    }

    // 绘制按钮到缓存
    for (int i = 0; i < buttons.size(); i++)
    {
        Button *button = buttons[i];
        SelectObject(hdc_loadBmp, button->img);
        TransparentBlt(
            hdc_memBuffer, button->x, button->y + 50,
            button->width, button->height,
            hdc_loadBmp, 0, 0, button->width, button->height,
            RGB(255, 255, 255));
    }
    // 最后将所有的信息绘制到屏幕上
    BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

    // 回收资源所占的内存（非常重要）
    DeleteObject(blankBmp);
    DeleteDC(hdc_loadBmp);
    DeleteDC(hdc_memBuffer);

    // 结束绘制
    EndPaint(hWnd, &ps);
}

// 创建纯白背景图像
HBITMAP CreateWhiteBackground(HWND hWnd)
{
    // 开始绘制
    PAINTSTRUCT ps;
    HDC hdc_window = BeginPaint(hWnd, &ps);

    // 创建缓存
    HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);

    // 初始化缓存
    HBITMAP bmp_output = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
    SelectObject(hdc_memBuffer, bmp_output);

    // 创建纯白色画刷
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));

    // 创建一个矩形
    RECT rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    // 将缓存填充为白色
    FillRect(hdc_memBuffer, &rect, hBrush);

    // 回收资源所占的内存（非常重要）
    DeleteObject(hBrush);
    DeleteDC(hdc_memBuffer);

    // 结束绘制
    EndPaint(hWnd, &ps);

    return bmp_output;
}

HBITMAP CreateGameBackground(HWND hWnd)
{
    // 开始绘制
    PAINTSTRUCT ps;
    HDC hdc_window = BeginPaint(hWnd, &ps);

    // 创建缓存
    HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
    HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);

    // 初始化缓存
    HBITMAP bmp_output = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
    SelectObject(hdc_memBuffer, bmp_output);

    // 初始化为白色背景
    SelectObject(hdc_loadBmp, bmp_WhiteBackground);
    BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);

    // 画四周石头
    SelectObject(hdc_loadBmp, bmp_Side);
    for (int i = 0; i < BG_ROWS; i++)
    {
        TransparentBlt(
            hdc_memBuffer,(BG_COLUMNS - 1) / 3 * BG_CELL_WIDTH, i * BG_CELL_HEIGHT,
            BG_CELL_WIDTH, BG_CELL_HEIGHT,
            hdc_loadBmp, 0, 0, 38, 38,
            RGB(255, 255, 255));
        TransparentBlt(
            hdc_memBuffer, (2*(BG_COLUMNS - 1)/3) * BG_CELL_WIDTH, i * BG_CELL_HEIGHT,
            BG_CELL_WIDTH, BG_CELL_HEIGHT,
            hdc_loadBmp, 0, 0, 38, 38,
            RGB(255, 255, 255));
    }
    for (int j = (BG_COLUMNS - 1) / 3; j < 2*(BG_COLUMNS-1)/3; j++)
    {
        TransparentBlt(
            hdc_memBuffer, j * BG_CELL_WIDTH, (BG_ROWS - 1) * BG_CELL_HEIGHT,
            BG_CELL_WIDTH, BG_CELL_HEIGHT,
            hdc_loadBmp, 0, 0, 38, 38,
            RGB(255, 255, 255));
    }

    // 回收资源所占的内存（非常重要）
    DeleteDC(hdc_loadBmp);
    DeleteDC(hdc_memBuffer);

    // 结束绘制
    EndPaint(hWnd, &ps);

    return bmp_output;
}
#pragma endregion
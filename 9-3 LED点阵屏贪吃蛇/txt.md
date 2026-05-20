![alt text](image-1.png)

不加关键字code存在RAM里面;加了关键字code存在比较大的flash里面

#include "regx52.h"
#include "delay.h"
#include "matrixled.h"
#include "timer0.h"
#include "stdlib.h"
#include "MatrixKey.h"
#include "Nixie.h"

//点阵大小
#define WIDTH 8
#define HEIGHT 8
//蛇身最大长度
#define MAX_SNAKE_LEN 64
//蛇身坐标数组（储存每个节的x，y坐标）
unsigned char xdata snake_x[MAX_SNAKE_LEN];
unsigned char xdata snake_y[MAX_SNAKE_LEN];
//当前蛇身长度
unsigned char snake_len;
//方向定义
#define DIR_UP      0
#define DIR_DOWN    1
#define DIR_LEFT    2
#define DIR_RIGHT   3

//当前移动方向
unsigned char direction;
//下次移动方向
unsigned char next_direction;
//移动标志（在定时器中置位）
bit need_move;
//移动计时器
unsigned int move_timer;


//显示缓冲区（8列，每列的行数据）
unsigned char display[WIDTH];

//当前显示的列
unsigned char scan_col;

unsigned char food_x, food_y;
unsigned int score;
unsigned char Score_Nixie[2];
unsigned char tries;
unsigned char Score_Count = 5;

bit game_over;

bit IsFoodOnSnake(unsigned char x, unsigned char y)
{
    unsigned char i;
    for (i = 0; i < snake_len; i++) {
        if (snake_x[i] == x && snake_y[i] == y) return 1;
        
    }
    return 0;
}

void InitSnake(void)
{
    snake_len = 3;
    snake_x[0] = 5; snake_y[0] = 4;
    snake_x[1] = 4; snake_y[1] = 4;
    snake_x[2] = 3; snake_y[2] = 4;

    direction = DIR_RIGHT;
    next_direction = DIR_RIGHT;
    game_over = 0;
    score = 0;
    
    // 随机生成食物（确保不与蛇重叠）
    do {
            food_x = (TL0% 6)+1;
            food_y = (TH0% 6)+1;
    } while (IsFoodOnSnake(food_x, food_y));
}




void UpdateDisplay(void)
{
    unsigned char i, x, y;
    for (i = 0; i < 8; i++) display[i] = 0;
    for (i = 0;i < snake_len;i++)
    {
        x = snake_x[i];
        y = snake_y[i];
        if (x < WIDTH && y < HEIGHT)
        {
            display[x] |= (1 << y);   // 按你的左下角原点，y=0 是最下面一行
        }
    }

    // 显示食物（如果游戏未结束）
    if (!game_over) {
        display[food_x] |= (1 << food_y);
    }

}



void MoveSnake(void)
{
    unsigned char i;
    unsigned char new_x = snake_x[0];
    unsigned char new_y = snake_y[0];
    
    switch (direction)
    {
        case DIR_UP:    new_y++; break;
        case DIR_DOWN:  new_y--; break;
        case DIR_LEFT:  new_x--; break;
        case DIR_RIGHT: new_x++; break;
    }



    // 检查是否吃到食物
    if (new_x == food_x && new_y == food_y)
    {
        // 吃到：长度+1，分数增加
        snake_len++;
        score += 1;
        // 将新头插入到数组头部，原有身体后移
        for (i = snake_len - 1; i > 0; i--)
        {
            snake_x[i] = snake_x[i - 1];
            snake_y[i] = snake_y[i-1];
        }
        snake_x[0] = new_x;
        snake_y[0] = new_y;

        if (snake_len==32)
        {   //身长==7
            game_over = 1;
            // 可选：显示胜利信息
            P2 = 0xf0;
        }
        // 生成新食物
        do
        {
            food_x = (TL0% 6)+1;
            food_y = (TH0 % 6) + 1;
            tries++;
            if (tries > 200)
            {   // 尝试200次无果，认为胜利
                game_over = 1;
                // 可选：显示胜利信息
                P2 = 0xf0;
                break;
            }
            
        } while (IsFoodOnSnake(food_x, food_y));
    }
    else
    {
        // 没吃到：正常移动，尾部消失
        for (i = snake_len - 1; i > 0; i--)
        {
            snake_x[i] = snake_x[i - 1];
            snake_y[i] = snake_y[i-1];
        }
        snake_x[0] = new_x;
        snake_y[0] = new_y;
    }
}



bit CheckCollision(void)
{
    unsigned char i;
    unsigned char head_x = snake_x[0];
    unsigned char head_y = snake_y[0];
    
    // 撞墙
    if (head_x >= WIDTH || head_y >= HEIGHT) return 1;
    
    // 撞自身（从第1节开始检查）
    for (i = 1; i < snake_len; i++) {
        if (snake_x[i] == head_x && snake_y[i] == head_y) return 1;
    }
    return 0;
}




void main()
{
    Timer0Init();
    MatrixLED_Init();
    InitSnake();
    UpdateDisplay();
    while (1)
    {      


        // 读取按键，更新 next_direction（不立即改变 direction）
        unsigned char key = MatrixKey();
        if (key != 0) {
            switch (key)
            {
                case 11: next_direction = DIR_UP;    break;
                case 15: next_direction = DIR_DOWN;  break;
                case 14: next_direction = DIR_LEFT;  break;
                case 16: next_direction = DIR_RIGHT; break;
            }
        }
        
        // 允许方向改变（不能反向）
        if ((direction == DIR_UP && next_direction == DIR_DOWN) ||
            (direction == DIR_DOWN && next_direction == DIR_UP) ||
            (direction == DIR_LEFT && next_direction == DIR_RIGHT) ||
            (direction == DIR_RIGHT && next_direction == DIR_LEFT))
        {
            // 保持原方向
        }
        else
        {
            direction = next_direction;
        }
        
        // 检查是否需要移动
        
        if (need_move && !game_over)
        {
            need_move = 0;
            MoveSnake();            // 蛇移动一步
            if (CheckCollision()) {
                game_over = 1;
                P2 = 0x00;//  Game Over，点亮所有LED并停止
            }
            UpdateDisplay();        // 更新显示缓冲区
        }
    }
}

void Timer0_Rountine() interrupt 1
{
    static unsigned int move_counter;
    TH0 = 0xFC;
    TL0 = 0x18;
    //动态显示
    MatrixLED_ShowColum(scan_col, display[scan_col]);
    scan_col = (scan_col + 1) % 8;
    //移动计时
    move_counter++;
    
    if (move_counter >= 800)
    {
        move_counter = 0;
        need_move = 1;
    }

    // 动态显示分数
    // Score_Nixie[0] = score / 10;
    // Score_Nixie[1] = score % 10;
   
    // if (Score_Count == 7)
    // {
    //     Score_Count = 5;
    // }
    // else
    // {
    //     Nixie(Score_Count, Score_Nixie[Score_Count - 5]);
    //     Score_Count++;
    // }
    
        

}

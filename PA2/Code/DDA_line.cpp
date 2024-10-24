#include <graphics.h>
#include <cmath>
#include <conio.h>
using namespace std;

// DDA 直线生成算法
void DDA_Line(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    // 计算步数（根据 dx 和 dy 中的较大值来决定）
    int steps = fmax(abs(dx), abs(dy));

    // 计算每步增量
    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;

    // 初始化起点
    float x = x0;
    float y = y0;

    // 在起始点绘制像素
    putpixel(round(x), round(y), WHITE);

    // 逐步绘制线上的像素点
    for (int i = 0; i < steps; i++)
    {
        x += x_inc;
        y += y_inc;
        putpixel(round(x), round(y), WHITE);
    }
}

int main()
{
    // 初始化图形窗口
    initgraph(600, 400);

    // 使用 DDA 算法绘制直线（起点和终点）
    DDA_Line(100, 100, 300, 300);
    DDA_Line(300, 300, 500, 100);
    DDA_Line(100, 100, 500, 100);

    // 等待按键关闭窗口
    _getch();
    closegraph();

    return 0;
}

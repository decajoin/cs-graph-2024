#include <graphics.h>
#include <cmath>
#include <conio.h>

// Bresenham 直线绘制算法
void Bresenham_Line(int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1; // x 增量的方向
    int sy = (y0 < y1) ? 1 : -1; // y 增量的方向

    int err = dx - dy; // 决策变量

    while (true)
    {
        // 绘制当前点
        putpixel(x0, y0, WHITE);

        // 到达终点时退出循环
        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        // 判断是否横向移动
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        // 判断是否纵向移动
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

int main()
{
    // 初始化图形窗口
    initgraph(600, 400);

    // 使用 Bresenham 算法绘制直线（起点和终点）
    Bresenham_Line(100, 100, 300, 300);
    Bresenham_Line(300, 300, 500, 100);
    Bresenham_Line(100, 100, 500, 100);

    // 等待按键关闭窗口
    _getch();
    closegraph();

    return 0;
}

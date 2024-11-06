#include <graphics.h>
#include <conio.h>

// 定义种子填充函数
void seedFill(int x, int y, COLORREF fillColor, COLORREF boundaryColor)
{
    if (getpixel(x, y) != boundaryColor && getpixel(x, y) != fillColor)
    {
        putpixel(x, y, fillColor); // 填充当前像素
        // 递归填充上下左右四个方向
        seedFill(x + 1, y, fillColor, boundaryColor);
        seedFill(x - 1, y, fillColor, boundaryColor);
        seedFill(x, y + 1, fillColor, boundaryColor);
        seedFill(x, y - 1, fillColor, boundaryColor);
    }
}

int main()
{
    // 初始化图形窗口
    initgraph(640, 480);
    setlinecolor(WHITE); // 设置多边形边界颜色

    // 定义多边形的点
    int poly[] = {40, 190, 40, 70, 140, 100, 250, 20, 250, 140, 140, 220};

    // 绘制多边形
    drawpoly(6, poly);

    // 设置种子点位置
    int seedX = 100, seedY = 100;

    // 调用种子填充算法
    seedFill(seedX, seedY, RED, WHITE);

    // 等待用户按键退出
    _getch();
    closegraph();
    return 0;
}

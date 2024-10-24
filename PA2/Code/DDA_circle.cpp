#include <graphics.h>
#include <cmath>
#include <conio.h>

// 定义PI
#define PI 3.14159265358979323846

// 使用 DDA 算法绘制圆
void DDA_Circle(int xc, int yc, int r)
{
    // 设置角度的增量，步长越小，圆形越平滑
    float theta_inc = 1.0 / r; // 步长与半径成反比
    float theta = 0;

    // 逐步计算圆上的点
    while (theta <= 2 * PI)
    {
        // 利用圆的参数方程，计算圆周上的 x 和 y 坐标
        int x = xc + round(r * cos(theta));
        int y = yc + round(r * sin(theta));

        // 在 (x, y) 处绘制像素点
        putpixel(x, y, WHITE);

        // 增加角度
        theta += theta_inc;
    }
}

int main()
{
    // 初始化图形窗口
    initgraph(640, 480);

    // 使用 DDA 算法绘制一个圆（圆心和半径）
    DDA_Circle(320, 240, 150);

    // 等待按键关闭窗口
    _getch();
    closegraph();

    return 0;
}

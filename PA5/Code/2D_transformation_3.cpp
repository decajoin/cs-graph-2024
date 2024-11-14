#include <graphics.h>
#include <conio.h>
#include <cmath>

// 自定义窗口大小
const static int x = 1200, y = 900;

// 原图形坐标
const static int g[] = {0, 0, 10, 30, 5, 15, 15, 15, 20, 0, 10, 30};

// x 轴坐标变换函数
int x_transformation(int a)
{
    return a * 10;
}

// y 轴坐标变换函数
int y_transformation(int b)
{
    return y - b * 10;
}

// 变换函数：平移
void translation_transformation(int &x, int &y)
{
    int new_x = x + 52;
    int new_y = y + 60;

    // 更新坐标
    x = new_x;
    y = new_y;
}

// 原图形绘制函数
void draw_graph(const int *g, int length)
{
    for (int i = 0; i < length; i += 4)
    {
        // 提取原始坐标
        int x1 = g[i];
        int y1 = g[i + 1];
        int x2 = g[i + 2];
        int y2 = g[i + 3];

        // 坐标变换
        int x1_trans = x_transformation(x1);
        int y1_trans = y_transformation(y1);
        int x2_trans = x_transformation(x2);
        int y2_trans = y_transformation(y2);

        // 绘制直线
        line(x1_trans, y1_trans, x2_trans, y2_trans);
    }
}

// 变换后图形绘制函数
void draw_transformed_graph(const int *g, int length)
{
    {
        for (int i = 0; i < length; i += 4)
        {
            // 提取原始坐标
            int x1 = g[i];
            int y1 = g[i + 1];
            int x2 = g[i + 2];
            int y2 = g[i + 3];

            // 图像变换
            translation_transformation(x1, y1);
            translation_transformation(x2, y2);

            // 坐标变换
            int x1_trans = x_transformation(x1);
            int y1_trans = y_transformation(y1);
            int x2_trans = x_transformation(x2);
            int y2_trans = y_transformation(y2);

            // 绘制直线
            line(x1_trans, y1_trans, x2_trans, y2_trans);
        }
    }
}

int main()
{

    // 初始化图形窗口
    initgraph(x, y);

    // 绘制坐标轴
    line(0, 0, 0, y);
    line(0, y, x, y);

    // 绘制原图形
    draw_graph(g, sizeof(g) / sizeof(g[0]));

    // 绘制变换后的图形
    draw_transformed_graph(g, sizeof(g) / sizeof(g[0]));

    // 等待用户按键退出
    _getch();
    closegraph();

    return 0;
}
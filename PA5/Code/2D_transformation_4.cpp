#include <graphics.h>
#include <conio.h>
#include <cmath>

// 自定义窗口大小
const static int x = 840, y = 680;

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

// 变换函数：将原图放大为 2 倍，将原图缩小为 0.5 倍
void scaling_transformation(int &x, int &y, double k)
{
    // 定义缩放矩阵
    double scaling_matrix[2][2] = {
        {k, 0},
        {0, k}};

    // 使用矩阵乘法进行变换
    double new_x = scaling_matrix[0][0] * x + scaling_matrix[0][1] * y;
    double new_y = scaling_matrix[1][0] * x + scaling_matrix[1][1] * y;

    // 将计算结果转换为整数并更新坐标
    x = round(new_x);
    y = round(new_y);
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
void draw_transformed_graph(const int *g, int length, double k)
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
            scaling_transformation(x1, y1, k);
            scaling_transformation(x2, y2, k);

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
    draw_transformed_graph(g, sizeof(g) / sizeof(g[0]), 2);
    draw_transformed_graph(g, sizeof(g) / sizeof(g[0]), 0.5);

    // 等待用户按键退出
    _getch();
    closegraph();

    return 0;
}
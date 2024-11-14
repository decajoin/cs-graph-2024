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
    return x / 2 + a * 10;
}

// y 轴坐标变换函数
int y_transformation(int b)
{
    return y / 2 - b * 10;
}

// 变换函数：X 方向错切 15 度
void shear_transformation(int &x, int &y, double k)
{
    // 错切因子 k = tan(15°)
    k = tan(k * M_PI / 180.0); // 15° 转为弧度

    // 使用错切矩阵进行变换
    double new_x = x + k * y;
    double new_y = y;

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
            shear_transformation(x1, y1, 45);
            shear_transformation(x2, y2, 45);

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
    line(x / 2, 0, x / 2, y);
    line(0, y / 2, x, y / 2);

    // 绘制原图形
    draw_graph(g, sizeof(g) / sizeof(g[0]));

    // 绘制变换后的图形
    draw_transformed_graph(g, sizeof(g) / sizeof(g[0]));

    // 等待用户按键退出
    _getch();
    closegraph();

    return 0;
}
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

// 变换函数：绕着原点逆时针旋转 75 度
void rotation_transformation(int &x, int &y, double k)
{
    // 将角度转换为弧度
    double theta = k * M_PI / 180.0;

    // 使用math库计算准确的cos和sin值
    double cos_theta = cos(theta);
    double sin_theta = sin(theta);

    // 定义旋转矩阵
    double rotation_matrix[2][2] = {
        {cos_theta, -sin_theta},
        {sin_theta, cos_theta}};

    // 将原始坐标 (x, y) 表示为一个列向量
    double original_coords[2] = {static_cast<double>(x), static_cast<double>(y)};

    // 使用矩阵乘法进行变换
    double new_x = rotation_matrix[0][0] * original_coords[0] + rotation_matrix[0][1] * original_coords[1];
    double new_y = rotation_matrix[1][0] * original_coords[0] + rotation_matrix[1][1] * original_coords[1];

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
            rotation_transformation(x1, y1, 75);
            rotation_transformation(x2, y2, 75);

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
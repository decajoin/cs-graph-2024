#include <graphics.h>
#include <cmath>
#include <iostream>
using namespace std;

// 定义三棱锥的顶点结构体
struct Point3D
{
    float x, y, z;
};

// 定义投影后的二维点
struct Point2D
{
    float x, y;
};

// 三棱锥顶点
Point3D pyramid[] = {
    {0, 0, 20},  // A
    {20, 0, 20}, // B
    {20, 0, 0},  // C
    {10, 20, 10} // D
};

// 投影函数，将三维点投影到二维平面
Point2D project(Point3D point, float d)
{
    Point2D result;
    result.x = d * point.x / (d - point.z);
    result.y = d * point.y / (d - point.z);
    return result;
}

// 计算平面法向量
Point3D calculateNormal(Point3D p1, Point3D p2, Point3D p3)
{
    Point3D normal = {
        p1.y * (p2.z - p3.z) + p2.y * (p3.z - p1.z) + p3.y * (p1.z - p2.z),
        p1.z * (p2.x - p3.x) + p2.z * (p3.x - p1.x) + p3.z * (p1.x - p2.x),
        p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)
    };

    return normal;
}

// 判断面是否可见
bool isFaceVisible(Point3D normal, Point3D viewVector)
{
    // 点积 > 0，面朝向视点
    float dotProduct = normal.x * viewVector.x + normal.y * viewVector.y + normal.z * viewVector.z;
    return dotProduct > 0;
}

// 画三棱锥的投影（带消隐）
void drawPyramidProjection(Point2D projected[], bool visibleEdges[6])
{
    // 根据可见性绘制每条边
    // 底面三角形 ABC
    setlinestyle(visibleEdges[0] ? PS_SOLID : PS_DASH, 1);
    line(projected[0].x, projected[0].y, projected[1].x, projected[1].y);

    setlinestyle(visibleEdges[1] ? PS_SOLID : PS_DASH, 1);
    line(projected[1].x, projected[1].y, projected[2].x, projected[2].y);

    setlinestyle(visibleEdges[2] ? PS_SOLID : PS_DASH, 1);
    line(projected[2].x, projected[2].y, projected[0].x, projected[0].y);

    // 侧面线段 AD, BD, CD
    setlinestyle(visibleEdges[3] ? PS_SOLID : PS_DASH, 1);
    line(projected[0].x, projected[0].y, projected[3].x, projected[3].y);

    setlinestyle(visibleEdges[4] ? PS_SOLID : PS_DASH, 1);
    line(projected[1].x, projected[1].y, projected[3].x, projected[3].y);

    setlinestyle(visibleEdges[5] ? PS_SOLID : PS_DASH, 1);
    line(projected[2].x, projected[2].y, projected[3].x, projected[3].y);
}

// 数学坐标转屏幕坐标
void coordinates_transformation(Point2D &point)
{
    const float scale = 8.0f; // 放大倍数
    point.x = scale * point.x;
    point.y = scale * point.y;
}

int main()
{
    // 初始化图形窗口
    initgraph(800, 600);   // 800x600 窗口大小
    setorigin(400, 300);   // 设置坐标原点为屏幕中心
    setaspectratio(1, -1); // 翻转Y轴

    float d = 50.0f;                // 视点到投影面的距离
    Point3D viewVector = {0, 0, d}; // 视点方向向量
    Point2D projected[4];           // 存储投影后的二维点

    // 计算每个顶点的投影
    for (int i = 0; i < 4; ++i)
    {
        projected[i] = project(pyramid[i], d);
        printf("Projected point %d: (%f, %f)\n", i, projected[i].x, projected[i].y);
        coordinates_transformation(projected[i]);
    }

    // 计算每个面的可见性
    bool visibleEdges[6] = {false}; // 每条边的可见性
    Point3D normals[4];
    normals[0] = calculateNormal(pyramid[0], pyramid[1], pyramid[2]); // 底面 ABC
    normals[1] = calculateNormal(pyramid[0], pyramid[1], pyramid[3]); // 侧面 ABD
    normals[2] = calculateNormal(pyramid[1], pyramid[2], pyramid[3]); // 侧面 BCD
    normals[3] = calculateNormal(pyramid[2], pyramid[0], pyramid[3]); // 侧面 CAD

    // 底面边可见性（逆时针为可见）
    visibleEdges[0] = isFaceVisible(normals[1], viewVector) || isFaceVisible(normals[0], viewVector); // 边 AB
    visibleEdges[1] = isFaceVisible(normals[2], viewVector) || isFaceVisible(normals[0], viewVector); // 边 BC
    visibleEdges[2] = isFaceVisible(normals[3], viewVector) || isFaceVisible(normals[0], viewVector); // 边 AC

    // 侧面边可见性
    visibleEdges[3] = isFaceVisible(normals[1], viewVector) || isFaceVisible(normals[3], viewVector); // 边 AD
    visibleEdges[4] = isFaceVisible(normals[1], viewVector) || isFaceVisible(normals[2], viewVector); // 边 BD
    visibleEdges[5] = isFaceVisible(normals[2], viewVector) || isFaceVisible(normals[3], viewVector); // 边 CD

    // 绘制投影后的三棱锥
    drawPyramidProjection(projected, visibleEdges);

    for (int i = 0; i < 6; i++) {
        printf("Edge %d is visible: %s\n", i, visibleEdges[i] ? "true" : "false");
    }
    // 等待用户操作关闭窗口
    system("pause");
    closegraph();
    return 0;
}

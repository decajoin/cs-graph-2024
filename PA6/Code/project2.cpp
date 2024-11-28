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
        p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)};
    return normal;
}

// 判断面是否可见
bool isFaceVisible(Point3D normal, Point3D viewVector)
{
    float dotProduct = normal.x * viewVector.x + normal.y * viewVector.y + normal.z * viewVector.z;
    return dotProduct > 0;
}

// 绘制三棱锥投影
void drawPyramidProjection(Point2D projected[], bool visibleEdges[6])
{
    // 根据可见性绘制每条边
    setlinestyle(visibleEdges[0] ? PS_SOLID : PS_DASH, 1);
    line(projected[0].x, projected[0].y, projected[1].x, projected[1].y);

    setlinestyle(visibleEdges[1] ? PS_SOLID : PS_DASH, 1);
    line(projected[1].x, projected[1].y, projected[2].x, projected[2].y);

    setlinestyle(visibleEdges[2] ? PS_SOLID : PS_DASH, 1);
    line(projected[2].x, projected[2].y, projected[0].x, projected[0].y);

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
    const float scale = 8.0f;
    point.x = scale * point.x;
    point.y = scale * point.y;
}

// 三维旋转函数
Point3D rotateY(Point3D point, float angle)
{
    float rad = angle * M_PI / 180.0;
    Point3D rotated;
    rotated.x = point.x * cos(rad) + point.z * sin(rad);
    rotated.y = point.y;
    rotated.z = -point.x * sin(rad) + point.z * cos(rad);
    return rotated;
}

int main()
{
    // 初始化图形窗口
    initgraph(800, 600);
    setorigin(400, 300);
    setaspectratio(1, -1);

    float d = 50.0f;                // 视点到投影面的距离
    Point3D viewVector = {0, 0, d}; // 视点方向向量
    Point2D projected[4];           // 存储投影后的二维点

    // 旋转 -30 度后的三棱锥
    Point3D rotatedPyramid[4];
    for (int i = 0; i < 4; ++i)
    {
        rotatedPyramid[i] = rotateY(pyramid[i], -30.0f);
    }

    // 计算旋转后的顶点投影
    for (int i = 0; i < 4; ++i)
    {
        projected[i] = project(rotatedPyramid[i], d);
        coordinates_transformation(projected[i]);
    }

    // 计算每个面的可见性
    bool visibleEdges[6] = {false};
    Point3D normals[4];
    normals[0] = calculateNormal(rotatedPyramid[0], rotatedPyramid[1], rotatedPyramid[2]);
    normals[1] = calculateNormal(rotatedPyramid[0], rotatedPyramid[1], rotatedPyramid[3]);
    normals[2] = calculateNormal(rotatedPyramid[1], rotatedPyramid[2], rotatedPyramid[3]);
    normals[3] = calculateNormal(rotatedPyramid[2], rotatedPyramid[0], rotatedPyramid[3]);

    visibleEdges[0] = isFaceVisible(normals[1], viewVector) || isFaceVisible(normals[0], viewVector);
    visibleEdges[1] = isFaceVisible(normals[2], viewVector) || isFaceVisible(normals[0], viewVector);
    visibleEdges[2] = isFaceVisible(normals[3], viewVector) || isFaceVisible(normals[0], viewVector);
    visibleEdges[3] = isFaceVisible(normals[1], viewVector) || isFaceVisible(normals[3], viewVector);
    visibleEdges[4] = isFaceVisible(normals[1], viewVector) || isFaceVisible(normals[2], viewVector);
    visibleEdges[5] = isFaceVisible(normals[2], viewVector) || isFaceVisible(normals[3], viewVector);

    // 绘制旋转后的投影
    drawPyramidProjection(projected, visibleEdges);

    system("pause");
    closegraph();
    return 0;
}

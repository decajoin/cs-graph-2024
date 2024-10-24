#include <graphics.h>
#include <conio.h>

// 定义 'Y' 和 'Q' 的矢量点坐标
typedef struct
{
    int x, y;
} Point;

// 定义 Y 字母的矢量
Point Y_vectors[] = {
    {50, 50}, {100, 100}, // 从上方的 Y 字形左臂
    {100, 100}, {150, 50}, // Y 字形右臂
    {100, 100}, {100, 200} // Y 字形的底部竖线
};

// 定义 Q 字母的矢量
Point Q_vectors[] = {
    {75, 50}, {125, 50}, // 上部的横线
    {125, 50}, {150, 100}, // 右上圆弧部分
    {150, 100}, {150, 150}, // 右侧的竖线
    {150, 150}, {125, 200}, // 右下圆弧部分
    {125, 200}, {75, 200}, // 下部的横线
    {75, 200}, {50, 150}, // 左下圆弧部分
    {50, 150}, {50, 100}, // 左侧的竖线
    {50, 100}, {75, 50}, // 左上圆弧部分
    {125, 165}, {165, 200} // Q 字形中的斜线
};

// 通过矢量法绘制字符
void drawVectorChar(Point vectors[], int size, int startX, int startY)
{
    for (int i = 0; i < size; i += 2)
    {
        line(vectors[i].x + startX, vectors[i].y + startY, vectors[i + 1].x + startX, vectors[i + 1].y + startY);
    }
}

int main()
{
    initgraph(640, 480);

    // 绘制字母 Y 和 Q 的矢量图形
    drawVectorChar(Y_vectors, sizeof(Y_vectors) / sizeof(Y_vectors[0]), 50, 100);
    drawVectorChar(Y_vectors, sizeof(Y_vectors) / sizeof(Y_vectors[0]), 200, 100);
    drawVectorChar(Q_vectors, sizeof(Q_vectors) / sizeof(Q_vectors[0]), 350, 100);

    _getch();
    closegraph();
    return 0;
}

#include <graphics.h>
#include <conio.h>

// 八个方向的编码
int Model[8][2] = {
    {1, 0},   // 右
    {1, -1},  // 右上
    {0, -1},  // 上
    {-1, -1}, // 左上
    {-1, 0},  // 左
    {-1, 1},  // 左下
    {0, 1},   // 下
    {1, 1}    // 右下
};

// 定义 Y 字母的方向编码
int Y_direction[] = {
    7, 7, 7, 7,
    1, 1, 1, 1,
    5, 5, 5, 5,
    6, 6, 6, 6, 6, 6, 6
};

// 定义 Q 字母的方向编码
int Q_direction[] = {
    0, 0, 0, 0,
    7, 7, 7,
    6, 6, 6, 6, 6,
    7, 7, 7,
    3, 3, 3,
    5, 5, 5,
    4, 4, 4, 4,
    3, 3, 3,
    2, 2, 2, 2, 2,
    1, 1, 1,
};

// 根据方向编码绘制字符
void drawDirectionCode(int direction[], int size, int startX, int startY, int stepSize)
{
    int currentX = startX;
    int currentY = startY;

    int nextX, nextY;

    // 根据方向编码绘制字符
    for (int i = 0; i < size; i++)
    {
        // 计算下一个点的坐标
        nextX = currentX + Model[direction[i]][0] * stepSize;
        nextY = currentY + Model[direction[i]][1] * stepSize;

        // 用线连接当前点和下一个点
        line(currentX, currentY, nextX, nextY);

        // 更新当前点为下一个点
        currentX = nextX;
        currentY = nextY;
    }
}

int main()
{
    initgraph(500, 300);

    // 绘制字母 Y 的方向编码 (两次)
    drawDirectionCode(Y_direction, sizeof(Y_direction) / sizeof(Y_direction[0]), 100, 100, 10);
    drawDirectionCode(Y_direction, sizeof(Y_direction) / sizeof(Y_direction[0]), 200, 100, 10);

    // 绘制字母 Q 的方向编码
    drawDirectionCode(Q_direction, sizeof(Q_direction) / sizeof(Q_direction[0]), 320, 100, 10);

    _getch();
    closegraph();
    return 0;
}

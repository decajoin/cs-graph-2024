#include <graphics.h>
#include <conio.h>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int ymax; // 边的最大y值
    float x;  // 边的当前x值
    float dx; // 边的斜率的倒数
};

// 将多边形按边组织到边表中
void buildEdgeTable(vector<Edge> edgeTable[], int poly[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int x1 = poly[2 * i];
        int y1 = poly[2 * i + 1];
        int x2 = poly[2 * ((i + 1) % n)];
        int y2 = poly[2 * ((i + 1) % n) + 1];

        if (y1 == y2)
            continue; // 忽略水平边

        if (y1 > y2)
        {
            swap(x1, x2);
            swap(y1, y2);
        }

        // 创建边并加入边表
        Edge edge;
        edge.ymax = y2;
        edge.x = x1;
        edge.dx = (float)(x2 - x1) / (y2 - y1); // 计算斜率的倒数

        edgeTable[y1].push_back(edge);
    }
}

// 扫描线填充算法实现
void scanLineFill(int poly[], int n)
{
    vector<Edge> edgeTable[480];        // 边表
    buildEdgeTable(edgeTable, poly, n); // 构建边表

    vector<Edge> activeEdgeTable; // 活动边表

    // 扫描线从下到上
    for (int y = 0; y < 480; y++)
    {
        // 将当前扫描线的所有边加入活动边表
        for (auto &edge : edgeTable[y])
        {
            activeEdgeTable.push_back(edge);
        }

        // 移除活动边表中ymax等于当前y的边
        activeEdgeTable.erase(
            remove_if(activeEdgeTable.begin(), activeEdgeTable.end(), [y](Edge &e)
                      { return e.ymax == y; }),
            activeEdgeTable.end());

        // 对活动边表按x值排序
        sort(activeEdgeTable.begin(), activeEdgeTable.end(), [](Edge &e1, Edge &e2)
             { return e1.x < e2.x; });

        // 逐对填充交点之间的区域
        for (size_t i = 0; i < activeEdgeTable.size(); i += 2)
        {
            int x1 = (int)activeEdgeTable[i].x;
            int x2 = (int)activeEdgeTable[i + 1].x;
            line(x1, y, x2, y);
        }

        // 更新活动边表中每条边的x值
        for (auto &edge : activeEdgeTable)
        {
            edge.x += edge.dx;
        }
    }
}

int main()
{
    // 初始化图形窗口
    initgraph(640, 480);
    setlinecolor(WHITE); // 设置多边形边界颜色

    // 定义多边形的顶点坐标
    int poly[] = {40, 190, 40, 70, 140, 100, 250, 20, 250, 140, 140, 220};

    // 绘制多边形
    drawpoly(6, poly);

    // 调用扫描线填充算法
    scanLineFill(poly, 6);

    // 等待用户按键退出
    _getch();
    closegraph();
    return 0;
}

#include <graphics.h>
#include <conio.h>
#define pi 3.1415926

int percent[6] = {50, 20, 10, 5, 10, 5};
int fillstyle[6] = {0, 1, 2, 3, 4, 5};
char *Text[6] = {"computer", "printer", "plotter", "scanner", "computer paper", "hard disk"};

void DrawPie(int x, int y, int radius)
{
    double startAngle = 0; // 起始角度
    for (int i = 0; i < 6; i++)
    {
        double endAngle = startAngle + (percent[i] / 100.0) * (2 * pi); // 结束角度
        setfillstyle(BS_HATCHED, fillstyle[i]);                     // 填充格式
        setfillcolor(BLACK);
        fillpie(x - radius, y + radius, x + radius, y - radius, startAngle, endAngle);        // 绘制扇形
        startAngle = endAngle;                                      // 更新起始角度
    }
}


void DrawLegend(int x, int y, int radius, int width, int height)
{
    int legendX = x + 220; // 图例的起始 X 坐标
    int legendY = y;       // 图例的起始 Y 坐标
    int legendHeight = 20; // 图例项的高度
    for (int i = 0; i < 6; i++)
    {
        // 绘制图例颜色块
        setfillstyle(BS_HATCHED, fillstyle[i]);
        bar(legendX, legendY + i * legendHeight, legendX + width, legendY + i * legendHeight + height);
        // 绘制图例文本
        settextcolor(BLACK);
        settextstyle(20, 0, "Arial");
        outtextxy(legendX + width + 10, legendY + i * legendHeight + (height - 20) / 2, Text[i]);
    }
}

int main()
{
    initgraph(640, 480);   // 创建绘图窗口，大小为 640x480 像素
    setbkcolor(WHITE);     // 设置背景色为白色
    cleardevice();         // 清空绘图窗口
    setcolor(BLACK);       // 设置画笔颜色为黑色

    int x = 320, y = 240, radius = 200;
    DrawPie(x, y, radius); // 绘制扇形
    DrawLegend(x, y, radius, 20, 20); // 绘制图例

    // 绘制饼图中的百分比文本
    outtextxy(x, y - 100, "50%");
    outtextxy(x - 100, y + 100, "20%");
    outtextxy(x - 20, y + 100, "10%");
    outtextxy(x + 50, y + 100, "5%");
    outtextxy(x + 100, y + 70, "10%");
    outtextxy(x + 100, y + 10, "5%");


    _getch();              // 按任意键继续
    closegraph();          // 关闭绘图窗口
    return 0;
}

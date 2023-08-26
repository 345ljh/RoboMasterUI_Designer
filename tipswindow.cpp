#include "tipswindow.h"

TipsWindow::TipsWindow(QWidget *parent)
    : QWidget{parent}
{
    resize(400, 600);
    setWindowTitle("说明与提示");

    QLabel* tips = new QLabel;
    tips->move(0, 0);
    tips->resize(400, 600);
    tips->setWordWrap(true);
    tips->setText("1.画面大小为1920*1080，左下角为原点。\n"
                  "2.图传界面设置背景图将自动缩放为16:9。为保证显示效果，请选取符合比例的图片。\n"
                  "3.绘制圆弧时，角度值为0代表12点钟方向，且绘制方向为顺时针。\n即：UI角度值 = 90 - 数学角度值\n"
                  "4.浮点数输入数值为实际显示值*1000，如输入1001将显示1.001。\n"
                  "5.数值与字符在此软件中绘制时无需输入长度与线宽，在裁判系统中建议字体大小与线宽为10:1。\n"
                  "6.字体选择原因，此软件与裁判系统显示字符会存在部分差异。\n"
                  "7.参数输入时，已根据协议内容对输入值进行限制。此软件下显示数值范围为int16_t，裁判系统为int32_t。\n"
                  "8.未命名的图形将会自动命名为graphics+序号。\n"
                  "9.成功添加、修改、删除图形或导出信息后，左下角会提示操作已完成。\n"
                  "10.软件目录下带有DS-DIGI字体，需要自行安装。");
    tips->setParent(this);
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tipswindow.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QPushButton>
#include <QLabel>
#include <QImage>
#include <QComboBox>
#include <QLineEdit>
#include <QPainter>
#include <QClipboard>
#include <QTime>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <vector>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef struct graphic_data_t{
    QString name;
    enum figure_type_e {
        Line = 0, Rectangle, Circle, Oval, Arc, Text_Float, Text_Int, Text_Char
    } figure_type;
    enum color_e {
        RedBlue = 0, Yellow, Green, Orange, Purple, Pink, Cyan, Black, White
    }color;
    short details_a;
    short details_b;
    short width;
    short start_x;
    short start_y;
    short details_c;
    short details_d;
    short details_e;
    QString str;
}graphic_data;

// 若需要限定输入为整数,需要自行在外部创建QIntValidator
class QLineEditRanged: public QLineEdit{
private:
    int min;
    int max;
public:
    QLineEditRanged(int setmin = 0, int setmax = 5){
        min = setmin;
        max = setmax;
    }
    void setRange(int setmin, int setmax){
        min = setmin;
        max = setmax;
    }
    // 开启后,超范围数值自动改为范围边界值
    void enableLimit(void) {
        connect(this, &QLineEdit::textChanged, this, [&](){
            if(this->text().toInt() > max) this->setText(QString::number(max));
            if(this->text().toInt() < min) this->setText(QString::number(min));
        });
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void SetFile(QString* str);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QLabel* layer0;
    QLabel* layer1;
    QLabel* layer2;
    QLabel* layer3;
    QLabel* filepath;
    QLabel* msg;

    QComboBox* operation_select;
    QLabel* operation_tip;
    QLineEdit* addui_name;
    QComboBox* modifyui_name;
    QPushButton* setimage;
    QPushButton* operation_button;
    QPushButton* clear_button;
    QPushButton* grid_button;
    QPushButton* tips_button;
    QPushButton* exportclip_button;
    QPushButton* export_button;
    QPushButton* import_button;

    QLabel* details[11];
    QComboBox* details_typeselect;
    QComboBox* details_colorselect;
    QLineEditRanged* details_input[9];
    QLabel* details_typeselect_label;
    QLabel* details_colorselect_label;
    QLabel* details_input_label[9];

    // 绘制元素时所需显示配置
    char detail_showmatrix[8][9] = {
    /*            det_a det_b width st_x st_y det_c det_d det_e str  */
    /* line   */  {0,   0,    1,    1,   1,   0,    1,    1,    0},
    /* rect   */  {0,   0,    1,    1,   1,   0,    1,    1,    0},
    /* circle */  {0,   0,    1,    1,   1,   1,    0,    0,    0},
    /* oval   */  {0,   0,    1,    1,   1,   0,    1,    1,    0},
    /* arc    */  {1,   1,    1,    1,   1,   0,    1,    1,    0},
    /* float  */  {1,   0,    0,    1,   1,   1,    0,    0,    0},
    /* int    */  {1,   0,    0,    1,   1,   1,    0,    0,    0},
    /* char   */  {1,   0,    0,    1,   1,   0,    0,    0,    1}
    };
    QString detail_labelmatrix[8][9] = {
        {"", "", "线宽", "起点x坐标", "起点y坐标", "", "终点x坐标", "终点y坐标", ""},
        {"", "", "线宽", "起点x坐标", "起点y坐标", "", "终点x坐标", "终点y坐标", ""},
        {"", "", "线宽", "圆心x坐标", "圆心y坐标", "半径", "", "", ""},
        {"", "", "线宽", "圆心x坐标", "圆心y坐标", "", "x半轴长度", "y半轴长度", ""},
        {"起始角度", "终止角度", "线宽", "圆心x坐标", "圆心y坐标", "", "x半轴长度", "y半轴长度", ""},
        {"字体大小", "", "", "起点x坐标", "起点y坐标", "数值*1000", "", "", ""},
        {"字体大小", "", "", "起点x坐标", "起点y坐标", "32位整形", "", "", ""},
        {"字体大小", "", "", "起点x坐标", "起点y坐标", "", "", "", "字符串"}
    };

    std::vector<graphic_data> graphics;

    // slots
    void OperationChange(void);
    void ModifyuiChange(void);
    void GraphicTypeChange(void);
    void Draw(void);
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::OperationChange(void){
    if(operation_select->currentData() == "add"){
        addui_name->show();
        modifyui_name->hide();
        operation_tip->setText("输入添加元素名:");
        operation_button->setText("添加");

        details_typeselect->show();
        details_colorselect->show();
        for(int i = 0; i < 9; i++) details_input[i]->show();
        details_typeselect_label->hide();
        details_colorselect_label->hide();
        for(int i = 0; i < 9; i++) details_input_label[i]->hide();
    } else if(operation_select->currentData() == "modify"){
        addui_name->hide();
        modifyui_name->show();
        operation_tip->setText("选择修改元素:");
        operation_button->setText("修改");

        details_typeselect->show();
        details_colorselect->show();
        for(int i = 0; i < 9; i++) details_input[i]->show();
        details_typeselect_label->hide();
        details_colorselect_label->hide();
        for(int i = 0; i < 9; i++) details_input_label[i]->hide();
    } else if(operation_select->currentData() == "delete"){
        addui_name->hide();
        modifyui_name->show();
        operation_tip->setText("选择删除元素:");
        operation_button->setText("删除");

        details_typeselect->hide();
        details_colorselect->hide();
        for(int i = 0; i < 9; i++) details_input[i]->hide();
        details_typeselect_label->show();
        details_colorselect_label->show();
        for(int i = 0; i < 9; i++) details_input_label[i]->show();
    }
}

void MainWindow::ModifyuiChange(void){
        if(!graphics.size()) return;
        if(operation_select->currentData() == "modify"){
            details_typeselect->setCurrentIndex(graphics[modifyui_name->currentIndex()].figure_type);
            details_colorselect->setCurrentIndex(graphics[modifyui_name->currentIndex()].color);
            details_input[0]->setText(QString::number(graphics[modifyui_name->currentIndex()].details_a));
            details_input[1]->setText(QString::number(graphics[modifyui_name->currentIndex()].details_b));
            details_input[2]->setText(QString::number(graphics[modifyui_name->currentIndex()].width));
            details_input[3]->setText(QString::number(graphics[modifyui_name->currentIndex()].start_x));
            details_input[4]->setText(QString::number(graphics[modifyui_name->currentIndex()].start_y));
            details_input[5]->setText(QString::number(graphics[modifyui_name->currentIndex()].details_c));
            details_input[6]->setText(QString::number(graphics[modifyui_name->currentIndex()].details_d));
            details_input[7]->setText(QString::number(graphics[modifyui_name->currentIndex()].details_e));
            details_input[8]->setText(graphics[modifyui_name->currentIndex()].str);
        } else if(operation_select->currentData() == "delete"){
            details_typeselect_label->setText(details_typeselect->itemText(graphics[modifyui_name->currentIndex()].figure_type));
            details_colorselect_label->setText(details_colorselect->itemText(graphics[modifyui_name->currentIndex()].color));
            details_input_label[0]->setText(QString::number(graphics[modifyui_name->currentIndex()].details_a));
            details_input_label[1]->setText(QString::number(graphics[modifyui_name->currentIndex()].details_b));
            details_input_label[2]->setText(QString::number(graphics[modifyui_name->currentIndex()].width));
            details_input_label[3]->setText(QString::number(graphics[modifyui_name->currentIndex()].start_x));
            details_input_label[4]->setText(QString::number(graphics[modifyui_name->currentIndex()].start_y));
            details_input_label[5]->setText(QString::number(graphics[modifyui_name->currentIndex()].details_c));
            details_input_label[6]->setText(QString::number(graphics[modifyui_name->currentIndex()].details_d));
            details_input_label[7]->setText(QString::number(graphics[modifyui_name->currentIndex()].details_e));
            details_input_label[8]->setText(graphics[modifyui_name->currentIndex()].str);

            for(int i = 0; i < 9; i++){
                if(!detail_showmatrix[graphics[modifyui_name->currentIndex()].figure_type][i]) details_input_label[i]->setText(""); //不需要的属性不显示文字

                details[i + 2]->setText(detail_labelmatrix[graphics[modifyui_name->currentIndex()].figure_type][i]);
                if(detail_showmatrix[graphics[modifyui_name->currentIndex()].figure_type][i]) details[i + 2]->show();
                else details[i + 2]->hide();
            }
        }
}

void MainWindow::GraphicTypeChange(void){
        for(int i = 0; i < 9; i++) {
            details[i + 2]->setText(detail_labelmatrix[details_typeselect->currentData().toInt()][i]);
            if(operation_select->currentData() == "add" || operation_select->currentData() == "modify"){
                if(detail_showmatrix[details_typeselect->currentData().toInt()][i]){
                    details[i + 2]->show();
                    details_input[i]->show();
                } else {
                    details[i + 2]->hide();
                    details_input[i]->hide();
                }
                if(details_typeselect->currentData().toInt() == 5 || details_typeselect->currentData().toInt() == 6) details_input[5]->setRange(-32768, 32767);
                else details_input[5]->setRange(0, 1023);
                details_input[5]->enableLimit();
            } else if(operation_select->currentData() == "delete"){
                if(detail_showmatrix[graphics[modifyui_name->currentIndex()].figure_type][i]){
                    details[i + 2]->show();
                    details_input_label[i]->show();
                } else {
                    details[i + 2]->hide();
                    details_input_label[i]->hide();
                }
            }
        }
}

void MainWindow::Draw(void){
        // 绘图
        QImage img2 = QImage(960, 540, QImage::Format_ARGB32_Premultiplied);
        QPainter painter(&img2);
        QPen pen;

        for(int i = 0; i < int(graphics.size()); i++){
            switch(graphics[i].color){
            case graphic_data::RedBlue:
                pen.setColor(qRgb(255, 65, 71));
                break;
            case graphic_data::Yellow:
                pen.setColor(qRgb(255, 238, 69));
                break;
            case graphic_data::Green:
                pen.setColor(qRgb(168, 255, 43));
                break;
            case graphic_data::Orange:
                pen.setColor(qRgb(243, 163, 41));
                break;
            case graphic_data::Purple:
                pen.setColor(qRgb(255, 35, 255));
                break;
            case graphic_data::Pink:
                pen.setColor(qRgb(227, 89, 138));
                break;
            case graphic_data::Cyan:
                pen.setColor(qRgb(71, 255, 241));
                break;
            case graphic_data::Black:
                pen.setColor(qRgb(0, 0, 0));
                break;
            case graphic_data::White:
                pen.setColor(qRgb(255, 255, 255));
                break;
            }
            pen.setWidth(graphics[i].width);
            painter.setPen(pen);
            QFont font("DS-Digital");
            switch(graphics[i].figure_type){
            case graphic_data::Line:
                painter.drawLine(graphics[i].start_x / 2, 540 - graphics[i].start_y / 2, graphics[i].details_d / 2, 540 - graphics[i].details_e / 2);
                break;
            case graphic_data::Rectangle:
                painter.drawRect(graphics[i].start_x / 2, 540 - graphics[i].start_y / 2, (graphics[i].details_d - graphics[i].start_x) / 2, 540 - (graphics[i].details_e + graphics[i].start_y) / 2);
                break;
            case graphic_data::Circle:
                painter.drawEllipse((graphics[i].start_x - graphics[i].details_c) / 2, 540 - (graphics[i].start_y + graphics[i].details_c) / 2, graphics[i].details_c, graphics[i].details_c);
                break;
            case graphic_data::Oval:
                painter.drawEllipse((graphics[i].start_x - graphics[i].details_d) / 2, 540 - (graphics[i].start_y + graphics[i].details_e) / 2, graphics[i].details_d, graphics[i].details_e);
                break;
            case graphic_data::Arc:
                painter.drawArc((graphics[i].start_x - graphics[i].details_d) / 2,  540 - (graphics[i].start_y + graphics[i].details_e) / 2, graphics[i].details_d, graphics[i].details_e, (450 - graphics[i].details_b) * 16, (graphics[i].details_b - graphics[i].details_a) * 16);
                break;
            case graphic_data::Text_Float:
                font.setPixelSize(graphics[i].details_a);
                painter.setFont(font);
                painter.drawText(graphics[i].start_x / 2, 540 - (graphics[i].start_y) / 2, QString::number(graphics[i].details_c / 1000.0));
                break;
            case graphic_data::Text_Int:
                font.setPixelSize(graphics[i].details_a);
                painter.setFont(font);
                painter.drawText(graphics[i].start_x / 2, 540 - (graphics[i].start_y) / 2, QString::number(graphics[i].details_c));
                break;
            case graphic_data::Text_Char:
                font.setPixelSize(graphics[i].details_a);
                painter.setFont(font);
                painter.drawText(graphics[i].start_x / 2, 540 - (graphics[i].start_y) / 2, graphics[i].str);
                break;
            }
        }
        layer3->setPixmap(QPixmap::fromImage(img2));//将图形显示到label上面
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1250, 800);
    setWindowIcon(QIcon("icon.png"));

    // 先创建对象的图层在下
    // 背景图片
    layer0 = new QLabel;
    layer0->setGeometry(145, 50, 960, 540);
    layer0->setStyleSheet("QLabel{background-color:black}");
    layer0->setStyleSheet("QLabel{background:transparent}");
    layer0->setParent(this);

    // 官方ui界面
    layer1 = new QLabel;
    layer1->setGeometry(145, 50, 960, 540);
    layer1->setStyleSheet("QLabel{background-color:black}");
    layer1->setStyleSheet("QLabel{background:transparent}");
    layer1->setParent(this);

    QImage* img1 = new QImage;
    img1->load("rmui_new.png");
    *img1 = img1->scaled(960, 540, Qt::IgnoreAspectRatio);
    layer1->setPixmap(QPixmap::fromImage(*img1));

    // 网格
    layer2 = new QLabel;
    layer2->setGeometry(145, 50, 960, 540);
    layer2->setStyleSheet("QLabel{background-color:black}");
    layer2->setStyleSheet("QLabel{background:transparent}");
    layer2->setParent(this);

    QImage* img2 = new QImage;
    img2->load("grid.png");
    *img2 = img2->scaled(960, 540, Qt::IgnoreAspectRatio);
    layer2->setPixmap(QPixmap::fromImage(*img2));
    layer2->hide();

    // 绘制ui
    layer3 = new QLabel;
    layer3->setGeometry(145, 50, 960, 540);
    layer3->setStyleSheet("QLabel{background-color:black}");
    layer3->setStyleSheet("QLabel{background:transparent}");
    layer3->setParent(this);

    filepath = new QLabel;
    filepath->resize(1000, 30);
    filepath->move(100, 600);
    filepath->setText("文件路径:");
    filepath->setParent(this);

    setimage = new QPushButton;
    setimage->resize(120, 30);
    setimage->move(1000, 600);
    setimage->setText("设置图传画面");
    setimage->setParent(this);
    connect(setimage, &QPushButton::clicked, this, [&](){
        QString filename = QFileDialog::getOpenFileName(this, tr("设置图传画面"), "", tr("Image Files (*.png *.jpg *.bmp)"));
        QImage* img0 = new QImage;
        img0->load(filename);
        *img0=img0->scaled(960, 540, Qt::IgnoreAspectRatio);
        layer0->setPixmap(QPixmap::fromImage(*img0));
        filepath->setText("文件路径: " + filename);
        if (!filename.isNull()) {
            QString msgstr = "[" + QTime::currentTime().toString("hh:mm:ss.zzz") + "] 成功设置图传画面！";
            msg->setText(msgstr);
        } else {
            QString msgstr = "[" + QTime::currentTime().toString("hh:mm:ss.zzz") + "] 清除图传画面！";
            msg->setText(msgstr);
        }
    });

    // 模式选择
    operation_select = new QComboBox;
    operation_select->move(100, 640);
    operation_select->resize(100, 30);
    operation_select->addItem("添加", "add");
    operation_select->addItem("修改", "modify");
    operation_select->addItem("删除", "delete");
    operation_select->setParent(this);

    operation_tip = new QLabel;
    operation_tip->move(220, 640);
    operation_tip->resize(140, 30);
    operation_tip->setText("输入添加元素名:");
    operation_tip->setParent(this);

    addui_name = new QLineEdit;
    addui_name->move(380, 640);
    addui_name->resize(160, 30);
    addui_name->setParent(this);

    modifyui_name = new QComboBox;
    modifyui_name->move(380, 640);
    modifyui_name->resize(160, 30);
    modifyui_name->setParent(this);
    modifyui_name->hide();

    operation_button = new QPushButton;
    operation_button->resize(100, 30);
    operation_button->move(560, 640);
    operation_button->setText("添加");
    operation_button->setParent(this);

    clear_button = new QPushButton;
    clear_button->resize(100, 30);
    clear_button->move(670, 640);
    clear_button->setText("清空");
    clear_button->setParent(this);
    connect(clear_button, &QPushButton::clicked, this, [&](){
        graphics.clear();
        modifyui_name->clear();
        QString msgstr = "[" + QTime::currentTime().toString("hh:mm:ss.zzz") + "] 已清空所有图形！";
        msg->setText(msgstr);
        Draw();
    });

    grid_button = new QPushButton;
    grid_button->resize(100, 30);
    grid_button->move(780, 640);
    grid_button->setText("显示网格");
    grid_button->setParent(this);
    static char grid_show = 0;
    connect(grid_button, &QPushButton::clicked, this, [&](){
        grid_show = !grid_show;
        if(grid_show){
            layer2->show();
            grid_button->setText("隐藏网格");
        } else {
            layer2->hide();
            grid_button->setText("显示网格");
        }
    });

    tips_button = new QPushButton;
    tips_button->resize(100, 30);
    tips_button->move(1090, 760);
    tips_button->setText("说明");
    tips_button->setParent(this);
    connect(tips_button, &QPushButton::clicked, this, [&](){
        TipsWindow* tipswindow = new TipsWindow;
        tipswindow->show();
    });

    // 导出当前图形信息到剪贴板
    exportclip_button = new QPushButton;
    exportclip_button->resize(100, 30);
    exportclip_button->move(980, 760);
    exportclip_button->setText("导出剪贴板");
    exportclip_button->setParent(this);
    connect(exportclip_button, &QPushButton::clicked, this, [&](){
        QString export_str;
        for(int i = 0; i < int(graphics.size()); i++){
            export_str += graphics[i].name + " ";
            export_str += details_typeselect->itemText(graphics[i].figure_type) + " ";
            export_str += details_colorselect->itemText(graphics[i].color) + " ";
            long dataarray[8] = {graphics[i].details_a, graphics[i].details_b, graphics[i].width, graphics[i].start_x, graphics[i].start_y ,graphics[i].details_c, graphics[i].details_d, graphics[i].details_e};
            for(int j = 0; j <= 7; j++){
                if(detail_showmatrix[graphics[i].figure_type][j]){
                    export_str += (detail_labelmatrix[graphics[i].figure_type][j] + ":" + QString::number(dataarray[j]) + " ");
                }
            }
            if(graphics[i].figure_type == graphic_data::Text_Char) export_str += ("字符串:" + graphics[i].str + " ");
            export_str += "\n";
        }
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(export_str);
        QString msgstr = "[" + QTime::currentTime().toString("hh:mm:ss.zzz") + "] 已导出" + QString::number(graphics.size()) + "个图形到剪贴板！";
        msg->setText(msgstr);
    });

    // 导出文件
    export_button = new QPushButton;
    export_button->resize(100, 30);
    export_button->move(870, 760);
    export_button->setText("导出文件");
    export_button->setParent(this);
    connect(export_button, &QPushButton::clicked, this, [&](){
        QString filename = QFileDialog::getSaveFileName(this, tr("导出文件"), "", tr("RMUI Designer文件 (*.rmui)"));
        if (!filename.isNull()) {
            QFile file(filename);
            if (file.open(QIODevice::WriteOnly)) {
                QDataStream out(&file);
                // 图形数量
                unsigned char size = graphics.size();
                out.writeRawData((char*)(&size), sizeof(size));
                // 数据
                // 名字16,类型颜色1*2,参数2*8,字符串30,共64
                for(int i = 0; i < int(graphics.size()); i++){
                    unsigned char buffer[64] = {0};
                    for(int j = 0; j < int(graphics[i].name.length()); j++) buffer[j] = *(graphics[i].name.toUtf8().constData() + j);
                    buffer[16] = graphics[i].figure_type;
                    buffer[17] = graphics[i].color;
                    unsigned char* pdata[8] = {(unsigned char*)&graphics[i].details_a, (unsigned char*)&graphics[i].details_b, (unsigned char*)&graphics[i].width, (unsigned char*)&graphics[i].start_x,
                                               (unsigned char*)&graphics[i].start_y, (unsigned char*)&graphics[i].details_c, (unsigned char*)&graphics[i].details_d, (unsigned char*)&graphics[i].details_e};
                    for(int j = 0; j < 8; j++) memcpy(buffer + 18 + j * 2, pdata[j], 2);
                    for(int j = 0; j < int(graphics[i].str.length()); j++) buffer[34 + j] = *(graphics[i].str.toUtf8().constData() + j);
                    out.writeRawData((char*)(buffer), sizeof(buffer));
                }
                file.close();
                QString msgstr = "[" + QTime::currentTime().toString("hh:mm:ss.zzz") + "] 已导出文件！";
                msg->setText(msgstr);
            }
        } else {
            QString msgstr = "[" + QTime::currentTime().toString("hh:mm:ss.zzz") + "] 取消导出！";
            msg->setText(msgstr);
        }
    });

    // 导入文件
    import_button = new QPushButton;
    import_button->resize(100, 30);
    import_button->move(760, 760);
    import_button->setText("导入文件");
    import_button->setParent(this);
    connect(import_button, &QPushButton::clicked, this, [&](){
        QString filename = QFileDialog::getOpenFileName(this, tr("导入文件"), "", tr("RMUI Designer文件 (*.rmui)"));
        if (!filename.isNull()) {
            QFile file(filename);
            if (file.open(QIODevice::ReadOnly)) {
                QByteArray filedata = file.readAll();
                unsigned char size = filedata[0];
                for(int i = 0; i < size; i++){
                    char name[16] = {0};
                    for(int j = 0; j < 16; j++) name[j] = filedata[i * 64 + j + 1];
                    char str[30] = {0};
                    for(int j = 0; j < 30; j++) str[j] = filedata[i * 64 + j + 35];

                    char data_tochar[16] = {0};
                    for(int j = 0; j < 16; j++) data_tochar[j] = filedata[i * 64 + j + 19];
                    short* pdata[8];
                    for(int j = 0; j < 8; j++) pdata[j] = (short*)(&data_tochar[j * 2]);
                    graphic_data temp = {
                        .name = QString::fromUtf8((char*)name),
                        .figure_type = graphic_data::figure_type_e(char(filedata[i * 64 + 17])),
                        .color = graphic_data::color_e(char(filedata[i * 64 + 18])),
                        .details_a = *pdata[0],
                        .details_b = *pdata[1],
                        .width = *pdata[2],
                        .start_x = *pdata[3],
                        .start_y = *pdata[4],
                        .details_c = *pdata[5],
                        .details_d = *pdata[6],
                        .details_e = *pdata[7],
                        .str = QString::fromUtf8((char*)str)
                    };
                    graphics.push_back(temp);
                    modifyui_name->addItem(temp.name);
                }
                QString msgstr = "[" + QTime::currentTime().toString("hh:mm:ss.zzz") + "] 已添加" + QString::number(size) + "个图形 ！";
                msg->setText(msgstr);
                Draw();
            }
        }
    });

    // 提示信息
    msg = new QLabel;
    msg->resize(400, 30);
    msg->move(0, 770);
    msg->setStyleSheet("color: red");
    msg->setParent(this);

    connect(operation_select, &QComboBox::currentTextChanged, this, [&](){
        OperationChange();
        ModifyuiChange();
        GraphicTypeChange();
    });

    connect(modifyui_name, &QComboBox::currentTextChanged, this, [&](){
        ModifyuiChange();
        GraphicTypeChange();
    });

    connect(operation_button, &QPushButton::clicked, this, [&](){
        if(operation_select->currentData() == "add") {
            graphic_data temp = {
                .name = (addui_name->text() == "") ? ("graphic" + QString::number(graphics.size())) : addui_name->text(),
                .figure_type = graphic_data::figure_type_e(details_typeselect->currentData().toInt()),
                .color = graphic_data::color_e(details_colorselect->currentData().toInt()),
                .details_a = short(details_input[0]->text().toInt()),
                .details_b = short(details_input[1]->text().toInt()),
                .width = short(details_input[2]->text().toInt()),
                .start_x = short(details_input[3]->text().toInt()),
                .start_y = short(details_input[4]->text().toInt()),
                .details_c = short(details_input[5]->text().toInt()),
                .details_d = short(details_input[6]->text().toInt()),
                .details_e = short(details_input[7]->text().toInt()),
                .str = details_input[8]->text()
            };
            graphics.push_back(temp);
            modifyui_name->addItem(temp.name);
            QString msgstr = "[" + QTime::currentTime().toString("hh:mm:ss.zzz") + "] 已添加图形 " + temp.name + " ！";
            msg->setText(msgstr);
        } else if(operation_select->currentData() == "modify") {
            if(!graphics.size()) return;
            graphics[modifyui_name->currentIndex()].figure_type = graphic_data::figure_type_e(details_typeselect->currentData().toInt());
            graphics[modifyui_name->currentIndex()].color = graphic_data::color_e(details_colorselect->currentData().toInt());
            graphics[modifyui_name->currentIndex()].details_a = details_input[0]->text().toInt();
            graphics[modifyui_name->currentIndex()].details_b = details_input[1]->text().toInt();
            graphics[modifyui_name->currentIndex()].width = details_input[2]->text().toInt();
            graphics[modifyui_name->currentIndex()].start_x = details_input[3]->text().toInt();
            graphics[modifyui_name->currentIndex()].start_y = details_input[4]->text().toInt();
            graphics[modifyui_name->currentIndex()].details_c = details_input[5]->text().toInt();
            graphics[modifyui_name->currentIndex()].details_d = details_input[6]->text().toInt();
            graphics[modifyui_name->currentIndex()].details_e = details_input[7]->text().toInt();
            graphics[modifyui_name->currentIndex()].str = details_input[8]->text();
            QString msgstr = "[" + QTime::currentTime().toString("hh:mm:ss.zzz") + "] 已修改图形 " + graphics[modifyui_name->currentIndex()].name + " 的属性！";
            msg->setText(msgstr);
        } else if(operation_select->currentData() == "delete") {
            if(!graphics.size()) return;
            QString msgstr = "[" + QTime::currentTime().toString("hh:mm:ss.zzz") + "] 已删除 " + graphics[modifyui_name->currentIndex()].name + " ！";
            graphics.erase(graphics.begin() + modifyui_name->currentIndex());
            modifyui_name->removeItem(modifyui_name->currentIndex());
            msg->setText(msgstr);
        }
        Draw();
    });

    // 提示文本
    for(int i = 0; i < 11; i++) {
        details[i] = new QLabel;
        details[i]->move(100 + 80 * i, 680);
        details[i]->resize(80, 30);
        details[i]->setStyleSheet("QLabel{font: 8pt; text-align: center}");
        details[i]->setParent(this);
    }

    // 类型选择
    details_typeselect = new QComboBox;
    details_typeselect->move(100, 720);
    details_typeselect->resize(70, 30);
    details_typeselect->setParent(this);
    details_typeselect->addItem("直线", "0");
    details_typeselect->addItem("矩形", "1");
    details_typeselect->addItem("正圆", "2");
    details_typeselect->addItem("椭圆", "3");
    details_typeselect->addItem("圆弧", "4");
    details_typeselect->addItem("浮点", "5");
    details_typeselect->addItem("整形", "6");
    details_typeselect->addItem("字符", "7");

    // 颜色选择
    details_colorselect = new QComboBox;
    details_colorselect->move(180, 720);
    details_colorselect->resize(70, 30);
    details_colorselect->setParent(this);
    details_colorselect->addItem("红色", "0");
    details_colorselect->addItem("黄色", "1");
    details_colorselect->addItem("绿色", "2");
    details_colorselect->addItem("橙色", "3");
    details_colorselect->addItem("紫红", "4");
    details_colorselect->addItem("粉色", "5");
    details_colorselect->addItem("青色", "6");
    details_colorselect->addItem("黑色", "7");
    details_colorselect->addItem("白色", "8");

    // 图形参数输入框
    for(int i = 0; i < 9; i++){
        details_input[i] = new QLineEditRanged;
        details_input[i]->move(260 + 80 * i, 720);
        details_input[i]->resize(i == 8 ? 220 : 70, 30);
        details_input[i]->setText("0");
        details_input[i]->setParent(this);
    }

    // 参数显示(删除模式下)
    details_typeselect_label = new QLabel;
    details_typeselect_label->move(100, 720);
    details_typeselect_label->resize(70, 30);
    details_typeselect_label->setParent(this);
    details_typeselect_label->hide();

    details_colorselect_label = new QLabel;
    details_colorselect_label->move(180, 720);
    details_colorselect_label->resize(70, 30);
    details_colorselect_label->setParent(this);
    details_colorselect_label->hide();

    for(int i = 0; i < 9; i++){
        details_input_label[i] = new QLabel;
        details_input_label[i]->move(260 + 80 * i, 720);
        details_input_label[i]->resize(i == 8 ? 220 : 70, 30);
        details_input_label[i]->setParent(this);
        details_input_label[i]->hide();
    }

    // 数值范围限制
    QRegularExpressionValidator *validator[8];
    int max_limit[8] = {511, 511, 1023, 2047, 2047, 1023, 2047, 2047};
    for(int i = 0; i < 8; i++){
        validator[i] = new QRegularExpressionValidator(QRegularExpression("-?\\d+"), details_input[i]);
        details_input[i]->setValidator(validator[i]);
        details_input[i]->setRange(0, max_limit[i]);
        details_input[i]->enableLimit();
    }
    // 字符串限制输入ascii字符
    details_input[8]->setMaxLength(30);
    QRegularExpressionValidator *strvalidator;
    strvalidator = new QRegularExpressionValidator(QRegularExpression("[\\x20-\\x7E]+"), details_input[8]);
    details_input[8]->setValidator(strvalidator);
    // 图形命名规则依照c语言变量命名(关键字规则除外)
    addui_name->setMaxLength(16);
    QRegularExpressionValidator *namevalidator;
    namevalidator = new QRegularExpressionValidator(QRegularExpression("^(?!\\d)\\w+$"), addui_name);
    addui_name->setValidator(namevalidator);

    details[0]->setText("图形类型");
    details[1]->setText("颜色");
    for(int i = 0; i < 9; i++) {
        details[i + 2]->setText(detail_labelmatrix[0][i]);
        if(!detail_showmatrix[0][i]){
            details[i + 2]->hide();
            details_input[i]->hide();
        }
    }

    connect(details_typeselect, &QComboBox::currentTextChanged, this, [&](){
        GraphicTypeChange();
    });
}


MainWindow::~MainWindow()
{
    delete ui;
}


/************************************************************
FileName: YGIS.h
Author: yuanlin
Version : 1.0
Date: 2024-06-28
Description: // 主界面的头文件
Function List: // 主界面的头文件
1. -------
History: // 历史修改记录
<author> <time> <version > <desc>
yuanlin 24/06/28 1.0 build this moudle
***********************************************************/


#include <QtWidgets/QMainWindow>
#include "ui_YGIS.h"
#include <QLabel>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QMouseEvent>
#include "mainwindow.h"
#include "delaunay.h"
#include "ogrsf_frmts.h"
#include <gdal.h>
#include <gdal_priv.h>
#include <ogrsf_frmts.h>
#include <QPainter>
#include <QFileDialog>
#include <QMouseEvent>
#include <QInputDialog>
#include <QColorDialog>
#include <QDesktopServices>
#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QString>
#include <QWidget>
#include <QApplication>

#include <QUndoStack>
#include <QUndoCommand>

//#include "AllCommands.h"

#define EPSILON 0.000001

class YGIS : public QMainWindow
{
    Q_OBJECT

public:
    YGIS(QWidget* parent = nullptr);
    ~YGIS();

public slots:
    void openFile();
    void saveToShapefile(const QString& filename);
    void exitApplication();  // 用于处理退出程序的槽函数
    void showmainwindow();  // 用于显示 paint 窗口的槽函数
    void on_actionbuffer_triggered(); //生成缓冲区
    void on_item_double_clicked(QTreeWidgetItem* item, int column);
    void on_actionrandom_triggered();
    void on_TIN_double_clicked(QTreeWidgetItem* item, int column);
    void on_Count_double_clicked(QTreeWidgetItem* item, int column);
    void on_Count_triggered();
    void on_Area_double_clicked(QTreeWidgetItem* item, int column);
    void on_Area_triggered();
    void on_Paint_double_clicked(QTreeWidgetItem* item, int column);
    void openTIF();  //专门开栅格文件
    void loadTifFile(const QString& sfileName);
    void disOpenTIF();
    void on_mask_double_clicked(QTreeWidgetItem* item, int column);
    void on_masks_double_clicked(QTreeWidgetItem* item, int column);
    void on_mask_triggered();
    void on_masks_triggered();
    void on_statistics_double_clicked(QTreeWidgetItem* item, int column);
    void on_statistics_triggered();

protected:
    void wheelEvent(QWheelEvent* event) override;  // 用于处理滚轮事件，实现缩放功能


public:
    Ui::YGISClass ui;
    
    QGraphicsView* view;  // 用于显示图片的视图
    QGraphicsScene* scene;  // 场景
    QGraphicsPixmapItem* pixmapItem;  // 图片项
    MainWindow* mainwindow;  // paint 窗口实例

    void displayImage(const QString& filePath);  // 显示图片

    void mousePressEvent(QMouseEvent* event);	// 鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);	// 鼠标移动事件


//protected:

    void loadShapefile(const QString& filePath);
    void disLoadShapefile(); //  
    void onLayerItemChanged(QTreeWidgetItem* item, int column);

private:
    QUndoStack* undoStack;   // 撤销栈
    GDALDataset* poDS;
    QVector<QPointF> points;  // 添加points声明
    QPen pen;			     // 点的颜色和大小
    QAction* action_buffer;  //定义缓冲区
    int n;
    QAction* action_mask;  //定义直方图输出
    QAction* action_masks;  //定义均衡化增强显示直方图输出
    QAction* action_statistics;  //定义领域统计
    QAction* action_TIN;  //定义TIN
    QAction* action_Count;  //定义矢量统计工具数量统计
    QAction* action_Area;  //定义矢量统计工具面积统计
    QAction* action_Paint;  //定义打开Paint窗口

private slots:
    // 程序按钮对应的槽函数，切换程序状态
    void on_action_point_triggered();
    void on_action_line_triggered();
    void on_action_triangle_triggered();
    void on_action_rectangle_triggered();
    void on_action_circle_triggered();
    void on_action_ellipse_triggered();
    void on_action_polygon_triggered();
    void on_action_curve_triggered();
    void on_action_translate_triggered();
    void on_action_rotate_triggered();
    void on_action_palette_triggered();
    void on_action_trash_triggered();
    void on_action_zoomin_triggered();
    void on_action_zoomout_triggered();
    void on_action_clip_triggered();
    void on_action_addpoint_triggered();
    void on_action_deletepoint_triggered();
    void on_action_help_triggered();
    void on_action_save_triggered();
    void on_action_save_txt();

};

// 自定义对话框类
class CustomMessageBox : public QDialog {
    Q_OBJECT

public:
    CustomMessageBox(const QString& title, const QString& text, QWidget* parent = nullptr)
        : QDialog(parent)
    {
        setWindowTitle(title);

        // 设置布局
        QVBoxLayout* layout = new QVBoxLayout(this);

        // 创建文本显示控件
        QLabel* messageLabel = new QLabel(text, this);
        layout->addWidget(messageLabel);

        // 创建按钮
        QPushButton* okButton = new QPushButton("OK", this);
        layout->addWidget(okButton);

        // 连接按钮点击信号与对话框接受信号
        connect(okButton, &QPushButton::clicked, this, &CustomMessageBox::accept);

        // 设置对话框布局
        setLayout(layout);
        resize(300, 150); // 设置对话框初始大小
    }
};

// 打开shp文件命令
class LoadShapefileCommand : public QUndoCommand {
public:
    LoadShapefileCommand(YGIS* prYgisReceiver, const QString& sFilePath)
        : prYgisReceiver(prYgisReceiver), sFilePath(sFilePath) {}

    void redo() {
        prYgisReceiver->loadShapefile(sFilePath);
    }
    void undo() {
        prYgisReceiver->disLoadShapefile();
    }

private:
    YGIS* prYgisReceiver;
    QString sFilePath;
};

// 打开tif文件命令
class LoadTiffileCommand : public QUndoCommand {
public:
    LoadTiffileCommand(YGIS* prYgisReceiver, const QString& sFilePath)
        : prYgisReceiver(prYgisReceiver), sFilePath(sFilePath) {}

    void redo() {
        prYgisReceiver->openTIF();
    }
    void undo() {
        prYgisReceiver->disOpenTIF();
    }

private:
    YGIS* prYgisReceiver;
    QString sFilePath;
};

/************************************************************
FileName: YGIS.h
Author: yuanlin
Version : 1.0
Date: 2024-06-28
Description: // �������ͷ�ļ�
Function List: // �������ͷ�ļ�
1. -------
History: // ��ʷ�޸ļ�¼
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
    void exitApplication();  // ���ڴ����˳�����Ĳۺ���
    void showmainwindow();  // ������ʾ paint ���ڵĲۺ���
    void on_actionbuffer_triggered(); //���ɻ�����
    void on_item_double_clicked(QTreeWidgetItem* item, int column);
    void on_actionrandom_triggered();
    void on_TIN_double_clicked(QTreeWidgetItem* item, int column);
    void on_Count_double_clicked(QTreeWidgetItem* item, int column);
    void on_Count_triggered();
    void on_Area_double_clicked(QTreeWidgetItem* item, int column);
    void on_Area_triggered();
    void on_Paint_double_clicked(QTreeWidgetItem* item, int column);
    void openTIF();  //ר�ſ�դ���ļ�
    void loadTifFile(const QString& sfileName);
    void disOpenTIF();
    void on_mask_double_clicked(QTreeWidgetItem* item, int column);
    void on_masks_double_clicked(QTreeWidgetItem* item, int column);
    void on_mask_triggered();
    void on_masks_triggered();
    void on_statistics_double_clicked(QTreeWidgetItem* item, int column);
    void on_statistics_triggered();

protected:
    void wheelEvent(QWheelEvent* event) override;  // ���ڴ�������¼���ʵ�����Ź���


public:
    Ui::YGISClass ui;
    
    QGraphicsView* view;  // ������ʾͼƬ����ͼ
    QGraphicsScene* scene;  // ����
    QGraphicsPixmapItem* pixmapItem;  // ͼƬ��
    MainWindow* mainwindow;  // paint ����ʵ��

    void displayImage(const QString& filePath);  // ��ʾͼƬ

    void mousePressEvent(QMouseEvent* event);	// ��갴���¼�
    void mouseMoveEvent(QMouseEvent* event);	// ����ƶ��¼�


//protected:

    void loadShapefile(const QString& filePath);
    void disLoadShapefile(); //  
    void onLayerItemChanged(QTreeWidgetItem* item, int column);

private:
    QUndoStack* undoStack;   // ����ջ
    GDALDataset* poDS;
    QVector<QPointF> points;  // ���points����
    QPen pen;			     // �����ɫ�ʹ�С
    QAction* action_buffer;  //���建����
    int n;
    QAction* action_mask;  //����ֱ��ͼ���
    QAction* action_masks;  //������⻯��ǿ��ʾֱ��ͼ���
    QAction* action_statistics;  //��������ͳ��
    QAction* action_TIN;  //����TIN
    QAction* action_Count;  //����ʸ��ͳ�ƹ�������ͳ��
    QAction* action_Area;  //����ʸ��ͳ�ƹ������ͳ��
    QAction* action_Paint;  //�����Paint����

private slots:
    // ����ť��Ӧ�Ĳۺ������л�����״̬
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

// �Զ���Ի�����
class CustomMessageBox : public QDialog {
    Q_OBJECT

public:
    CustomMessageBox(const QString& title, const QString& text, QWidget* parent = nullptr)
        : QDialog(parent)
    {
        setWindowTitle(title);

        // ���ò���
        QVBoxLayout* layout = new QVBoxLayout(this);

        // �����ı���ʾ�ؼ�
        QLabel* messageLabel = new QLabel(text, this);
        layout->addWidget(messageLabel);

        // ������ť
        QPushButton* okButton = new QPushButton("OK", this);
        layout->addWidget(okButton);

        // ���Ӱ�ť����ź���Ի�������ź�
        connect(okButton, &QPushButton::clicked, this, &CustomMessageBox::accept);

        // ���öԻ��򲼾�
        setLayout(layout);
        resize(300, 150); // ���öԻ����ʼ��С
    }
};

// ��shp�ļ�����
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

// ��tif�ļ�����
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

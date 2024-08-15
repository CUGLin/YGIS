#ifndef YGIS_H
#define YGIS_H

#include "YGIS.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QWheelEvent>
#include <QScrollBar>
#include <QTreeWidgetItem>
#include <algorithm>
#include <vector>
#include <iostream>
#include <QTextEdit>



//#include "MyLogger/MyLogger.h"

YGIS::YGIS(QWidget* parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);

    // ��ʼ����ͼ�ͳ���
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    pixmapItem = new QGraphicsPixmapItem();
    scene->addItem(pixmapItem);
    view->setScene(scene);
    setCentralWidget(view);

    // ��ʼ�� paint ����
    mainwindow = new MainWindow(this);
    


    // ������������
    connect(ui.actionLastStep, &QAction::triggered, undoStack, &QUndoStack::undo);
    connect(ui.actionNextStep, &QAction::triggered, undoStack, &QUndoStack::redo);

    // ���Ӵ��ļ�����
    connect(ui.actionOpenFile, &QAction::triggered, this, &YGIS::openFile);

    //���Ӵ�դ���ļ�
    connect(ui.actionOpenTIF, &QAction::triggered, this, &YGIS::openTIF);

    //���ӱ����ļ�����
    connect(ui.actionSaveFile, &QAction::triggered, this, &YGIS::on_action_save_triggered);

    // �����˳��������
    connect(ui.actionexit, &QAction::triggered, this, &YGIS::exitApplication);

    // ������ʾ paint ���ڲ���
    connect(ui.actionStart, &QAction::triggered, this, &YGIS::showmainwindow);

    // ���ӱ��� txt �ı��ļ�����
    connect(ui.actionSaveTXT, &QAction::triggered, this, &YGIS::on_action_save_txt);

    // ��ʾDock����
    connect(ui.actionShowBrowser, &QAction::triggered, ui.Browser, &QDockWidget::show);
    connect(ui.actionShowLayer, &QAction::triggered, ui.Layer, &QDockWidget::show);
    connect(ui.actionShowToolBox, &QAction::triggered, ui.ToolBox, &QDockWidget::show);

    //����ʸ���༭����
    connect(ui.action_point, &QAction::triggered, this, &YGIS::on_action_point_triggered);
    connect(ui.action_line, &QAction::triggered, this, &YGIS::on_action_line_triggered);
    connect(ui.action_triangle, &QAction::triggered, this, &YGIS::on_action_triangle_triggered);
    connect(ui.action_rectangle, &QAction::triggered, this, &YGIS::on_action_rectangle_triggered);
    connect(ui.action_circle, &QAction::triggered, this, &YGIS::on_action_circle_triggered);
    connect(ui.action_ellipse, &QAction::triggered, this, &YGIS::on_action_ellipse_triggered);
    connect(ui.action_polygon, &QAction::triggered, this, &YGIS::on_action_polygon_triggered);
    connect(ui.action_translate, &QAction::triggered, this, &YGIS::on_action_translate_triggered);
    connect(ui.action_rotate, &QAction::triggered, this, &YGIS::on_action_rotate_triggered);
    connect(ui.action_palette, &QAction::triggered, this, &YGIS::on_action_palette_triggered);
    connect(ui.action_trash, &QAction::triggered, this, &YGIS::on_action_trash_triggered);
    connect(ui.action_zoomin, &QAction::triggered, this, &YGIS::on_action_zoomin_triggered);
    connect(ui.action_zoomout, &QAction::triggered, this, &YGIS::on_action_zoomout_triggered);
    connect(ui.action_clip, &QAction::triggered, this, &YGIS::on_action_clip_triggered);
    connect(ui.action_addpoint, &QAction::triggered, this, &YGIS::on_action_addpoint_triggered);
    connect(ui.action_deletepoint, &QAction::triggered, this, &YGIS::on_action_deletepoint_triggered);
    connect(ui.action_help, &QAction::triggered, this, &YGIS::on_action_help_triggered);

    //ֱ��ͼ���
    action_mask = new QAction("Histogram Display", this);
    connect(ui.treeWidget_toolbox, &QTreeWidget::itemDoubleClicked, this, &YGIS::on_mask_double_clicked);

    //���⻯��ǿ��ʾֱ��ͼ���
    action_masks = new QAction("Histogram Equalization", this);
    connect(ui.treeWidget_toolbox, &QTreeWidget::itemDoubleClicked, this, &YGIS::on_masks_double_clicked);

    //����ͳ��
    action_statistics = new QAction("Neighborhood Statistics", this);
    connect(ui.treeWidget_toolbox, &QTreeWidget::itemDoubleClicked, this, &YGIS::on_statistics_double_clicked);

    //������
    action_buffer = new QAction("Buffer Calculation", this);
    connect(ui.treeWidget_toolbox, &QTreeWidget::itemDoubleClicked, this, &YGIS::on_item_double_clicked);

    //������������TIN
    action_TIN = new QAction("Start TIN", this);
    connect(ui.treeWidget_toolbox, &QTreeWidget::itemDoubleClicked, this, &YGIS::on_TIN_double_clicked);

    //����ͳ��
    action_Count = new QAction("Count", this);
    connect(ui.treeWidget_toolbox, &QTreeWidget::itemDoubleClicked, this, &YGIS::on_Count_double_clicked);

    //���ͳ��
    action_Area = new QAction("Area", this);
    connect(ui.treeWidget_toolbox, &QTreeWidget::itemDoubleClicked, this, &YGIS::on_Area_double_clicked);

    //paint��
    action_Paint = new QAction("Paint", this);
    connect(ui.treeWidget_toolbox, &QTreeWidget::itemDoubleClicked, this, &YGIS::on_Paint_double_clicked);

    // ���ToolBox������Ŀ
    QTreeWidgetItem* item1 = new QTreeWidgetItem(ui.treeWidget_toolbox, QStringList("Raster Statistics"));
    QTreeWidgetItem* item2 = new QTreeWidgetItem(ui.treeWidget_toolbox, QStringList("Vector Geometry Analysis"));
    QTreeWidgetItem* item3 = new QTreeWidgetItem(ui.treeWidget_toolbox, QStringList("Vector Statistics Analysis"));
    QTreeWidgetItem* item4 = new QTreeWidgetItem(ui.treeWidget_toolbox, QStringList("Draw for everything"));

    // ����ToolBox������Ŀͼ��
    item1->setIcon(0, QIcon(":/YGIS/res/TOOLBOX .png"));
    item2->setIcon(0, QIcon(":/YGIS/res/TOOLBOX .png"));
    item3->setIcon(0, QIcon(":/YGIS/res/TOOLBOX .png"));
    item4->setIcon(0, QIcon(":/YGIS/res/TOOLBOX .png"));

    // ���ToolBox����Ŀ
    QTreeWidgetItem* subItem1 = new QTreeWidgetItem(item1, QStringList("Histogram Display"));
    QTreeWidgetItem* subItem2 = new QTreeWidgetItem(item1, QStringList("Histogram Equalization"));
    QTreeWidgetItem* subItem3 = new QTreeWidgetItem(item1, QStringList("Neighborhood Statistics"));
    QTreeWidgetItem* subItem4 = new QTreeWidgetItem(item2, QStringList("Start TIN"));
    QTreeWidgetItem* subItem5 = new QTreeWidgetItem(item2, QStringList("Buffer Calculation"));
    QTreeWidgetItem* subItem6 = new QTreeWidgetItem(item3, QStringList("Count"));
    QTreeWidgetItem* subItem7 = new QTreeWidgetItem(item3, QStringList("Area"));
    QTreeWidgetItem* subItem8 = new QTreeWidgetItem(item4, QStringList("Paint"));

    // ����ToolBox����Ŀͼ��
    subItem1->setIcon(0, QIcon(":/YGIS/res/yanmo.png"));
    subItem2->setIcon(0, QIcon(":/YGIS/res/yanmo.png"));
    subItem3->setIcon(0, QIcon(":/YGIS/res/tongji.png"));
    subItem4->setIcon(0, QIcon(":/YGIS/res/tubao.png"));
    subItem5->setIcon(0, QIcon(":/YGIS/res/huanchong.png"));
    subItem6->setIcon(0, QIcon(":/YGIS/res/Count.png"));
    subItem7->setIcon(0, QIcon(":/YGIS/res/Area.png"));
    subItem8->setIcon(0, QIcon(":/YGIS/res/paint.png"));

    // ���Browser������Ŀ
    QTreeWidgetItem* item11 = new QTreeWidgetItem(ui.treeWidget_Browser, QStringList("C:\(Windows-SSD)"));
    QTreeWidgetItem* item21 = new QTreeWidgetItem(ui.treeWidget_Browser, QStringList("D:\(Data)"));
    QTreeWidgetItem* item31 = new QTreeWidgetItem(ui.treeWidget_Browser, QStringList("PostgreSQL"));
    QTreeWidgetItem* item41 = new QTreeWidgetItem(ui.treeWidget_Browser, QStringList("Oracle"));
    QTreeWidgetItem* item51 = new QTreeWidgetItem(ui.treeWidget_Browser, QStringList("WMS"));
    QTreeWidgetItem* item61 = new QTreeWidgetItem(ui.treeWidget_Browser, QStringList("New idea"));
    QTreeWidgetItem* item71 = new QTreeWidgetItem(ui.treeWidget_Browser, QStringList("Upvote"));
    QTreeWidgetItem* item81 = new QTreeWidgetItem(ui.treeWidget_Browser, QStringList("Collect"));
    QTreeWidgetItem* item91 = new QTreeWidgetItem(ui.treeWidget_Browser, QStringList("Share"));

    // ����Browser������Ŀͼ��
    item11->setIcon(0, QIcon(":/YGIS/res/bigfile.png"));
    item21->setIcon(0, QIcon(":/YGIS/res/bigfile.png"));
    item31->setIcon(0, QIcon(":/YGIS/res/PostgreSQL.png"));
    item41->setIcon(0, QIcon(":/YGIS/res/Oracle.png"));
    item51->setIcon(0, QIcon(":/YGIS/res/WMS.png"));
    item61->setIcon(0, QIcon(":/YGIS/res/idea.png"));
    item71->setIcon(0, QIcon(":/YGIS/res/love.png"));
    item81->setIcon(0, QIcon(":/YGIS/res/enjoy.png"));
    item91->setIcon(0, QIcon(":/YGIS/res/share.png"));

    // ���Browser����Ŀ
    QTreeWidgetItem* subItem11 = new QTreeWidgetItem(item11, QStringList("PerfLogs"));
    QTreeWidgetItem* subItem21 = new QTreeWidgetItem(item11, QStringList("PerfLogs Files"));
    QTreeWidgetItem* subItem31 = new QTreeWidgetItem(item11, QStringList("Program Files"));
    QTreeWidgetItem* subItem41 = new QTreeWidgetItem(item11, QStringList("Program Files (x86)"));
    QTreeWidgetItem* subItem51 = new QTreeWidgetItem(item11, QStringList("Users"));
    QTreeWidgetItem* subItem61 = new QTreeWidgetItem(item11, QStringList("Windows"));
    QTreeWidgetItem* subItem71 = new QTreeWidgetItem(item21, QStringList("BaiduNetdisk"));
    QTreeWidgetItem* subItem81 = new QTreeWidgetItem(item21, QStringList("BaiduNetdiskDownload"));
    QTreeWidgetItem* subItem91 = new QTreeWidgetItem(item21, QStringList("Clash"));
    QTreeWidgetItem* subItem101 = new QTreeWidgetItem(item21, QStringList("Java"));
    QTreeWidgetItem* subItem111 = new QTreeWidgetItem(item21, QStringList("Miscroft VS Code"));
    QTreeWidgetItem* subItem121 = new QTreeWidgetItem(item21, QStringList("OSGeo4W"));
    QTreeWidgetItem* subItem131 = new QTreeWidgetItem(item21, QStringList("QGIS"));
    QTreeWidgetItem* subItem141 = new QTreeWidgetItem(item21, QStringList("QT"));
    QTreeWidgetItem* subItem151 = new QTreeWidgetItem(item21, QStringList("WeChatFile"));

    // ����Browser����Ŀͼ��
    subItem11->setIcon(0, QIcon(":/YGIS/res/smallfile.png"));
    subItem21->setIcon(0, QIcon(":/YGIS/res/smallfile.png"));
    subItem31->setIcon(0, QIcon(":/YGIS/res/smallfile.png"));
    subItem41->setIcon(0, QIcon(":/YGIS/res/smallfile.png"));
    subItem51->setIcon(0, QIcon(":/YGIS/res/smallfile.png"));
    subItem61->setIcon(0, QIcon(":/YGIS/res/smallfile.png"));
    subItem71->setIcon(0, QIcon(":/YGIS/res/smallfile.png"));
    subItem81->setIcon(0, QIcon(":/YGIS/res/smallfile.png"));
    subItem91->setIcon(0, QIcon(":/YGIS/res/smallfile.png"));
    subItem101->setIcon(0, QIcon(":/YGIS/res/smallfile.png"));
    subItem111->setIcon(0, QIcon(":/YGIS/res/smallfile.png"));
    subItem121->setIcon(0, QIcon(":/YGIS/res/smallfile.png"));
    subItem131->setIcon(0, QIcon(":/YGIS/res/smallfile.png"));
    subItem141->setIcon(0, QIcon(":/YGIS/res/smallfile.png"));
    subItem151->setIcon(0, QIcon(":/YGIS/res/smallfile.png"));

    //����״̬��
    QStatusBar* m_statusBar = this->statusBar();
    //��ӵײ�״̬���������Ϣ
    QLabel* labelLeft = new QLabel("EPSG:4326", this);
    m_statusBar->addWidget(labelLeft);

    QLabel* labelRight = new QLabel("UTF-8", this);
    m_statusBar->addPermanentWidget(labelRight);
}

YGIS::~YGIS()
{
    //delete mainwindow; //�ͷſ��´��ڵ�ָ��
    //delete scene;
    //delete view;
    // 
    // ɾ��������ָ��
    if (mainwindow) {
        delete mainwindow;
        mainwindow = nullptr;
    }
    // ɾ����������ͼ�е�������
    if (scene) {
        scene->clear();  // ����������е�����ͼ����
        delete scene;
        scene = nullptr;
    }
    // ɾ����ͼָ��
    if (view) {
        delete view;
        view = nullptr;
    }
    // ɾ�� QUndoStack ָ��
    if (undoStack) {
        delete undoStack;
        undoStack = nullptr;
    }
}

void YGIS::openFile()
{
    QString sfileName = QFileDialog::getOpenFileName(this, tr("Open Shapefile"), "/home", tr("Shapefiles (*.shp)"));

    if (!sfileName.isEmpty()) {
        //auto command = new LoadShapefileCommand(this, sfileName);
        //undoStack->push(command);
        loadShapefile(sfileName);
    }
    if (sfileName.isEmpty())
        return;

    //loadShapefile(sfileName);
    //Logger::info("��shp�ļ��ɹ�");
}



void YGIS::loadShapefile(const QString& filePath)
{
    GDALAllRegister();
    CPLSetConfigOption("SHAPE_ENCODING", "");  //���������������

    poDS = (GDALDataset*)GDALOpenEx(filePath.toUtf8().constData(), GDAL_OF_VECTOR, NULL, NULL, NULL);
    if (poDS == NULL)
    {
        QMessageBox::warning(this, tr("�� Shapefile"), tr("�ļ��޷��򿪡�"), QMessageBox::Ok);
        return;
    }

    // ���� TreeWidgetItem������ӵ� treeWidget_Layer
    QTreeWidgetItem* layerItem = new QTreeWidgetItem(ui.treeWidget_Layer);
    layerItem->setText(0, QFileInfo(filePath).fileName());
    layerItem->setCheckState(0, Qt::Checked);  // Ĭ�Ϲ�ѡ
    ui.treeWidget_Layer->addTopLevelItem(layerItem);

    // ���� checkbox ״̬�仯�źŵ��ۺ���
    connect(ui.treeWidget_Layer, &QTreeWidget::itemChanged, this, &YGIS::onLayerItemChanged);

    // ����ͼ����
    QGraphicsItemGroup* layerGroup = new QGraphicsItemGroup();
    scene->addItem(layerGroup);

    OGRLayer* poLayer = poDS->GetLayer(0); //��ȡͼ��

    OGRFeature* poFeature;
    poLayer->ResetReading();

    while ((poFeature = poLayer->GetNextFeature()) != NULL)
    {
        OGRGeometry* poGeometry = poFeature->GetGeometryRef();
        QGraphicsItem* item = nullptr;

        if (poGeometry != NULL)
        {
            switch (wkbFlatten(poGeometry->getGeometryType()))
            {
            case wkbPoint:
            {
                OGRPoint* poPoint = (OGRPoint*)poGeometry;
                QGraphicsEllipseItem* pointItem = new QGraphicsEllipseItem(poPoint->getX() - 2, -poPoint->getY() - 2, 4, 4);
                pointItem->setPen(QPen(Qt::red));
                pointItem->setBrush(QBrush(Qt::red));
                item = pointItem;
                break;
            }
            case wkbLineString:
            {
                OGRLineString* poLine = (OGRLineString*)poGeometry;
                QPainterPath path;

                path.moveTo(poLine->getX(0), -poLine->getY(0));
                for (int i = 1; i < poLine->getNumPoints(); i++)
                {
                    path.lineTo(poLine->getX(i), -poLine->getY(i));
                }

                QGraphicsPathItem* lineItem = new QGraphicsPathItem(path);
                lineItem->setPen(QPen(Qt::green));
                item = lineItem;
                break;
            }
            case wkbPolygon:
            {
                OGRPolygon* poPolygon = (OGRPolygon*)poGeometry;
                OGRLinearRing* poRing = poPolygon->getExteriorRing();
                QPolygonF polygon;

                for (int i = 0; i < poRing->getNumPoints(); i++)
                {
                    polygon << QPointF(poRing->getX(i), -poRing->getY(i));
                }

                QGraphicsPolygonItem* polygonItem = new QGraphicsPolygonItem(polygon);
                polygonItem->setPen(QPen(pen));
                polygonItem->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
                item = polygonItem;
                break;
            }
            }

            if (item)
            {
                layerGroup->addToGroup(item);
            }
        }
        OGRFeature::DestroyFeature(poFeature);
    }

    // ���� layerGroup �� TreeWidgetItem
    layerItem->setData(0, Qt::UserRole, QVariant::fromValue<void*>(layerGroup));

    // ������ͼ���ʺϴ�С
    view->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void YGIS::disLoadShapefile() {

}

void YGIS::onLayerItemChanged(QTreeWidgetItem* item, int column)
{
    if (column == 0) // ����� checkbox ��
    {
        QGraphicsItemGroup* layerGroup = static_cast<QGraphicsItemGroup*>(item->data(0, Qt::UserRole).value<void*>());
        if (layerGroup)
        {
            layerGroup->setVisible(item->checkState(0) == Qt::Checked);
        }
    }
}



void YGIS::displayImage(const QString& filePath)
{
    QImage image(filePath);
    if (image.isNull())
    {
        // ����������ʾ
        QMessageBox::warning(this, tr("��ͼƬ"), tr("�ļ��޷��򿪡�"), QMessageBox::Ok);
        return;
    }

    // ��ͼƬ����Ϊͼ���������
    pixmapItem->setPixmap(QPixmap::fromImage(image));
    view->fitInView(pixmapItem, Qt::KeepAspectRatio);

    // �������ι���
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    view->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
}

void YGIS::wheelEvent(QWheelEvent* event)
{
    // ʵ�����Ź���
    if (event->angleDelta().y() > 0)
        view->scale(1.5, 1.5); // �Ŵ�
    else
        view->scale(0.5, 0.5); // ��С
    event->accept();
}



void YGIS::exitApplication()
{
    // �˳�����
    QApplication::quit();
}

void YGIS::showmainwindow()
{
    // ��ʾ paint ����
    mainwindow->show();
}


enum DrawMode
{
    NoDrawing,
    DrawPoint,
    DrawLine
};

DrawMode currentMode = NoDrawing; // Ĭ�ϲ�����

void YGIS::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF point = view->mapToScene(event->pos());

        if (currentMode == DrawPoint)
        {
            points.append(point);  // ʹ�� QVector<QPointF> �洢��
            scene->addEllipse(point.x() - 2, point.y() - 2, 4, 4, QPen(), QBrush(Qt::SolidPattern));
        }
        else if (currentMode == DrawLine)
        {
            points.append(point);  // ʹ�� QVector<QPointF> �洢��
            scene->addEllipse(point.x() - 2, point.y() - 2, 4, 4, QPen(), QBrush(Qt::SolidPattern));
            if (points.size() > 1)
            {
                scene->addLine(QLineF(points[points.size() - 2], point), QPen(Qt::black, 2));
            }
        }
    }
}

void YGIS::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        QPointF point = view->mapToScene(event->pos());

        if (currentMode == DrawLine)
        {
            scene->addLine(QLineF(points.last(), point), QPen(Qt::gray, 1, Qt::DashLine));
        }
    }
}

void YGIS::on_action_point_triggered()
{
    currentMode = DrawPoint; // �л������Ƶ��ģʽ
}

void YGIS::on_action_line_triggered()
{
    currentMode = DrawLine; // �л�������ֱ�ߵ�ģʽ
}

//��������ȥʵ�ֵĻ��Ʋ���
void YGIS::on_action_triangle_triggered() 
{
    // ʵ�������λ���
}

void YGIS::on_action_rectangle_triggered() 
{
    // ʵ�־��λ���
}

void YGIS::on_action_circle_triggered()
{
    // ʵ��Բ�λ���
}

void YGIS::on_action_ellipse_triggered() 
{
    // ʵ����Բ����
}

void YGIS::on_action_polygon_triggered()
{
    // ʵ�ֶ���λ���
}

void YGIS::on_action_curve_triggered() 
{
    // ʵ�����߻���
}

void YGIS::on_action_translate_triggered()
{
    // ʵ��ƽ�Ʋ���
}

void YGIS::on_action_rotate_triggered() 
{
    // ʵ����ת����
}

void YGIS::on_action_palette_triggered() 
{
    // ʵ�ֵ�ɫ�����
}

void YGIS::on_action_trash_triggered() 
{
    // ʵ����ջ�������
}

void YGIS::on_action_zoomin_triggered()
{
    // ʵ�ַŴ����
}

void YGIS::on_action_zoomout_triggered()
{
   // ʵ����С����
}

void YGIS::on_action_clip_triggered() 
{
    // ʵ�ֲü�����
}

void YGIS::on_action_addpoint_triggered()
{
    // ʵ����ӵ����
}

void YGIS::on_action_deletepoint_triggered() 
{
    // ʵ��ɾ�������
}


void YGIS::on_action_help_triggered()
{
    QDesktopServices::openUrl(QUrl("https://cuglin.pages.dev"));
}

void YGIS::on_action_save_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Shapefile", "", "Shapefiles (*.shp)");
    if (!filename.isEmpty()) {
        saveToShapefile(filename);
    }
}

// save txt
void YGIS::on_action_save_txt()
{
    QString shpFilePath = QFileDialog::getOpenFileName(this, tr("Open Shapefile"), "", tr("Shapefiles (*.shp)"));
    if (shpFilePath.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("No file selected."));
        return;
    }

    GDALAllRegister();
    GDALDataset* poDS = static_cast<GDALDataset*>(GDALOpenEx(shpFilePath.toStdString().c_str(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr));
    if (poDS == nullptr) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open SHP file."));
        return;
    }

    // ��ȡ��һͼ��
    OGRLayer* poLayer = poDS->GetLayer(0);
    if (poLayer == nullptr) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to get the first layer."));
        GDALClose(poDS);
        return;
    }

    // ʹ��QFileDialogѡ�񱣴�TXT�ļ���λ��
    QString txtFilePath = QFileDialog::getSaveFileName(this, tr("Save TXT File"), "", tr("Text Files (*.txt)"));
    if (txtFilePath.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("No file selected."));
        GDALClose(poDS);
        return;
    }

    // �����TXT�ļ�
    QFile outFile(txtFilePath);
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open output file."));
        GDALClose(poDS);
        return;
    }

    QTextStream outStream(&outFile);

    // д���ֶ�����TXT�ļ�
    OGRFeatureDefn* poFDefn = poLayer->GetLayerDefn();
    int iFieldCount = poFDefn->GetFieldCount();
    for (int i = 0; i < iFieldCount; i++) {
        OGRFieldDefn* poFieldDefn = poFDefn->GetFieldDefn(i);
        outStream << poFieldDefn->GetNameRef();
        if (i < iFieldCount - 1)
            outStream << ", ";
    }
    outStream << "\n";

    // ��������Ҫ�ز�����д��TXT�ļ�
    OGRFeature* poFeature;
    poLayer->ResetReading();
    while ((poFeature = poLayer->GetNextFeature()) != nullptr) {
        // д��ÿ���ֶε�ֵ
        for (int i = 0; i < iFieldCount; i++) {
            if (poFeature->IsFieldSet(i)) {
                outStream << poFeature->GetFieldAsString(i);
            }
            if (i < iFieldCount - 1)
                outStream << ", ";
        }
        outStream << "\n";

        // �ͷ�Ҫ��
        OGRFeature::DestroyFeature(poFeature);
    }

    // �ر��ļ���GDAL���ݼ�
    outFile.close();
    GDALClose(poDS);
}

void YGIS::saveToShapefile(const QString& filename)
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Shapefile"), "", tr("Shapefile (*.shp)"));
    if (fileName.isEmpty())
        return;

    GDALAllRegister();
    GDALDriver* poDriver = GetGDALDriverManager()->GetDriverByName("ESRI Shapefile");
    if (poDriver == nullptr)
    {
        QMessageBox::critical(this, tr("Error"), tr("Shapefile driver not available."));
        return;
    }

    GDALDataset* poDS = poDriver->Create(fileName.toUtf8().constData(), 0, 0, 0, GDT_Unknown, nullptr);
    if (poDS == nullptr)
    {
        QMessageBox::critical(this, tr("Error"), tr("Failed to create shapefile."));
        return;
    }

    OGRLayer* poLayer = poDS->CreateLayer("layer", nullptr, wkbLineString, nullptr);
    if (poLayer == nullptr)
    {
        QMessageBox::critical(this, tr("Error"), tr("Failed to create layer."));
        GDALClose(poDS);
        return;
    }

    OGRFieldDefn oFieldX("X", OFTReal);
    OGRFieldDefn oFieldY("Y", OFTReal);
    poLayer->CreateField(&oFieldX);
    poLayer->CreateField(&oFieldY);

    OGRLineString line;
    for (const QPointF& point : points)
    {
        line.addPoint(point.x(), point.y());

        OGRFeature* poFeature = OGRFeature::CreateFeature(poLayer->GetLayerDefn());
        poFeature->SetField("X", point.x());
        poFeature->SetField("Y", point.y());
        poFeature->SetGeometry(&line);
        if (poLayer->CreateFeature(poFeature) != OGRERR_NONE)
        {
            QMessageBox::critical(this, tr("Error"), tr("Failed to create feature."));
            OGRFeature::DestroyFeature(poFeature);
            GDALClose(poDS);
            return;
        }
        OGRFeature::DestroyFeature(poFeature);
    }

    GDALClose(poDS);
    QMessageBox::information(this, tr("Success"), tr("Shapefile saved successfully."));
}

void YGIS::on_item_double_clicked(QTreeWidgetItem* item, int column)
{
    if (item && item->text(column) == "Buffer Calculation") {
        on_actionbuffer_triggered(); 
    }
}

void YGIS::on_actionbuffer_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Vector"), "", "*.shp");
    QByteArray ba = filename.toLocal8Bit();
    const char* p = ba.data();

    int r = 10;
    int radius = QInputDialog::getInt(NULL, "Input Dialog", "Please input the buffer radius", QLineEdit::Normal, r);

    QString filename1 = QFileDialog::getSaveFileName(this, tr("Save As"), "", tr("*.shp"));
    if (filename1 == "") return;
    QByteArray ba1 = filename1.toLocal8Bit();
    const char* pszVectorFile = ba1.data();

    GDALAllRegister();
    GDALDataset* DS1 = (GDALDataset*)GDALOpenEx(p, GDAL_OF_VECTOR, NULL, NULL, NULL);
    OGRLayer* poLayer;
    poLayer = DS1->GetLayer(0); //��ȡ��
    OGRFeature* poFeature;
    //ע������
    const char* pszDriverName = "ESRI Shapefile";
    GDALDriver* poDriver;
    poDriver = GetGDALDriverManager()->GetDriverByName(pszDriverName);

    GDALDataset* DS2 = poDriver->Create(pszVectorFile, 0, 0, 0, GDT_Unknown, NULL); //����shp�ļ�

    OGRLayer* newLayer = DS2->CreateLayer("NewLayer");

    while ((poFeature = poLayer->GetNextFeature()) != NULL)  //��ͼ���л�ȡҪ��
    {
        OGRGeometry* poGeometry = poFeature->GetGeometryRef();   //��Ҫ���л�ȡ����ͼ��
        OGRGeometry* newGeometry = poGeometry->OGRGeometry::Buffer(radius);//���ɻ�����
        OGRFeatureDefn* poDefn = newLayer->GetLayerDefn();
        OGRFeature* newFeature = OGRFeature::CreateFeature(poDefn);
        newFeature->SetGeometry(newGeometry);
        newLayer->CreateFeature(newFeature);
        OGRFeature::DestroyFeature(newFeature);
    }
    GDALClose(DS1);
    GDALClose(DS2);
}

void YGIS::on_TIN_double_clicked(QTreeWidgetItem* item, int column)
{
    if (item && item->text(column) == "Start TIN") {
        on_actionrandom_triggered();
    }
}

void YGIS::on_actionrandom_triggered()
{

    n = 100;
    int num = QInputDialog::getInt(NULL, "Input Dialog", "Please input the number of points", QLineEdit::Normal, n);
    QString filename1 = QFileDialog::getSaveFileName(this, tr("Save As"), "", tr("*.shp"));
    // ���� QGraphicsView �� QGraphicsScene
    ui.graphicsView = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    ui.graphicsView->setScene(scene);
    // ����Դ�ļ��м���ͼƬ
    QPixmap pixmap(":/YGIS/res/TIN.png");
    if (pixmap.isNull()) {
        qWarning("ͼƬ����ʧ�ܡ�");
        return;
    }
    // ���� QGraphicsPixmapItem ��������ӵ�������
    QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap);
    scene->addItem(pixmapItem);
    // ʹͼƬ��Ӧ��ͼ�����ֱ���
    ui.graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio);

    // ������� QMainWindow �У�ʹ�� setCentralWidget �������ò���
    setCentralWidget(ui.graphicsView);

}

void YGIS::on_Count_double_clicked(QTreeWidgetItem* item, int column)
{
    if (item && item->text(column) == "Count") {
        on_Count_triggered();
    }
}

void YGIS::on_Count_triggered()
{
    if (poDS == nullptr) {
        QMessageBox::warning(this, tr("Count Features"), tr("No shapefile loaded."), QMessageBox::Ok);
        return;
    }

    OGRLayer* poLayer = poDS->GetLayer(0);
    if (poLayer == nullptr) {
        QMessageBox::warning(this, tr("Count Features"), tr("Failed to get layer."), QMessageBox::Ok);
        return;
    }

    // ͳ�Ƹ���ʸ��Ҫ������
    int pointCount = 0;
    int lineCount = 0;
    int polygonCount = 0;

    OGRFeature* poFeature;
    poLayer->ResetReading();
    while ((poFeature = poLayer->GetNextFeature()) != nullptr)
    {
        OGRGeometry* poGeometry = poFeature->GetGeometryRef();
        if (poGeometry != nullptr)
        {
            switch (wkbFlatten(poGeometry->getGeometryType()))
            {
            case wkbPoint:
                pointCount++;
                break;
            case wkbLineString:
                lineCount++;
                break;
            case wkbPolygon:
                polygonCount++;
                break;
            default:
                break;
            }
        }
        OGRFeature::DestroyFeature(poFeature);
    }

    // ��ʾͳ�ƽ��
    QString message = QString("Point Features: %1\nLine Features: %2\nPolygon Features: %3")
        .arg(pointCount).arg(lineCount).arg(polygonCount);
    QMessageBox::information(this, tr("Feature Count"), message, QMessageBox::Ok);
}



void YGIS::on_Area_double_clicked(QTreeWidgetItem* item, int column)
{
    if (item && item->text(column) == "Area") {
        on_Area_triggered();
    }
}

void YGIS::on_Area_triggered()
{
    if (poDS == nullptr) {
        QMessageBox::warning(this, tr("Calculate Area"), tr("No shapefile loaded."), QMessageBox::Ok);
        return;
    }

    OGRLayer* poLayer = poDS->GetLayer(0);
    if (poLayer == nullptr) {
        QMessageBox::warning(this, tr("Calculate Area"), tr("Failed to get layer."), QMessageBox::Ok);
        return;
    }

    double totalArea = 0.0;

    OGRFeature* poFeature;
    poLayer->ResetReading();
    while ((poFeature = poLayer->GetNextFeature()) != nullptr)
    {
        OGRGeometry* poGeometry = poFeature->GetGeometryRef();
        if (poGeometry != nullptr && wkbFlatten(poGeometry->getGeometryType()) == wkbPolygon)
        {
            OGRPolygon* poPolygon = (OGRPolygon*)poGeometry;
            totalArea += poPolygon->get_Area();
        }
        OGRFeature::DestroyFeature(poFeature);
    }

    // ��ʾ��������
    QString message = QString("Total Area of Polygons: %1 square units").arg(totalArea);
    QMessageBox::information(this, tr("Total Area"), message, QMessageBox::Ok);
}


void YGIS::on_Paint_double_clicked(QTreeWidgetItem* item, int column)
{
    if (item && item->text(column) == "Paint") {
        mainwindow->show();
    }
}


void YGIS::openTIF()
{
    // ʹ��QFileDialog���ļ�ѡ��Ի���
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Open file", QDir::homePath(), "Tif File (*.tif)");

    if (!fileName.isEmpty()) {
        //auto command = new LoadTiffileCommand(this, fileName);
        //undoStack->push(command);
        loadTifFile(fileName);
    }
    if (fileName.isEmpty())
        return;

    //loadTifFile(sfileName);
    //Logger::info("��tif�ļ��ɹ�");
}


void YGIS::loadTifFile(const QString& fileName)
{
    // ��դ���ļ�
    if (fileName.isEmpty()) {
        std::cout << "wrong" << std::endl;
        return;
    }

    // ע��GDAL����
    GDALAllRegister();

    // ��GDAL���ݼ�
    GDALDataset* poDataset = (GDALDataset*)GDALOpenEx(fileName.toStdString().c_str(), GDAL_OF_RASTER, NULL, NULL, NULL);
    if (poDataset == NULL) {
        std::cout << "wrong: cannot open " << fileName.toStdString() << std::endl;
        return;
    }

    // ��ȡ����������դ��ߴ�
    int bandCount = poDataset->GetRasterCount();
    int xSize = poDataset->GetRasterXSize();
    int ySize = poDataset->GetRasterYSize();

    // ����һ��QTextEditС����������ʾ��Ϣ
    QTextEdit* infoTextEdit = new QTextEdit;
    infoTextEdit->setReadOnly(true); // ����Ϊֻ��

    // ��ʾ���������ݼ���Ϣ
    infoTextEdit->append(QString("Dimensions: %1 x %2, Bands: %3").arg(xSize).arg(ySize).arg(bandCount));

    // ��ȡ��������
    std::vector<std::vector<uint8_t>> bands(bandCount);
    for (int i = 0; i < bandCount; ++i) {
        GDALRasterBand* poBand = poDataset->GetRasterBand(i + 1);
        std::vector<uint8_t> bandData(xSize * ySize);
        poBand->RasterIO(GF_Read, 0, 0, xSize, ySize, bandData.data(), xSize, ySize, GDT_Byte, 0, 0);
        bands[i] = std::move(bandData);
    }

    // �������ɫͼ��
    QImage image(xSize, ySize, QImage::Format_RGB888);
    for (int y = 0; y < ySize; ++y) {
        for (int x = 0; x < xSize; ++x) {
            int index = y * xSize + x;
            QRgb color = qRgb(bands[0][index], bands[1][index], bands[2][index]); // Red, Green, Blue bands
            image.setPixel(x, y, color);
        }
    }

    // ��ͼƬ����Ϊͼ���������
    pixmapItem->setPixmap(QPixmap::fromImage(image));
    view->fitInView(pixmapItem, Qt::KeepAspectRatio);

    // �������ι���
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    view->setResizeAnchor(QGraphicsView::AnchorUnderMouse);

    // ���� TreeWidgetItem������ӵ� treeWidget_Layer
    QTreeWidgetItem* layerItem = new QTreeWidgetItem(ui.treeWidget_Layer);
    layerItem->setText(0, QFileInfo(fileName).fileName());
    layerItem->setCheckState(0, Qt::Checked);  // Ĭ�Ϲ�ѡ

    // ����һ�� QGraphicsItemGroup ����ʾͼ�㣬�������� TreeWidgetItem ����
    QGraphicsItemGroup* layerGroup = new QGraphicsItemGroup;
    layerGroup->addToGroup(pixmapItem); // �� pixmapItem ��ӵ�����
    ui.treeWidget_Layer->addTopLevelItem(layerItem);
    layerItem->setData(0, Qt::UserRole, QVariant::fromValue<void*>(layerGroup));

    // ��ͼ������ӵ�������
    scene->addItem(layerGroup);

    // ���� treeWidget_Layer �� itemChanged �źŵ� onLayerItemChanged ��
    connect(ui.treeWidget_Layer, &QTreeWidget::itemChanged, this, &YGIS::onLayerItemChanged);

    // �ر����ݼ�
    GDALClose(poDataset);
}


void YGIS::disOpenTIF()
{

}

void YGIS::on_mask_double_clicked(QTreeWidgetItem* item, int column)
{
    if (item && item->text(column) == "Histogram Display") {
        on_mask_triggered();
    }
}

void YGIS::on_mask_triggered()
{
    //�Ҷ�ֱ��ͼ���
    // ʹ��QFileDialog���ļ�ѡ��Ի���
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Open File", QDir::homePath(), "Tif File (*.tif)");
    if (fileName.isEmpty()) {
        std::cout << "No file selected" << std::endl;
        return;
    }

    // ע��GDAL����
    GDALAllRegister();

    // ��GDAL���ݼ�
    GDALDataset* poDataset = (GDALDataset*)GDALOpenEx(fileName.toStdString().c_str(), GDAL_OF_RASTER, NULL, NULL, NULL);
    if (poDataset == NULL) {
        std::cout << "Cannot open file: " << fileName.toStdString() << std::endl;
        return;
    }

    // ��ȡ RGB ����
    GDALRasterBand* poRedBand = poDataset->GetRasterBand(1);
    GDALRasterBand* poGreenBand = poDataset->GetRasterBand(2);
    GDALRasterBand* poBlueBand = poDataset->GetRasterBand(3);

    if (poRedBand == nullptr || poGreenBand == nullptr || poBlueBand == nullptr) {
        std::cerr << "Failed to get RGB bands." << std::endl;
        GDALClose(poDataset);
        return;
    }

    // ��ȡդ�����ݵĳߴ�
    int nXSize = poRedBand->GetXSize();
    int nYSize = poRedBand->GetYSize();

    // ��ȡ RGB ��������
    std::vector<unsigned char> redBuffer(nXSize * nYSize);
    std::vector<unsigned char> greenBuffer(nXSize * nYSize);
    std::vector<unsigned char> blueBuffer(nXSize * nYSize);

    poRedBand->RasterIO(GF_Read, 0, 0, nXSize, nYSize, redBuffer.data(), nXSize, nYSize, GDT_Byte, 0, 0);
    poGreenBand->RasterIO(GF_Read, 0, 0, nXSize, nYSize, greenBuffer.data(), nXSize, nYSize, GDT_Byte, 0, 0);
    poBlueBand->RasterIO(GF_Read, 0, 0, nXSize, nYSize, blueBuffer.data(), nXSize, nYSize, GDT_Byte, 0, 0);

    // ת��Ϊ�Ҷ�ͼ��
    std::vector<unsigned char> grayBuffer(nXSize * nYSize);
    for (int i = 0; i < nXSize * nYSize; ++i) {
        grayBuffer[i] = static_cast<unsigned char>(
            0.299 * redBuffer[i] +
            0.587 * greenBuffer[i] +
            0.114 * blueBuffer[i]
            );
    }

    // ����Ҷ�ֱ��ͼ
    std::vector<int> histogram(256, 0);
    for (const auto& value : grayBuffer) {
        histogram[value]++;
    }

    // ����ֱ��ͼ�����ֵ
    int maxCount = *std::max_element(histogram.begin(), histogram.end());

    // �����Ҷ�ֱ��ͼͼ��
    const int width = 560;
    const int height = 400;
    QImage histogramImage(width, height, QImage::Format_Grayscale8);
    histogramImage.fill(Qt::white);

    QPainter painter(&histogramImage);
    painter.setPen(Qt::black);

    // ����ֱ��ͼ
    int barWidth = 2; // ���ӵĿ��
    for (int i = 0; i < 256; ++i) {
        int x = i * (barWidth + 1); // ��Ӽ��
        int barHeight = static_cast<int>(static_cast<float>(histogram[i]) / maxCount * height);
        painter.drawLine(x, height - barHeight, x, height);
    }


    // ����ֱ��ͼΪ PNG �ļ�
    QString saveFileName = QFileDialog::getSaveFileName(nullptr, "Save File", QDir::homePath() + "/histogram.png", "PNG File (*.png)");
    if (!saveFileName.isEmpty()) {
        histogramImage.save(saveFileName);
    }

    // ��ʾͼ���� UI �е����Ŀؼ���
    QWidget* centralWidget = this->centralWidget();
    QLabel* imageLabel = new QLabel(centralWidget);
    imageLabel->setPixmap(QPixmap::fromImage(histogramImage));
    imageLabel->setScaledContents(true);

    // ���ò���
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->addWidget(imageLabel);
    centralWidget->setLayout(layout);

    // �ر����ݼ�
    GDALClose(poDataset);
}

void YGIS::on_masks_double_clicked(QTreeWidgetItem* item, int column)
{
    if (item && item->text(column) == "Histogram Equalization") {
        on_masks_triggered();
    }
}

void YGIS::on_masks_triggered()
{
    // ʹ��QFileDialog���ļ�ѡ��Ի���
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Open File", QDir::homePath(), "Tif File (*.tif)");
    if (fileName.isEmpty()) {
        std::cout << "No file selected" << std::endl;
        return;
    }

    // ע��GDAL����
    GDALAllRegister();

    // ��GDAL���ݼ�
    GDALDataset* poDataset = (GDALDataset*)GDALOpenEx(fileName.toStdString().c_str(), GDAL_OF_RASTER, NULL, NULL, NULL);
    if (poDataset == NULL) {
        std::cout << "Cannot open file: " << fileName.toStdString() << std::endl;
        return;
    }

    // ��ȡ RGB ����
    GDALRasterBand* poRedBand = poDataset->GetRasterBand(1);
    GDALRasterBand* poGreenBand = poDataset->GetRasterBand(2);
    GDALRasterBand* poBlueBand = poDataset->GetRasterBand(3);

    if (poRedBand == nullptr || poGreenBand == nullptr || poBlueBand == nullptr) {
        std::cerr << "Failed to get RGB bands." << std::endl;
        GDALClose(poDataset);
        return;
    }

    // ��ȡդ�����ݵĳߴ�
    int nXSize = poRedBand->GetXSize();
    int nYSize = poRedBand->GetYSize();

    // ��ȡ RGB ��������
    std::vector<unsigned char> redBuffer(nXSize * nYSize);
    std::vector<unsigned char> greenBuffer(nXSize * nYSize);
    std::vector<unsigned char> blueBuffer(nXSize * nYSize);

    poRedBand->RasterIO(GF_Read, 0, 0, nXSize, nYSize, redBuffer.data(), nXSize, nYSize, GDT_Byte, 0, 0);
    poGreenBand->RasterIO(GF_Read, 0, 0, nXSize, nYSize, greenBuffer.data(), nXSize, nYSize, GDT_Byte, 0, 0);
    poBlueBand->RasterIO(GF_Read, 0, 0, nXSize, nYSize, blueBuffer.data(), nXSize, nYSize, GDT_Byte, 0, 0);

    // ת��Ϊ�Ҷ�ͼ��
    std::vector<unsigned char> grayBuffer(nXSize * nYSize);
    for (int i = 0; i < nXSize * nYSize; ++i) {
        grayBuffer[i] = static_cast<unsigned char>(
            0.299 * redBuffer[i] +
            0.587 * greenBuffer[i] +
            0.114 * blueBuffer[i]
            );
    }

    // ����Ҷ�ֱ��ͼ
    std::vector<int> histogram(256, 0);
    for (const auto& value : grayBuffer) {
        histogram[value]++;
    }

    // �����ۼƷֲ����� (CDF) ������ֱ��ͼ���⻯
    std::vector<int> cdf(256, 0);
    cdf[0] = histogram[0];
    for (int i = 1; i < 256; ++i) {
        cdf[i] = cdf[i - 1] + histogram[i];
    }

    int totalPixels = nXSize * nYSize;
    std::vector<unsigned char> equalizedGrayBuffer(nXSize * nYSize);
    for (int i = 0; i < totalPixels; ++i) {
        equalizedGrayBuffer[i] = static_cast<unsigned char>(255.0 * cdf[grayBuffer[i]] / totalPixels);
    }

    // ������⻯���ֱ��ͼ
    std::vector<int> equalizedHistogram(256, 0);
    for (const auto& value : equalizedGrayBuffer) {
        equalizedHistogram[value]++;
    }

    // ����ֱ��ͼ�����ֵ
    int maxCount = *std::max_element(equalizedHistogram.begin(), equalizedHistogram.end());

    // �������⻯���ֱ��ͼͼ��
    const int width = 700;
    const int height = 400;
    QImage histogramImage(width, height, QImage::Format_Grayscale8);
    histogramImage.fill(Qt::white);

    QPainter painter(&histogramImage);
    painter.setPen(Qt::black);

    // ���ƾ��⻯��ǿ��ʾֱ��ͼ
    int barWidth = 2; // ���ӵĿ��
    for (int i = 0; i < 256; ++i) {
        int x = i * (barWidth + 1); // ��Ӽ��
        int barHeight = static_cast<int>(static_cast<float>(equalizedHistogram[i]) / maxCount * height);
        painter.drawLine(x, height - barHeight, x, height);
    }

    // ����ֱ��ͼΪ PNG �ļ�
    QString saveFileName = QFileDialog::getSaveFileName(nullptr, "Save File", QDir::homePath() + "/equalized_histogram.png", "PNG File (*.png)");
    if (!saveFileName.isEmpty()) {
        histogramImage.save(saveFileName);
    }

    // ��ʾͼ���� UI �е����Ŀؼ���
    QWidget* centralWidget = this->centralWidget();
    QLabel* imageLabel = new QLabel(centralWidget);
    imageLabel->setPixmap(QPixmap::fromImage(histogramImage));
    imageLabel->setScaledContents(true);

    // ���ò���
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->addWidget(imageLabel);
    centralWidget->setLayout(layout);

    // �ͷ���Դ
    GDALClose(poDataset);
}

void YGIS::on_statistics_double_clicked(QTreeWidgetItem* item, int column)
{
    if (item && item->text(column) == "Neighborhood Statistics") {
        on_statistics_triggered();
    }
}

void YGIS::on_statistics_triggered()
{
    //����ͳ��
    // ʹ��QFileDialog���ļ�ѡ��Ի���
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Open File", QDir::homePath(), "Tif File (*.tif)");
    if (fileName.isEmpty()) {
        std::cout << "No file selected" << std::endl;
        return;
    }

    // ��ʼ��GDAL
    GDALAllRegister();

    // ��TIF�ļ�
    GDALDataset* dataset = (GDALDataset*)GDALOpen(fileName.toStdString().c_str(), GA_ReadOnly);
    if (dataset == nullptr) {
        QMessageBox::critical(nullptr, "Error", "Failed to open the file.");
        return;
    }

    // ��ȡդ������
    GDALRasterBand* band = dataset->GetRasterBand(1); // ��������ֻ�����һ������
    if (band == nullptr) {
        QMessageBox::critical(nullptr, "Error", "Failed to get raster band.");
        GDALClose(dataset);
        return;
    }

    // ��ȡդ�����ݵĳߴ�
    int xSize = band->GetXSize();
    int ySize = band->GetYSize();
    std::vector<float> data(xSize * ySize);

    // ��ȡդ������
    band->RasterIO(GF_Read, 0, 0, xSize, ySize, data.data(), xSize, ySize, GDT_Float32, 0, 0);

    // �����ֵ�����ֵ����Сֵ
    float minValue = std::numeric_limits<float>::max();
    float maxValue = std::numeric_limits<float>::lowest();
    double sum = 0;
    int count = 0;

    for (float value : data) {
        if (value != band->GetNoDataValue()) { // ����NoDataֵ
            minValue = std::min(minValue, value);
            maxValue = std::max(maxValue, value);
            sum += value;
            count++;
        }
    }

    double meanValue = (count > 0) ? (sum / count) : 0;

    // ������Ϣ����ʾ���
    QString resultText = QString("mean: %1\nmax: %2\nmin: %3")
        .arg(meanValue)
        .arg(maxValue)
        .arg(minValue);

    CustomMessageBox msgBox("Spatial Analyst", resultText);
    msgBox.exec();

    // �ر����ݼ�
    GDALClose(dataset);
}

#endif // !YGIS_H
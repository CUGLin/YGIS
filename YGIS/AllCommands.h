//// AllCommands.h
//// ���������࣬ÿ���඼����һ�������Ĳ�����ͨ���̳�����QUndoCommand�෽����г�����������
//#ifndef ALLCOMMANDS_H
//#define ALLCOMMANDS_H
//
//#include <QUndoCommand>
//#include <QString>
////#include <gdal/ogrsf_frmts.h>
////#include <gdal/gdal_priv.h>
//
//#include "YGIS.h"
////#include "ogrsf_frmts.h"
//
//// ǰ������������ѭ������
//class YGIS;
////class MyReceiver;
//
//class LoadShapefileCommand : public QUndoCommand {
//public:
//    LoadShapefileCommand(YGIS* prYgisReceiver, const QString& sFilePath)
//        : prYgisReceiver(prYgisReceiver), sFilePath(sFilePath) {}
//
//    void redo() {
//        prYgisReceiver->loadShapefile(sFilePath);
//    }
//    void undo() {
//        prYgisReceiver->disLoadShapefile();
//    }
//
//
//private:
//    //MyReceiver* prReceiver;
//    YGIS* prYgisReceiver;
//    QString sFilePath;
//    //GDALDataset* poDS;
//};
//
//#endif // !ALLCOMMANDS_H




//#ifndef ALLCOMMANDS_H
//#define ALLCOMMANDS_H
//
//#include <QUndoCommand>
//#include <QString>
//#include "YGIS.h"
//
//class YGIS;
//
//class LoadShapefileCommand : public QUndoCommand {
//public:
//    LoadShapefileCommand(YGIS* prYgisReceiver, const QString& sFilePath)
//        : prYgisReceiver(prYgisReceiver), sFilePath(sFilePath) {}
//
//    void redo() {
//        prYgisReceiver->loadShapefile(sFilePath);
//    }
//    void undo() {
//        prYgisReceiver->disLoadShapefile();
//    }
//
//private:
//    YGIS* prYgisReceiver;
//    QString sFilePath;
//};
//
//#endif // !ALLCOMMANDS_H
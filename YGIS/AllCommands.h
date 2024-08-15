//// AllCommands.h
//// 各项命令类，每个类都代表一个单独的操作，通过继承现有QUndoCommand类方便进行撤回重做操作
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
//// 前向声明，避免循环依赖
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
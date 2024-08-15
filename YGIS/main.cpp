#include "YGIS.h"
#include <QtWidgets/QApplication>
#include "MyLogger/MyLogger.h"
#include <qicon.h>

int main(int argc, char* argv[])
{
    Logger::info("主函数调用成功");

    QApplication a(argc, argv);
    YGIS w;
    w.show();

    return a.exec();

    YGIS mainWindow;
    // 设置窗口图标
    QIcon icon(":/YGIS/res/YGIS.ico");  // 使用资源文件
    mainWindow.setWindowIcon(icon);

}

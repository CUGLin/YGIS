#include "YGIS.h"
#include <QtWidgets/QApplication>
#include "MyLogger/MyLogger.h"
#include <qicon.h>

int main(int argc, char* argv[])
{
    Logger::info("���������óɹ�");

    QApplication a(argc, argv);
    YGIS w;
    w.show();

    return a.exec();

    YGIS mainWindow;
    // ���ô���ͼ��
    QIcon icon(":/YGIS/res/YGIS.ico");  // ʹ����Դ�ļ�
    mainWindow.setWindowIcon(icon);

}

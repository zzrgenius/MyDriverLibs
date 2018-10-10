#include "changebinfile.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChangeBinFile w;
    w.setWindowTitle("信多达OTA文件转换");
    w.show();

    return a.exec();
}

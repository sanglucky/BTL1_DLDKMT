#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("SERIAL PORT COMMUNICATION GUI");
    w.setWindowIcon(QIcon("E:\\Năm 3\\Photo\\Logo_BK.png"));
    w.show();
    return a.exec();
}

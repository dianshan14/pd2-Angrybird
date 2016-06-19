#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Angry Bird");
    w.setWindowIcon(QIcon(":/image/5000.png"));
    w.setFixedHeight(720);
    w.setFixedWidth(1280);
    w.show();

    return a.exec();
}

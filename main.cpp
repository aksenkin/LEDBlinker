#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile File(":styleSheet.qss");
     File.open(QFile::ReadOnly);
     QString StyleSheet = QLatin1String(File.readAll());

     qApp->setStyleSheet(StyleSheet);

    MainWindow w;



    w.move(QApplication::desktop()->screen()->rect().center()-w.rect().center());
    w.show();

    return a.exec();
}

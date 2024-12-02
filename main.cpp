#include "mainwindow.h"
#include "SlidePage/slidepage.h"
#include "Reader/reader.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/style.qss");
    if (file.exists()) {
        file.open(QFile::ReadOnly);
        QString stylesheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(stylesheet);
        file.close();
    }
//    MainWindow w;
    Reader w;
    w.show();
    return a.exec();
}

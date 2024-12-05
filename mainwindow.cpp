#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    selectPage = new SelectPage(this);
    selectPage->show();
    connect(selectPage, SIGNAL(showReader(char*)), this, SLOT(showReader(char*)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::showReader(char* ch)
{
    selectPage->hide();
    reader = new Reader(this, ch);
    reader->setAttribute(Qt::WA_DeleteOnClose);
    reader->show();
    connect(reader, SIGNAL(backToSelectPage()), this, SLOT(backToSelectPage()));
}

void MainWindow::backToSelectPage()
{
    reader->close();
    selectPage->show();
}


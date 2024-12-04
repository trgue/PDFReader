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
    reader = new Reader(this, ch);
    reader->show();
    connect(reader, SIGNAL(backToSelectPage()), this, SLOT(backToSelectPage()));
}

void MainWindow::backToSelectPage()
{
//    selectPage = new SelectPage(this);
    selectPage->show();
    connect(selectPage, SIGNAL(showReader(char*)), this, SLOT(showReader(char*)));
}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "SelectPage/selectpage.h"
#include "Reader/reader.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    SelectPage *selectPage;
    Reader *reader;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showReader(char*);
    void backToSelectPage();

};
#endif // MAINWINDOW_H

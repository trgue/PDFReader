#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QScroller>
#include <QPushButton>
#include <QImage>
#include <QIcon>
#include <QSize>
#include <QPixmap>
#include <QLabel>
#include <QPainter>
#include<QPaintEvent>
//#include <QGraphicsScene>
//#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "mupdf/pdf.h"
#include "mupdf/fitz.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    QWidget *widget;
    QWidget *buttonWidget;
    QWidget *textWidget;
    QListWidget *listWidget;
    QVBoxLayout *vBoxLayout;
    QHBoxLayout *hBoxLayout;
    QListWidgetItem *tmpItem;
    QLabel *pageLabel;
    QPainter *painter;
//    QGraphicsScene *scene;
//    QGraphicsProxyWidget *proxy;
    QPushButton *pushButton[2];

    fz_context *ctx;
    fz_document *doc;
    fz_pixmap *pix;
    fz_matrix ctm;
    float zoom, rotate;
    int page_count;

private:
    void multiPageShow();
    void buttonSet();
    void showPaint(int currentRow);
    void widgetSet();
    void paintEvent(QPaintEvent* event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void pushButton0_Clicked();
    void pushButton1_Clicked();
    void listWidgetRow_Changed(int currentRow);
};
#endif // MAINWINDOW_H

#ifndef READER_H
#define READER_H

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
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "SlidePage/slidepage.h"
#include "mupdf/pdf.h"
#include "mupdf/fitz.h"

class Reader : public QMainWindow
{
    Q_OBJECT
public:
    explicit Reader(QWidget *parent = nullptr, char* input = nullptr);
    ~Reader();

private:
    QWidget *widget;            // 主widget
    QWidget *buttonWidget;      // 翻页widget
    QWidget *textWidget;        // 页数widget
    QVBoxLayout *vBoxLayout;
    QHBoxLayout *hBoxLayout;
    QLabel *tmpLabel;           // 每一页的图像label
    QPainter *painter;
    QPushButton *pushButton[2];

    /* MuPDF */
    fz_context *ctx;
    fz_document *doc;
    fz_pixmap *pix;
    fz_matrix ctm;
    float zoom, rotate;
    int page_count;

    SlidePage *slidePage;       // 阅读页面

private:
    void multiPageShowBySlidePage();    // 阅读页面创建
    void buttonSet();                   // 按钮创建
    void showPaint(int currentRow);     // 画页数label
    void widgetSet();                   // 布局
    void paintEvent(QPaintEvent* event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void pushButton0_Clicked();
    void pushButton1_Clicked();
    void pdfWidgetRow_Changed(int currentRow);

signals:
    void backToSelectPage();

};

#endif // READER_H

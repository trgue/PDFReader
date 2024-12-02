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
    explicit Reader(QWidget *parent = nullptr);
    ~Reader();

private:
    QWidget *widget;            // 主widget
    QWidget *buttonWidget;      // 翻页widget
    QWidget *textWidget;        // 页数widget
    QWidget *pdfWidget;         // pdf图片widget
    QVBoxLayout *vBoxLayout;
    QHBoxLayout *hBoxLayout;
    QLabel *tmpLabel;
    QPainter *painter;
    QPushButton *pushButton[2];

    fz_context *ctx;
    fz_document *doc;
    fz_pixmap *pix;
    fz_matrix ctm;
    float zoom, rotate;
    int page_count;

    SlidePage *slidePage;

private:
    void multiPageShowBySlidePage();
    void buttonSet();
    void showPaint(int currentRow);
    void widgetSet();
    void paintEvent(QPaintEvent* event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void pushButton0_Clicked();
    void pushButton1_Clicked();
    void pdfWidgetRow_Changed(int currentRow);

};

#endif // READER_H

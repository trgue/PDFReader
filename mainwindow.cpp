#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(0, 0, 1024, 600);

    char *input = const_cast< char* >("1.pdf");
    hBoxLayout = new QHBoxLayout();
    widget = new QWidget();
    widget->setGeometry(0, 0, 1024, 600);
    widget->setObjectName("widget");

    textWidget = new QWidget();
    textWidget->setMinimumSize(100, 200);
    textWidget->setMaximumSize(100, 200);
    textWidget->installEventFilter(this);

    //100%缩放比
    zoom = 100;
    //旋转为0
    rotate = 90;

    /* 创建上下文 */
    ctx =  fz_new_context(NULL, NULL, FZ_STORE_DEFAULT);
    if (!ctx) {
        qDebug()<<stderr<<"cannot create mupdf context";
        return;
    }
    //注册文档控制
    fz_try(ctx)
            fz_register_document_handlers(ctx);
    fz_catch(ctx) {
        qDebug()<<stderr<<"cannot register document handlers:"<< fz_caught_message(ctx);
        fz_drop_context(ctx);
        return;
    }
    //打开文档
    fz_try(ctx)
        doc = fz_open_document(ctx, input);
    fz_catch(ctx)
    {
        qDebug()<<stderr<< "cannot open document:"<< fz_caught_message(ctx);
        fz_drop_context(ctx);
        return;
    }

    fz_try(ctx)
        page_count = fz_count_pages(ctx, doc);
    fz_catch(ctx)
    {
        qDebug()<<stderr<< "cannot count number of pages:"<< fz_caught_message(ctx);
        fz_drop_document(ctx, doc);
        fz_drop_context(ctx);
        return;
    }

    //计算缩放以及旋转
    fz_scale(&ctm, zoom / 100, zoom / 100);
    fz_pre_rotate(&ctm, rotate);

    buttonSet();

    connect(pushButton[0], SIGNAL(clicked()), this, SLOT(pushButton0_Clicked()));
    connect(pushButton[1], SIGNAL(clicked()), this, SLOT(pushButton1_Clicked()));

    multiPageShow();

    connect(listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(listWidgetRow_Changed(int)));

    fz_drop_document(ctx, doc);
    fz_drop_context(ctx);

    widget->setLayout(hBoxLayout);
    setCentralWidget(widget);

    listWidget->setCurrentRow(0);

    this->setFocus();
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    showPaint();

}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == textWidget && event->type() == QEvent::Paint)
    {
        showPaint(); //响应函数
    }
    return QWidget::eventFilter(watched,event);
}


void MainWindow::showPaint()
{
    painter = new QPainter(textWidget);
    QFont ft;
    ft.setPointSize(20);

    QPen pen(Qt::black);
    painter->setPen(pen);
    painter->setFont(ft);

    painter->translate(50, 50);
    painter->rotate(90);
    painter->drawText(0, 0, QString("1 / ") + QString::number(page_count));
    painter->end();
    vBoxLayout->addWidget(textWidget);

}

void MainWindow::listWidgetRow_Changed(int currentRow)
{
    if (currentRow >= 0) {
//        pageLabel->setText(QString::number(currentRow + 1) + QString(" / ") + QString::number(page_count));
    }
}

void MainWindow::pushButton0_Clicked()
{
    if (listWidget->currentRow() - 1 >= 0) {
        listWidget->setCurrentRow(listWidget->currentRow() - 1);
//        pageLabel->setText(QString::number(listWidget->currentRow() + 1) + QString(" / ") + QString::number(page_count));
    }
}

void MainWindow::pushButton1_Clicked()
{
    if (listWidget->currentRow() + 1 <= page_count - 1) {
        listWidget->setCurrentRow(listWidget->currentRow() + 1);
//        pageLabel->setText(QString::number(listWidget->currentRow() + 1) + QString(" / ") + QString::number(page_count));
    }
}

void MainWindow::buttonSet()
{
    vBoxLayout = new QVBoxLayout();
    buttonWidget = new QWidget();
    for (int i = 0; i < 2; i++) {
        pushButton[i] = new QPushButton();
        pushButton[i]->setMinimumSize(100, 100);
        if (i == 0) {
//            pushButton[i]->setText(QString("上一页"));
            pushButton[i]->setObjectName("btn_up");
        }
        else {
//            pushButton[i]->setText(QString("下一页"));
            pushButton[i]->setObjectName("btn_down");
        }
        vBoxLayout->addWidget(pushButton[i]);
    }
    buttonWidget->setLayout(vBoxLayout);
    hBoxLayout->addWidget(buttonWidget);
}

void MainWindow::multiPageShow()
{
    listWidget = new QListWidget();
    listWidget->setIconSize(QSize(900, 600));
    listWidget->setSpacing(10);
    listWidget->setResizeMode(QListView::Adjust);
    listWidget->setMovement(QListView::Static);
    listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setObjectName("listWidget");

    listWidget->setVerticalScrollMode(QListWidget::ScrollPerPixel);
    listWidget->setFrameShape(QListWidget::NoFrame);
    QScroller::grabGesture(listWidget, QScroller::LeftMouseButtonGesture);

    for (int i = 0; i < page_count; i++) {
        //渲染pixmap
        pix = fz_new_pixmap_from_page_number(ctx, doc, i, &ctm, fz_device_rgb(ctx), 0);

        unsigned char *samples = pix->samples;
        int width = fz_pixmap_width(ctx, pix);
        int height = fz_pixmap_height(ctx, pix);
        QImage image(samples, width, height,pix->stride,QImage::Format_RGB888);
        image = image.scaled(800, 600);

        tmpItem = new QListWidgetItem();
        tmpItem->setIcon(QIcon(QPixmap::fromImage(image)));
        tmpItem->setFlags(tmpItem->flags() & ~Qt::ItemIsSelectable);
        listWidget->addItem(tmpItem);

        fz_drop_pixmap(ctx, pix);
    }

    hBoxLayout->addWidget(listWidget);

}


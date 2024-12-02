#include "reader.h"
#include <QDebug>

Reader::Reader(QWidget *parent) : QMainWindow(parent)
{
    char *input = const_cast< char* >("1.pdf");
    hBoxLayout = new QHBoxLayout();
    hBoxLayout->setContentsMargins(0, 0, 0, 0);
    hBoxLayout->setSpacing(0);
    vBoxLayout = new QVBoxLayout();
    vBoxLayout->setContentsMargins(0, 0, 0, 0);
    vBoxLayout->setAlignment(Qt::AlignCenter);
    vBoxLayout->setSpacing(0);

    widget = new QWidget();
    widget->setMinimumSize(1024, 600);
    widget->setObjectName("widget");

    pdfWidget = new QWidget();
    pdfWidget->setMinimumSize(900, 600);
    pdfWidget->setWindowFlags(Qt::FramelessWindowHint);
    pdfWidget->setStyleSheet("background: transparent");

    textWidget = new QWidget();
    textWidget->setMinimumSize(100, 200);
    textWidget->setMaximumSize(100, 200);
    textWidget->installEventFilter(this);

    buttonWidget = new QWidget();

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

    multiPageShowBySlidePage();

    connect(slidePage, SIGNAL(currentPageIndexChanged(int)), this, SLOT(pdfWidgetRow_Changed(int)));

    fz_drop_document(ctx, doc);
    fz_drop_context(ctx);

    widgetSet();

    this->setFocus();
}


Reader::~Reader()
{
}


/* 设置各个widget */
void Reader::widgetSet()
{
    vBoxLayout->addWidget(pushButton[0]);
    vBoxLayout->addWidget(textWidget);
    vBoxLayout->addWidget(pushButton[1]);
    buttonWidget->setLayout(vBoxLayout);
    hBoxLayout->addWidget(buttonWidget);
    hBoxLayout->addWidget(pdfWidget);
    widget->setLayout(hBoxLayout);
    setCentralWidget(widget);
}


/* 在子控件画图，需要使用过滤器 */
void Reader::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    showPaint(slidePage->getCurrentPageIndex());
}

bool Reader::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == textWidget && event->type() == QEvent::Paint) {
        showPaint(slidePage->getCurrentPageIndex()); //响应函数
    }
    return QWidget::eventFilter(watched,event);
}

/* 画页数 */
void Reader::showPaint(int currentRow)
{
    QFont ft;
    ft.setPointSize(20);

    painter = new QPainter(textWidget);
    QPen pen(Qt::black);
    painter->setPen(pen);
    painter->setFont(ft);

    painter->translate(40, 55);
    painter->rotate(90);
    painter->drawText(0, 0, QString::number(currentRow + 1)
                      + QString(" / ")
                      + QString::number(slidePage->getPageCount()));
    painter->end();

}

void Reader::pdfWidgetRow_Changed(int currentRow)
{
    if (currentRow >= 0) {
        this->update();
    }
}

void Reader::pushButton0_Clicked()
{

}

void Reader::pushButton1_Clicked()
{

}

void Reader::buttonSet()
{
    for (int i = 0; i < 2; i++) {
        pushButton[i] = new QPushButton();
        pushButton[i]->setMinimumSize(100, 100);
        if (i == 0) {
            pushButton[i]->setObjectName("btn_up");
        }
        else {
            pushButton[i]->setObjectName("btn_down");
        }
    }

}

void Reader::multiPageShowBySlidePage()
{
    slidePage = new SlidePage(pdfWidget);
    for (int i = 0; i < page_count; i++) {
        //渲染pixmap
        pix = fz_new_pixmap_from_page_number(ctx, doc, i, &ctm, fz_device_rgb(ctx), 0);

        unsigned char *samples = pix->samples;
        int width = fz_pixmap_width(ctx, pix);
        int height = fz_pixmap_height(ctx, pix);
        QImage image(samples, width, height,pix->stride,QImage::Format_RGB888);
        image = image.scaled(900, 600);

        tmpLabel = new QLabel();
        tmpLabel->setMinimumSize(900, 600);
        tmpLabel->setPixmap(QPixmap::fromImage(image));
        slidePage->addPage(tmpLabel);

        fz_drop_pixmap(ctx, pix);
    }
}


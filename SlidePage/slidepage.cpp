#include "slidepage.h"
#include <QDebug>
#include <QPropertyAnimation>

SlidePage::SlidePage(QWidget *parent)
    : QWidget(parent)
    , pageIndex(0)
    , pageCount(0)
{
    this->setMinimumSize(900, 600);
//    this->setMaximumSize(900, 600);

    scrollArea = new QScrollArea(this);
    scrollArea->setAlignment(Qt::AlignCenter);

    mainWidget = new QWidget(this);
    mainWidget->setWindowFlags(Qt::FramelessWindowHint);

    scrollArea->setWidget(mainWidget);

    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("background: transparent");

    scroller = QScroller::scroller(scrollArea);
    QScroller::ScrollerGestureType gesture = QScroller::LeftMouseButtonGesture;
    scroller->grabGesture(scrollArea, gesture);

    /* 获取属性 */
    QScrollerProperties properties = scroller->scrollerProperties();

    /* 设置滑动的时间，值越大，时间越短 */
    properties.setScrollMetric(QScrollerProperties::SnapTime, 0.5);

    /* 设置滑动速度 */
    properties.setScrollMetric(QScrollerProperties::MinimumVelocity, 1);
    scroller->setScrollerProperties(properties);

    vBoxLayout = new QVBoxLayout();
    vBoxLayout->setContentsMargins(0, 0, 0, 0);
    vBoxLayout->setSpacing(0);

    mainWidget->setLayout(vBoxLayout);
    mainWidget->setStyleSheet("background: transparent");

    /* 定时器，用于判断用户是否是拖动屏幕，区分滑动，超过300ms表示拖动 */
    timer = new QTimer(this);

    connect(scrollArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(vScrollBarValueChanged(int)));
    connect(scroller, SIGNAL(stateChanged(QScroller::State)), this, SLOT(onStateChanged(QScroller::State)));
    connect(this, SIGNAL(currentPageIndexChanged(int)), this, SLOT(onCurrentPageIndexChanged(int)));
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerTimeOut()));
}

SlidePage::~SlidePage()
{
}

void SlidePage::widgetMake()
{

}

#if 1
void SlidePage::vScrollBarValueChanged(int)
{
    /* 滑动时判断当前页的下标 */
    pageIndex= scrollArea->verticalScrollBar()->value() / this->height();
    pageIndex = scrollArea->verticalScrollBar()->value() >= (pageIndex * this->height() + this->height() * 0.5) ? pageIndex + 1 : pageIndex;

}
#endif

void SlidePage::addPage(QWidget *w)
{
    /* 布局里添加页面 */
    vBoxLayout->addWidget(w);
    /* 页数加一 */
    pageCount++;
}

void SlidePage::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    scrollArea->resize(this->size());
    /* mainWidget需要比scrollArea小 */
    mainWidget->resize(this->width() - 4, this->height()  * pageCount);
    if (pageCount == 0)
        qDebug()<<"当前页面总数为0，请使用addPage()方法添加页面再使用！"<<endl;
    else
        onCurrentPageIndexChanged(0);
}

void SlidePage::onTimerTimeOut()
{
    /* 拖动标志位 */
    draggingFlag = true;
    timer->stop();
}

int SlidePage::getPageCount()
{
    return pageCount;
}

int SlidePage::getCurrentPageIndex()
{
    return pageIndex;
}

void SlidePage::onStateChanged(QScroller::State state)
{
    static int pressedValue = 0;
    static int releasedValue = 0;
    static int currentPageIndex = 0;

    /* 如果页面数为0，返回，不做任何操作 */
    if (pageCount == 0)
        return;

    /* 松开 */
    if (state == QScroller::Inactive) {
        /* 停止定时器，防止检测到界面是缓慢拖动状态 */
        timer->stop();
        /* 记录松开时的坐标 */
        releasedValue = QCursor::pos().y();

        /* 判断按下与松开的距离，首先先判断是不是拖动状态，如果是拖动状态，pageIndex不会变化 */
        if (!draggingFlag) {
            if (pressedValue - releasedValue >= 20 && currentPageIndex == pageIndex)
                pageIndex++;
            else if (pressedValue - releasedValue < -20 && currentPageIndex == pageIndex)
                pageIndex--;
            else if (pressedValue - releasedValue < 20 && pressedValue - releasedValue >= -20 && currentPageIndex == pageIndex){
                if (pressedValue > 400)
                    pageIndex++;
                else if (pressedValue < 200)
                    pageIndex--;
            }
        }

        /* 页面下标判断 */
        if (pageIndex == -1)
            pageIndex = 0;

        if (pageIndex >= pageCount)
            pageIndex = pageCount - 1;

        /* 动画 */
        QPropertyAnimation *animation = new QPropertyAnimation(scrollArea->verticalScrollBar(), "value");
        animation->setDuration(200);
        animation->setStartValue(scrollArea->verticalScrollBar()->value());
        animation->setEasingCurve(QEasingCurve::OutCurve);
        animation->setEndValue(pageIndex * this->height());
        animation->start(QAbstractAnimation::DeleteWhenStopped);

        if (currentPageIndex != pageIndex) {
            /* 发送当前页面的位置信号 */
            emit currentPageIndexChanged(pageIndex);
        }

        /* 重新赋值*/
        pressedValue = 0;
        releasedValue = 0;
        draggingFlag = false;
    }

    /* 按下 */
    if (state == QScroller::Pressed) {
        pressedValue = QCursor::pos().y();
        currentPageIndex = scrollArea->verticalScrollBar()->value() / this->height();
        /* 按下如果超过300ms，表示用户在拖动 */
        timer->start(300);
    }
}

void SlidePage::onCurrentPageIndexChanged(int index)
{

}

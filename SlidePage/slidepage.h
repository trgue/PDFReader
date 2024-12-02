#ifndef SLIDEPAGE_H
#define SLIDEPAGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QScroller>
#include <QScrollBar>
#include <QScrollArea>
#include <QTimer>
#include <QVBoxLayout>
#include <QLabel>

class SlidePage : public QWidget
{
    Q_OBJECT

public:
    SlidePage(QWidget *parent = nullptr);
    ~SlidePage();

    /* 添加新的页面 */
    void addPage(QWidget *);

    /* 页面总数 */
    int getPageCount();

    /* 当前页面 */
    int getCurrentPageIndex();

private:
    QScrollArea *scrollArea;    // 滚动区域
    QScroller *scroller;        // 滚屏对象
    QWidget *mainWidget;        // 主widget
//    QWidget *bottomWidget;      // 底部widget
    QTimer *timer;              // 定时器，用于检测用户是否在拖动屏幕
    QVBoxLayout *vBoxLayout;    // 垂直布局
    int pageIndex;              // 当前页数
    int pageCount;              // 总页数
    bool draggingFlag;          // 拖动标识位

    void widgetMake();
    void resizeEvent(QResizeEvent *event);

private slots:
    /* 垂直滚动条值变化 */
    void vScrollBarValueChanged(int);

    /* 滚动对象的状态 */
    void onStateChanged(QScroller::State);

    /* 定时器超时槽函数 */
    void onTimerTimeOut();

    /* 分页逗点槽函数 */
    void onCurrentPageIndexChanged(int);

signals:
    void currentPageIndexChanged(int);
};

#endif // SLIDEPAGE_H

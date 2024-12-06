#include "selectpage.h"
#include <QCoreApplication>
#include <QStringList>
#include <QDebug>
#include <Reader/reader.h>

SelectPage::SelectPage(QWidget *parent)
    : QMainWindow(parent)
{

    selectWidget = new QListWidget(this);
    selectWidget->setMinimumSize(1024, 600);

    /* 图标显示 */
    selectWidget->setViewMode(QListView::IconMode);
    /* 不可移动 */
    selectWidget->setMovement(QListView::Static);
    /* 间距 */
    selectWidget->setSpacing(10);
    /* icon大小 */
    selectWidget->setIconSize(QSize(100, 100));
    selectWidget->clear();

    transferButton = new QPushButton(this);

    mainWidget = new QWidget(this);
    mainWidget->setGeometry(0, 0, 1024, 600);
    hBoxLayout = new QHBoxLayout();
    hBoxLayout->addWidget(selectWidget);
    hBoxLayout->addWidget(transferButton);
    mainWidget->setLayout(hBoxLayout);
    setCentralWidget(mainWidget);



    scanPDF();

    connect(selectWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectWidgetCliked(QListWidgetItem*)));
    connect(transferButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));


}

void SelectPage::bleQuit()
{
    w->close();
}

void SelectPage::buttonClicked()
{
    w = new bluetoothtransfer(this);
    connect(w, SIGNAL(quit()), this, SLOT(bleQuit()));
    qDebug() << "button clicked " << endl;
    w->setWindowFlag(Qt::WindowStaysOnTopHint);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->setGeometry(312, 200, 400, 200);
    w->showMinimized();
}

void SelectPage::selectWidgetCliked(QListWidgetItem* item)
{

    QByteArray ba = ("./myPDF/" + item->text() + ".pdf").toUtf8();
    ch = new char;
    ch = ba.data();
    emit showReader(ch);
}


void SelectPage::scanPDF()
{
    QDir dir(QCoreApplication::applicationDirPath() + "/myPDF");
    QDir dirAbsolutePath(dir.absolutePath());
    if (dirAbsolutePath.exists()) {
        QStringList filter;
        filter << "*.pdf";
        QFileInfoList files = dirAbsolutePath.entryInfoList(filter, QDir::Files);


        for (int i = 0; i < files.count(); i++) {
            QString fileName = QString::fromUtf8(files.at(i).fileName().replace(".pdf", "").toUtf8().data());
//            qDebug() << fileName << endl;
            QImage image;
            image.load(":/icon/image/book");
            QListWidgetItem *tmpItem = new QListWidgetItem(QIcon(QPixmap::fromImage(image)), fileName);
            tmpItem->setSizeHint(QSize(100, 120));
            selectWidget->addItem(tmpItem);
        }
    }
}













#include "bluetoothtransfer.h"

bluetoothtransfer::bluetoothtransfer(QWidget *parent) : QMainWindow(parent)
{
//    this->setGeometry(0, 0, 1024, 600);
    waittingWidget = new QWidget(this);
    text = new QLabel(this);
    text->setText("this is text");
    waittingWidget->setMinimumSize(400, 200);
    quitButton = new QPushButton(this);
    quitButton->setMaximumSize(100, 100);

    vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->addWidget(text);
    vBoxLayout->addWidget(quitButton);
    waittingWidget->setLayout(vBoxLayout);
//    waittingWidget->setMaximumSize(400, 200);
    setCentralWidget(waittingWidget);

    connect(quitButton, SIGNAL(clicked()), this, SLOT(sendQuit()));
}

void bluetoothtransfer::sendQuit()
{
    emit quit();
}

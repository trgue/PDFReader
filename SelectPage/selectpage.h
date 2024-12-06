#ifndef SELECTPAGE_H
#define SELECTPAGE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDir>
#include <BlueToothTransfer/bluetoothtransfer.h>

//char* ch;

class SelectPage : public QMainWindow
{
    Q_OBJECT
public:
    char *ch;
public:
    explicit SelectPage(QWidget *parent = nullptr);


private:

    QListWidget *selectWidget;
    QWidget *mainWidget;
    QWidget *buttonWidget;
    QHBoxLayout *hBoxLayout;
    QPushButton *transferButton;
    bluetoothtransfer *w;



private:
    void scanPDF();

private slots:
    void selectWidgetCliked(QListWidgetItem*);
    void buttonClicked();
    void bleQuit();

signals:
    void showReader(char*);

};

#endif // SELECTPAGE_H

#ifndef BLUETOOTHTRANSFER_H
#define BLUETOOTHTRANSFER_H

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class bluetoothtransfer : public QMainWindow
{
    Q_OBJECT
public:
    explicit bluetoothtransfer(QWidget *parent = nullptr);

private:
    QWidget *waittingWidget;
    QLabel *text;
    QPushButton *quitButton;
    QVBoxLayout *vBoxLayout;

signals:
    void quit();

private slots:
    void sendQuit();

};

#endif // BLUETOOTHTRANSFER_H

#ifndef SELECTPAGE_H
#define SELECTPAGE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QDir>

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
    QHBoxLayout *hBoxLayout;


private:
    void scanPDF();

private slots:
    void selectWidgetCliked(QListWidgetItem*);

signals:
    void showReader(char*);

};

#endif // SELECTPAGE_H

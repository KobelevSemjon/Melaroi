#ifndef WIDGET_H
#define WIDGET_H

#include <QDebug>
#include <QWidget>
#include <QDesktopWidget>
#include <content.h>

#include <smatrix.h>
#include <sprocessing.h>
#include <ssegmentationmap.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void Open();
    void Load(int);

private:
    Ui::Widget *ui;
    Content folder;
};

#endif // WIDGET_H

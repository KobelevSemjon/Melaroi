#ifndef WIDGET_H
#define WIDGET_H

#include <QDebug>
#include <QWidget>
#include <QDesktopWidget>
#include <QString>
#include <QTime>
#include <content.h>

#include <SLib/classifying.h>
#include <SLib/components.h>
#include <SLib/core.h>
#include <SLib/features.h>
#include <SLib/processing.h>

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
    void GenerateTable();
    void GenerateAnswers();
    void GenerateClassifier();

private:
    Ui::Widget *ui;
    Content folder;
    SKNeighborsClassifier clf{9,S::manhattan()};

};

#endif // WIDGET_H

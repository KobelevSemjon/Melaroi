#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H
#include <QGraphicsView>
#include <QWheelEvent>

class ImageView:public QGraphicsView
{
    Q_OBJECT
public:
    ImageView(QWidget *parent): QGraphicsView(parent){}
    void wheelEvent(QWheelEvent *event);
};

#endif // IMAGEVIEW_H

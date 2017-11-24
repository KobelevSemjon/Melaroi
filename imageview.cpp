#include "imageview.h"


void ImageView::wheelEvent(QWheelEvent *event)
{
    float delta=event->delta();
    float coef=1+delta/800;
    scale(coef,coef);
    centerOn(mapToScene(event->pos()));
}

#include "simage.h"


SImage SImage::getPlane()
{
    SImage plane(size(),format());
    for (int y = 0; y < height(); ++y)
    {
        uchar* src = scanLine(y);
        uchar* dst = plane.scanLine(y);
        int depth =4;
        for (int x = 0; x < width(); ++x)
        {
            QRgb* srcpixel = reinterpret_cast<QRgb*>(src + x*depth);
            QRgb* dstpixel = reinterpret_cast<QRgb*>(dst + x*depth);

            int gray = qGray(*srcpixel);
            *dstpixel = QColor(gray, gray, gray).rgba();
        }
    }
    return plane;
}

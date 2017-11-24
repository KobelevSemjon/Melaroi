#ifndef SIMAGE_H
#define SIMAGE_H
#include <QImage>

class SImage:public QImage
{
public:
    SImage():QImage(){}
    SImage(const QImage & image)
        :QImage(image){}
    SImage(const QString & fileName, const char * format = 0)
        :QImage(fileName,format){}
    SImage(const QSize & size, Format format)
        :QImage(size, format){}
    SImage(int width, int height, Format format)
        :QImage(width,height, format){}
    SImage(uchar * data, int width, int height, Format format)
        :QImage(data, width, height,format){}
    SImage(const uchar * data, int width, int height, Format format)
        :QImage(data,width,height,format){}
    SImage(uchar * data, int width, int height, int bytesPerLine, Format format)
        :QImage(data,width,height,bytesPerLine,format){}
    SImage(const uchar * data, int width, int height, int bytesPerLine, Format format)
        :QImage(data,width,height,bytesPerLine,format){}
    SImage(const char * fileName, const char * format = 0)
        :QImage(fileName,format){}

    SImage getPlane();

};

#endif // SIMAGE_H

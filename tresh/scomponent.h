#ifndef SCOMPONENT_H
#define SCOMPONENT_H
#include <QImage>
#include <simagestatistics.h>

class SComponent
{
protected:
    double r=0,g=0,b=0;
public:
    SComponent(){}
    SComponent(double r,double g,double b):r(r),g(g),b(b){}
    int operator()(const QRgb& pixel) const
    {return int(r*double(qRed(pixel))+g*double(qRed(pixel))+b*double(qRed(pixel)));}
};

class SMainComponent:public SComponent
{
    SVector_3D eigenvalues;
    SMatrix_3x3 eigenvectors;
public:
    SMainComponent(const QImage& src);
    int operator()(const QRgb& pixel) const
    {return SComponent::operator ()(pixel);}
};

#endif // SCOMPONENT_H

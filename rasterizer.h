#ifndef RASTERIZER_H
#define RASTERIZER_H
#include<QtGui>
#include"polygon2d.h"
class Rasterizer
{
    QImage raster;
public:
    Rasterizer(int w,int h);
    QImage rasterize(Polygon2D);
};

#endif // RASTERIZER_H

#include "polygonkernel.h"

PolygonKernel::PolygonKernel(QSize s,QObject *parent) :
    QObject(parent)
{
    viewportSize=s;
}

void PolygonKernel::setViewportSize(QSize s)
{
    viewportSize=s;
}

QList<Polygon2D> PolygonKernel::getPolygons()
{
    return polygons;
}

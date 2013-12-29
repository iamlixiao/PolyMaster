#include "polygonkernel.h"

PolygonKernel::PolygonKernel(QObject *parent) :
    QObject(parent)
{
}

QList<Polygon2D> PolygonKernel::getPolygons()
{
    return polygons;
}

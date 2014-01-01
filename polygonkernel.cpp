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

QString PolygonKernel::getExplanation()
{
    return explanation;
}

void PolygonKernel::reset()
{
    polygons.clear();
    emit reseted();
}

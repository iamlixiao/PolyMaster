#include "polygon2d.h"

Polygon2D::Polygon2D()
{
    polygons.append(QPointF());
}

Polygon2D::Polygon2D(QList<QPointF>p,QColor c)
{
    polygons.append(p);
    color=c;
}

void Polygon2D::init(QList<QPointF>p, QColor c)
{
    polygons.append(p);
    color=c;
}

QPointF Polygon2D::point(int n)
{
    return polygons.at(n);
}

void Polygon2D::addPoint(QPointF p)
{
    polygons.append(p);
}

int Polygon2D::size()
{
    return polygons.size();
}

void Polygon2D::setColor(QColor c)
{
    color=c;
}

QColor Polygon2D::getColor()
{
    return color;
}

void Polygon2D::clear()
{
    polygons.clear();
    polygons.append(QPointF());
}

void Polygon2D::setLastPoly(QPointF p)
{
    polygons.last()=p;
}

QPointF Polygon2D::firstPoly()
{
    return polygons.first();
}

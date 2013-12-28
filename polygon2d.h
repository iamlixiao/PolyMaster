#ifndef POLYGON2D_H
#define POLYGON2D_H
#include<QtCore>
#include<QPointF>
#include<QColor>

class Polygon2D
{
    QList<QPointF>polygons;
    QColor color;
public:
    Polygon2D();
    Polygon2D(QList<QPointF>, QColor c);
    void init(QList<QPointF>, QColor c);
    QPointF point(int);
    void addPoint(QPointF);
    int size();
    void setColor(QColor);
    QColor getColor();
    void clear();
    void setLastPoly(QPointF);
    QPointF firstPoly();
};

#endif // POLYGON2D_H

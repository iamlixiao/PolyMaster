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
    int points();
    void setColor(QColor);
    QColor getColor();
    void clear();
    void setLast(QPointF);
    QPointF first();
    QPointF last();
};

#endif // POLYGON2D_H

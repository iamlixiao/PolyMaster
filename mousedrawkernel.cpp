#include "mousedrawkernel.h"

MouseDrawKernel::MouseDrawKernel(QObject *parent) :
    PolygonKernel(parent)
{
    polygons.append(Polygon2D());
}

void MouseDrawKernel::mouseMoveEvent(QMouseEvent *e)
{
    polygons.last().setLast(QPointF(e->x(),e->y()));
}

void MouseDrawKernel::mousePressEvent(QMouseEvent *e)
{
    polygons.last().addPoint(QPointF(e->x(),e->y()));
}

void MouseDrawKernel::leaveEvent(QEvent *)
{
    polygons.last().setLast(polygons.last().first());
}

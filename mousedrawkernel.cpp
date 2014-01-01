#include "mousedrawkernel.h"

MouseDrawKernel::MouseDrawKernel(QSize s, QObject *parent) :
    PolygonKernel(s,parent)
{
    polygons.append(Polygon2D());
    emit updated();

    connect(this,SIGNAL(reseted()),SLOT(clear()));
}

void MouseDrawKernel::mouseMoveEvent(QMouseEvent *e)
{
    polygons.last().setLast(QPointF(e->x(),e->y()));
    emit updated();
}

void MouseDrawKernel::mousePressEvent(QMouseEvent *e)
{
    polygons.last().addPoint(QPointF(e->x(),e->y()));
    emit updated();
}

void MouseDrawKernel::leaveEvent(QEvent *)
{
    polygons.last().setLast(polygons.last().first());
    emit updated();
}

void MouseDrawKernel::keyPressEvent(QKeyEvent *)
{

}

void MouseDrawKernel::keyReleaseEvent(QKeyEvent *)
{

}

void MouseDrawKernel::clear()
{
    polygons.append(Polygon2D());
    emit updated();
}

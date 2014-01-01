#include "mousedrawkernel.h"

MouseDrawKernel::MouseDrawKernel(QSize s, QObject *parent) :
    PolygonKernel(s,parent)
{
    explanation="用鼠标在绘图区域中点击，可以增加顶点，画出多边形！";
    polygons.append(Polygon2D({QPoint()},Qt::red));
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

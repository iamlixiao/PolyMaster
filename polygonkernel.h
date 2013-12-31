#ifndef POLYGONKERNEL_H
#define POLYGONKERNEL_H

#include <QObject>
#include<QtGui>
#include"polygon2d.h"

class PolygonKernel : public QObject
{
    Q_OBJECT
protected:
    QList<Polygon2D> polygons;
    QSize viewportSize;
public:
    explicit PolygonKernel(QSize s, QObject *parent = 0);
    void setViewportSize(QSize);
    QList<Polygon2D> getPolygons();

    virtual void mouseMoveEvent(QMouseEvent *)=0;
    virtual void mousePressEvent(QMouseEvent *)=0;
    virtual void leaveEvent(QEvent *)=0;
signals:
    void updated();
public slots:

};

#endif // POLYGONKERNEL_H

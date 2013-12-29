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
public:
    explicit PolygonKernel(QObject *parent = 0);
    QList<Polygon2D> getPolygons();

    virtual void mouseMoveEvent(QMouseEvent *)=0;
    virtual void mousePressEvent(QMouseEvent *)=0;
    virtual void leaveEvent(QEvent *)=0;
signals:

public slots:

};

#endif // POLYGONKERNEL_H

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
    QString explanation;
public:
    explicit PolygonKernel(QSize s, QObject *parent = 0);
    void setViewportSize(QSize);
    QList<Polygon2D> getPolygons();
    QString getExplanation();

    virtual void mouseMoveEvent(QMouseEvent *)=0;
    virtual void mousePressEvent(QMouseEvent *)=0;
    virtual void leaveEvent(QEvent *)=0;
    virtual void keyPressEvent(QKeyEvent*)=0;
    virtual void keyReleaseEvent(QKeyEvent *e)=0;
signals:
    void updated();
    void reseted();
public slots:
    void reset();
};

#endif // POLYGONKERNEL_H

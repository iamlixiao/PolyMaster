#ifndef POLYCANVAS_H
#define POLYCANVAS_H

#include <QtWidgets>
#include<QPoint>
#include"polygon2d.h"
#include"mousedrawkernel.h"

class PolyCanvas : public QWidget
{
    Q_OBJECT
    PolygonKernel*kernel;
    Polygon2D polygons;
    QPixmap*viewport;
    QSize viewportSize;
    QRgb paintcolor=qRgb(255,0,0);
public:
    explicit PolyCanvas(QWidget *parent = 0);

signals:

public slots:
    void update();
protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void leaveEvent(QEvent *);
};

#endif // POLYCANVAS_H

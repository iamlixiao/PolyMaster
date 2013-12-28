#ifndef POLYCANVAS_H
#define POLYCANVAS_H

#include <QtWidgets>
#include<QPoint>
#include"polygon2d.h"
#include"rasterizer.h"

class PolyCanvas : public QWidget
{
    Q_OBJECT
    QList<QPoint>points;
    QImage*canvas;
    QRgb paintcolor=qRgb(255,0,0);
    Polygon2D activePoly;
    QImage mask;
    Rasterizer*R;
public:
    explicit PolyCanvas(QWidget *parent = 0);

signals:

public slots:
protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void leaveEvent(QEvent *);
};

#endif // POLYCANVAS_H

#ifndef POLYCANVAS_H
#define POLYCANVAS_H

#include <QtWidgets>
#include<QPoint>

class PolyCanvas : public QWidget
{
    Q_OBJECT
    QList<QPoint>points;
    QImage*canvas;
    QRgb paintcolor=qRgb(255,0,0);
public:
    explicit PolyCanvas(QWidget *parent = 0);

signals:

public slots:
protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
};

#endif // POLYCANVAS_H

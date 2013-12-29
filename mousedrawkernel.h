#ifndef MOUSEDRAWKERNEL_H
#define MOUSEDRAWKERNEL_H
#include<polygonkernel.h>

class MouseDrawKernel : public PolygonKernel
{
    Q_OBJECT
public:
    explicit MouseDrawKernel(QSize s,QObject *parent = 0);

    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void leaveEvent(QEvent *);
signals:

public slots:

};

#endif // MOUSEDRAWKERNEL_H

#ifndef CUBEKERNEL_H
#define CUBEKERNEL_H
#include"polygon3d.h"
#include"polygonkernel.h"

class CubeKernel : public PolygonKernel
{
    Q_OBJECT
    void setTranslation(QVector3D p)
    {
        viewPoint=p;
        qreal a=p.x(),b=p.y(),c=p.z();
        qreal u=qSqrt(a*a+b*b+c*c),v=qSqrt(a*a+b*b);
        QMatrix4x4 T(-b/v,-a*c/u/v,-a/u,0,a/v,-b*c/u/v,-b/u,0,0,v/u,-c/u,0,0,0,u,1);
        translation=T;
    }
    QList<Polygon3D> scene;
    QVector3D viewPoint;
    QMatrix4x4 translation;
    qreal zs;
public:
    explicit CubeKernel(QObject *parent = 0);

    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void leaveEvent(QEvent *);
signals:

public slots:

};

#endif // CUBEKERNEL_H

#ifndef CUBEKERNEL_H
#define CUBEKERNEL_H
#include"polygon3d.h"
#include"polygonkernel.h"
#include<functional>

class CubeKernel : public PolygonKernel
{
    Q_OBJECT
    void setTranslation()
    {
        qreal a=viewPoint.x(),b=viewPoint.y(),c=viewPoint.z();
        qreal u=qSqrt(a*a+b*b+c*c),v=qSqrt(a*a+b*b);
        QMatrix4x4 T(-b/v,-a*c/u/v,-a/u,0,a/v,-b*c/u/v,-b/u,0,0,v/u,-c/u,0,0,0,u,1);
        aspect=T;
    }
    void setTranslation(QVector3D p);
    std::function<void()> rotateXZ001=[=]
    {
        rotation.rotate(3.6,0,1,0);
        update();
    };
    std::function<void()> rotateYZ001=[=]
    {
        rotation.rotate(3.6,1,0,0);
        update();
    };
    void rotateXZ(qreal a)
    {
        rotation.rotate(360*a,0,1,0);
    }
    void rotateYZ(qreal a)
    {
        rotation.rotate(360*a,1,0,0);
    }

    bool cubeSideNearer(Polygon3D s1,Polygon3D s2)
    {
        return viewPoint.distanceToPoint(s1.getCenter())<viewPoint.distanceToPoint(s2.getCenter());
    }
    bool canSee(Polygon3D face)
    {
        QVector3D n=-face.getCenter()*rotation;
        QVector3D v=viewPoint-face.getCenter()*rotation-movement;
        return QVector3D::dotProduct(n,v)<0;
    }
    float illuminace(Polygon3D face)
    {
        QVector3D n=-face.getCenter()*rotation;
        return QVector3D::dotProduct(n.normalized(),lightDirection.normalized());
    }

    void update();

    QList<Polygon3D> scene;
    QVector3D viewPoint;
    QVector3D lightDirection=QVector3D(1,1,2);
    QMatrix4x4 aspect;
    QMatrix4x4 rotation;
    QVector3D movement;
    qreal zs;

    QTimer*rotateXY001Timer,*rotateXZ001Timer,*rotateYZ001Timer;
    QTimer*rotateXY001bTimer,*rotateXZ001bTimer,*rotateYZ001bTimer;
    QTimer*moveX1Timer,*moveY1Timer,*moveZ1Timer;
    QTimer*moveX1bTimer,*moveY1bTimer,*moveZ1bTimer;
public:
    CubeKernel(QSize s,QObject *parent = 0);

    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void leaveEvent(QEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
signals:

public slots:
    void recover();
};

#endif // CUBEKERNEL_H

#ifndef CUBEKERNEL_H
#define CUBEKERNEL_H
#include"polygon3d.h"
#include"polygonkernel.h"

class CubeKernel : public PolygonKernel
{
    Q_OBJECT
    void setTranslation()
    {
        qreal a=viewPoint.x(),b=viewPoint.y(),c=viewPoint.z();
        qreal u=qSqrt(a*a+b*b+c*c),v=qSqrt(a*a+b*b);
        QMatrix4x4 T(-b/v,-a*c/u/v,-a/u,0,a/v,-b*c/u/v,-b/u,0,0,v/u,-c/u,0,0,0,u,1);
        translation=T;
        //改变了视点之后，面的排序也要随之改变
        for(int i=1;i<scene.size();++i)
        {
            for(int j=0;j<i;++j)
            {
                if(cubeSideNearer(scene.at(j),scene.at(i)))
                    scene.move(j,i);
            }
        }
    }
    void setTranslation(QVector3D p)
    {
        viewPoint=p;
        setTranslation();
    }
    void rotateXY(qreal a)
    {
        qreal originalAngle=qAtan2(viewPoint.y(),viewPoint.x());
        qreal newAngle=originalAngle+a;
        viewPoint.setX(200*qCos(newAngle));
        viewPoint.setY(200*qSin(newAngle));
        setTranslation();
    }
    bool cubeSideNearer(Polygon3D s1,Polygon3D s2)
    {
        return viewPoint.distanceToPoint(s1.getCenter())<viewPoint.distanceToPoint(s2.getCenter());
    }
    void update()
    {
        polygons.clear();
        double dx=viewportSize.width()/2.0,dy=viewportSize.height()/2.0;
        foreach(Polygon3D p,scene)
        {
            QList<QVector3D> ce=p.renderOut(translation);
            QList<QPointF> cs;
            foreach(QVector3D e,ce)
            {
                    cs.append(QPointF(e.x()*zs/e.z()+dx,e.y()*zs/e.z()+dy));
                    qDebug()<<QPointF(e.x()*zs/e.z(),e.y()*zs/e.z());
            }
            polygons.append(Polygon2D(cs,p.getColor()));
        }
        emit updated();
    }

    QList<Polygon3D> scene;
    QVector3D viewPoint;
    QMatrix4x4 translation;
    qreal zs;
public:
    CubeKernel(QSize s,QObject *parent = 0);

    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void leaveEvent(QEvent *);
signals:

public slots:

};

#endif // CUBEKERNEL_H

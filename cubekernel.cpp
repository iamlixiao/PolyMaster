#include "cubekernel.h"

CubeKernel::CubeKernel(QSize s, QObject *parent) :
    PolygonKernel(s,parent)
{
    scene.append(Polygon3D({{-50,50,-50},{50,50,-50},{50,50,50},{-50,50,50}},Qt::red));
    scene.append(Polygon3D({{-50,-50,-50},{50,-50,-50},{50,-50,50},{-50,-50,50}},Qt::yellow));
    scene.append(Polygon3D({{50,-50,-50},{50,50,-50},{50,50,50},{50,-50,50}},Qt::green));

    setTranslation({-50,-100,0});
    zs=90;

    double dx=s.width()/2.0,dy=s.height()/2.0;
    qDebug()<<dx<<dy<<s;
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
}

void CubeKernel::mouseMoveEvent(QMouseEvent *)
{

}

void CubeKernel::mousePressEvent(QMouseEvent *)
{

}

void CubeKernel::leaveEvent(QEvent *)
{

}

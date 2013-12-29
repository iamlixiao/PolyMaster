#include "cubekernel.h"

CubeKernel::CubeKernel(QObject *parent) :
    PolygonKernel(parent)
{
    scene.append(Polygon3D({{0,0,0},{50,0,0},{50,0,50},{0,0,50}},Qt::red));

    setTranslation({0,-100,0});
    zs=50;

    foreach(Polygon3D p,scene)
    {
        QList<QVector3D> ce=p.renderOut(translation);
        QList<QPointF> cs;
        foreach(QVector3D e,ce)
        {
                cs.append(QPointF(e.x()*zs/e.z(),e.y()*zs/e.z()));
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

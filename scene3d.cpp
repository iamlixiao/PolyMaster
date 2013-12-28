#include "scene3d.h"

Scene3D::Scene3D()
{
}

void Scene3D::addPolygon(QList<Polygon3D>p)
{
    polygons.append(p);
}

void Scene3D::addPolygon(Polygon3D p)
{
    polygons.append(p);
}

void Scene3D::setViewPoint(QVector3D p)
{
    viewPoint=p;
    qreal a=p.x(),b=p.y(),c=p.z();
    qreal u=qSqrt(a*a+b*b+c*c),v=qSqrt(a*a+b*b);
    QMatrix4x4 T(-b/v,-a*c/u/v,-a/u,0,a/v,-b*c/u/v,-b/u,0,0,v/u,-c/u,0,0,0,u,1);
    translation=T;
}

void Scene3D::setZs(qreal z)
{
    zs=z;
}

QList<Polygon2D> Scene3D::renderOut()
{
    QList<Polygon2D>c;
    foreach(Polygon3D p,polygons)
    {
        QList<QVector3D> ce=p.renderOut(translation);
        QList<QPointF> cs;
        foreach(QVector3D e,ce)
        {
                cs.append(QPointF(e.x()*zs/e.z(),e.y()*zs/e.z()));
        }
        c.append(Polygon2D(cs,p.getColor()));
    }
    return c;
}

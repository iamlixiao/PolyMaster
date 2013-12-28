#include "polygon3d.h"

Polygon3D::Polygon3D()
{
}

void Polygon3D::addVertices(QList<QVector3D> v)
{
    vertices.append(v);
}

void Polygon3D::addVertices(QVector3D v)
{
    vertices.append(v);
}

void Polygon3D::setViewPoint(QVector3D p)
{
    viewPoint=p;
    qreal a=p.x(),b=p.y(),c=p.z();
    qreal u=qSqrt(a*a+b*b+c*c),v=qSqrt(a*a+b*b);
    QMatrix4x4 T(-b/v,-a*c/u/v,-a/u,0,a/v,-b*c/u/v,-b/u,0,0,v/u,-c/u,0,0,0,u,1);
//    QMatrix4x4 T(1,0,0,0,0,1,0,0,0,0,1,0,5,5,5,1);
}

void Polygon3D::setZs(qreal z)
{
    zs=z;
}

void Polygon3D::setColor(QColor c)
{
    color=c;
}

QColor Polygon3D::getColor()
{
    return color;
}

QList<QVector3D> Polygon3D::renderOut(QMatrix4x4 translation)
{
    QList<QVector3D>c;
    foreach(QVector3D p,vertices)
    {
        QVector3D e=p*translation;
        qDebug()<<p*translation;
        c.append(e);
    }
    return c;
}

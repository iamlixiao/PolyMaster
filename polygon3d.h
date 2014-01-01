#ifndef MESH3D_H
#define MESH3D_H
#include<QtCore>
#include<qvector3d.h>
#include<qmatrix4x4.h>
#include<QColor>
#include"polygon2d.h"
class Polygon3D
{
    QList<QVector3D>vertices;
    QVector3D viewPoint;
    qreal zs;
    QColor color;
public:
    Polygon3D();
    Polygon3D(QList<QVector3D>v,QColor c);
    void addVertices(QList<QVector3D>v);
    void addVertices(QVector3D v);
    void setViewPoint(QVector3D p);
    void setZs(qreal z);
    void setColor(QColor);
    QColor getColor();
    QVector3D getCenter()
    {
        //求平均
        qreal x=0,y=0,z=0,s=vertices.size();
        foreach (QVector3D v, vertices) {
            x+=v.x()/s;
            y+=v.y()/s;
            z+=v.z()/s;
        }
        return QVector3D(x,y,z);
    }
    QList<QVector3D> renderOut(QMatrix4x4);
    QList<QVector3D> renderOut(QMatrix4x4,QVector3D,QMatrix4x4);
};

#endif // MESH3D_H

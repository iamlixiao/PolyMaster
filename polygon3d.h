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
    void addVertices(QList<QVector3D>v);
    void addVertices(QVector3D v);
    void setViewPoint(QVector3D p);
    void setZs(qreal z);
    void setColor(QColor);
    QColor getColor();
    QList<QVector3D> renderOut(QMatrix4x4);
};

#endif // MESH3D_H

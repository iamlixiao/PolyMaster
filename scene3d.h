#ifndef SCENE3D_H
#define SCENE3D_H
#include<QtCore>
#include"polygon3d.h"
class Scene3D
{
    QList<Polygon3D>polygons;
    QVector3D viewPoint;
    QMatrix4x4 translation;
    qreal zs;
public:
    Scene3D();
    void addPolygon(QList<Polygon3D>);
    void addPolygon(Polygon3D);
    void setViewPoint(QVector3D p);
    void setZs(qreal z);
    QList<Polygon2D> renderOut();
};

#endif // SCENE3D_H

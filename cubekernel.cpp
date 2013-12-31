#include "cubekernel.h"

CubeKernel::CubeKernel(QSize s, QObject *parent) :
    PolygonKernel(s,parent)
{
    scene.append(Polygon3D({{-50,50,-50},{50,50,-50},{50,50,50},{-50,50,50}},Qt::red));
    scene.append(Polygon3D({{-50,-50,-50},{50,-50,-50},{50,-50,50},{-50,-50,50}},Qt::yellow));
    scene.append(Polygon3D({{50,-50,-50},{50,50,-50},{50,50,50},{50,-50,50}},Qt::green));

    setTranslation({-50,-100,0});
    zs=90;

    update();
    QTimer*timer=new QTimer(this);
    timer->setInterval(33);
    connect(timer,&QTimer::timeout,[=]{
        rotateXY(0.01);
        update();
    });
    timer->start();
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

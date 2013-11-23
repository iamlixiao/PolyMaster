#include<QPainter>
#include<QDebug>
#include "polycanvas.h"

void paintCanvas(QImage*canvas,QList<QPoint>*points)
{
    canvas->fill(Qt::white);
    QPoint firstPoint=points->at(0),previousPoint=firstPoint;
    for(int i=1;i<points->size();++i)
    {
        QPoint currentPoint=points->at(i);
        QPoint d=currentPoint-previousPoint;
        qDebug()<<d;
        double k=(double)d.y()/d.x();
        qDebug()<<k;
        for(int x=(d.x()<0?d.x():0);x<=(d.x()>0?d.x():0);++x)
        {
            int y=x*k+previousPoint.y();
            canvas->setPixel(previousPoint.x()+x,y,qRgb(255,0,0));
        }
        previousPoint=currentPoint;
    }
    QPoint leftone(-1,0),rightone(1,0),topone(0,-1),buttomone(0,1);
    foreach(QPoint point,*points)
    {
        canvas->setPixel(point,qRgb(0,0,0));
        canvas->setPixel(point+leftone,qRgb(0,0,0));
        canvas->setPixel(point+rightone,qRgb(0,0,0));
        canvas->setPixel(point+topone,qRgb(0,0,0));
        canvas->setPixel(point+buttomone,qRgb(0,0,0));
    }
}

PolyCanvas::PolyCanvas(QWidget *parent) :
    QWidget(parent)
{
    points.append({QPoint(5,5),QPoint(10,10),QPoint(405,50)});
    points.append(QPoint(10,55));
    points.append(QPoint(400,60));
    canvas=new QImage(500,500,QImage::Format_ARGB32);
    paintCanvas(canvas,&points);
}

void PolyCanvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0,0),*canvas);
}

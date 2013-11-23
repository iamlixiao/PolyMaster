#include<QPainter>
#include<QDebug>
#include "polycanvas.h"
#include<iostream>
#include<QMouseEvent>
using namespace std;


void fillRegion(QImage*canvas,QPoint previousPoint,QPoint currentPoint){ //image, point0, point1

    QPoint d=currentPoint-previousPoint;
    if (d.x()==0){
        if (d.y()>0)
            for(int i=0;i<d.y();i++)
                canvas->setPixel(previousPoint.x(),previousPoint.y()+i,qRgb(255,0,0));
        else
            for(int i=d.y();i<=0;i++)
                canvas->setPixel(previousPoint.x(),previousPoint.y()+i,qRgb(255,0,0));
        return;
    }

    double k=(double)d.y()/d.x();
    for(int x=(d.x()<0?d.x():0);x<(d.x()>0?d.x():0);++x)
    {
        int y=x*k+previousPoint.y()+0.5;
        //canvas->setPixel(previousPoint.x()+x,y,qRgb(255,0,0));
        for(int yy=y;yy<500;yy++){
            if (canvas->pixel(previousPoint.x()+x,yy)==qRgb(255,0,0))
                canvas->setPixel(previousPoint.x()+x,yy,qRgb(255,255,255));
            else
                canvas->setPixel(previousPoint.x()+x,yy,qRgb(255,0,0));
        }
    }
}


void paintCanvas(QImage*canvas,QList<QPoint>*points)
{
    canvas->fill(Qt::white);
    QPoint firstPoint=points->at(0),previousPoint=firstPoint;
    for(int i=1;i<points->size();++i)
    {
        QPoint currentPoint=points->at(i);

        fillRegion(canvas,previousPoint,currentPoint);

        previousPoint=currentPoint;
    }
    fillRegion(canvas,points->at(points->size()-1),points->at(0));
    foreach(QPoint point,*points)
    {
        for(int i=-6;i<7;++i)
        {
            canvas->setPixel(point.x()+i,point.y(),qRgb(0,0,0));
            canvas->setPixel(point.x(),point.y()+i,qRgb(0,0,0));
        }
    }
}



PolyCanvas::PolyCanvas(QWidget *parent) :
    QWidget(parent)
{
    points.append(QPoint());
    setMouseTracking(true);
    canvas=new QImage(500,500,QImage::Format_ARGB32);
    canvas->fill(Qt::white);
}

void PolyCanvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0,0),*canvas);
}

void PolyCanvas::mouseMoveEvent(QMouseEvent *e)
{
    if(e->x()<canvas->width()&&e->y()<canvas->height())
    {
        points[points.size()-1]=QPoint(e->x(),e->y());
        if(points.size()>1)
        {
            paintCanvas(canvas,&points);
            update();
        }
    }
    else
    {
        points[points.size()-1]=points.at(0);
        paintCanvas(canvas,&points);
        update();
    }
}

void PolyCanvas::mousePressEvent(QMouseEvent *e)
{
    if(e->x()<canvas->width()&&e->y()<canvas->height())
    {
        points.append(QPoint(e->x(),e->y()));
        paintCanvas(canvas,&points);
        update();
    }

}

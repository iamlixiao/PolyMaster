#include<QPainter>
#include<QDebug>
#include "polycanvas.h"
#include<iostream>
#include<QMouseEvent>
using namespace std;


void drawLine(QImage*canvas,QPoint previousPoint,QPoint currentPoint){ //image, point0, point1

    QPoint d=currentPoint-previousPoint;
    qDebug()<<d;
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
    qDebug()<<k;
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

        drawLine(canvas,previousPoint,currentPoint);

        previousPoint=currentPoint;
    }
    drawLine(canvas,points->at(points->size()-1),points->at(0));

    /*int minX = 499;
    int maxX = 0;
    for(int i=0;i<points->size();i++){
        if (points->at(i).x()>maxX)
            maxX = points->at(i).x();
        if (points->at(i).x()<minX)
            minX = points->at(i).x();
    }
    for(int scanLine=minX;scanLine<=maxX;scanLine++){
        int downX = 0;
        for(int i=499;i>=0;i--)
            if (canvas->pixel(scanLine,i)==qRgb(255,0,0)){
                downX = i;
                break;
            }

        bool flag = false;
        for(int i=0;i<=downX;i++){
            if (canvas->pixel(scanLine,i)==qRgb(255,0,0)){
                    flag = !flag;
                   // if (scanLine==10)
                        //cout<<rightX<<i<<endl;
            }
            if (!flag)
                 canvas->setPixel(scanLine,i,qRgb(255,255,255));
            else
                 canvas->setPixel(scanLine,i,qRgb(255,0,0));
         }
    }*/



}



PolyCanvas::PolyCanvas(QWidget *parent) :
    QWidget(parent)
{
    points.append({QPoint(50,50),QPoint(75,150),QPoint(225,150),QPoint(125,175)});
    setMouseTracking(true);
    canvas=new QImage(500,500,QImage::Format_ARGB32);
    paintCanvas(canvas,&points);
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
        points[0]=QPoint(e->x(),e->y());
        paintCanvas(canvas,&points);
        update();
    }
}

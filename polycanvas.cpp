#include<QPainter>
#include<QDebug>
#include "polycanvas.h"
#include<iostream>
#include<QMouseEvent>
using namespace std;


void fillRegion(QImage*canvas,QPoint previousPoint,QPoint currentPoint,QRgb color){ //image, point0, point1

    QPoint d=currentPoint-previousPoint;
    if (d.x()==0){
        if (d.y()>0)
            for(int i=0;i<d.y();i++)
                canvas->setPixel(previousPoint.x(),previousPoint.y()+i,color);
        else
            for(int i=d.y();i<=0;i++)
                canvas->setPixel(previousPoint.x(),previousPoint.y()+i,color);
        return;
    }

    double k=(double)d.y()/d.x();
    for(int x=(d.x()<0?d.x():0);x<(d.x()>0?d.x():0);++x)
    {
        int y=x*k+previousPoint.y()+0.5;
        //canvas->setPixel(previousPoint.x()+x,y,qRgb(255,0,0));
        for(int yy=y;yy<canvas->height();yy++){
            if (canvas->pixel(previousPoint.x()+x,yy)==color)
                canvas->setPixel(previousPoint.x()+x,yy,qRgb(255,255,255));
            else
                canvas->setPixel(previousPoint.x()+x,yy,color);
        }
    }
}


void paintCanvas(QImage*canvas,QList<QPoint>*points,QRgb color)
{
    canvas->fill(Qt::white);
    QPoint firstPoint=points->at(0),previousPoint=firstPoint;
    for(int i=1;i<points->size();++i)
    {
        QPoint currentPoint=points->at(i);

        fillRegion(canvas,previousPoint,currentPoint,color);

        previousPoint=currentPoint;
    }
    fillRegion(canvas,points->at(points->size()-1),points->at(0),color);
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

    QPushButton*clearbutton=new QPushButton("清空",this);
    clearbutton->move(width()-clearbutton->width()-25,25);
    connect(clearbutton,&QPushButton::clicked,[=]{
        canvas->fill(Qt::white);
        update();
        points.clear();
        points.append(QPoint());
    });

    QLineEdit*rgbedit=new QLineEdit("255,0,0",this);
    rgbedit->move(width()-clearbutton->width()-25,75);
    QPushButton*changecolor=new QPushButton("更改颜色",this);
    changecolor->move(width()-clearbutton->width()-25,125);
    connect(changecolor,&QPushButton::clicked,[=]{
        QStringList colortxt=rgbedit->text().split(',');
        paintcolor=qRgb(colortxt[0].toInt(),colortxt[1].toInt(),colortxt[2].toInt());
        paintCanvas(canvas,&points,paintcolor);
        update();
    });

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
    }
    else
    {
        points[points.size()-1]=points.at(0);
    }
    paintCanvas(canvas,&points,paintcolor);
    update();
}

void PolyCanvas::mousePressEvent(QMouseEvent *e)
{
    if(e->x()<canvas->width()&&e->y()<canvas->height())
    {
        points.append(QPoint(e->x(),e->y()));
        paintCanvas(canvas,&points,paintcolor);
        update();
    }

}

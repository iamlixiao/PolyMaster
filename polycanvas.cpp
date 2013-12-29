#include<QPainter>
#include<QDebug>
#include "polycanvas.h"
#include<iostream>
#include<QMouseEvent>

QImage*rasterizePolygon(QSize rasterSize,Polygon2D p)
{
    QImage*raster=new QImage(rasterSize,QImage::Format_ARGB32);
    raster->fill(Qt::transparent);

    QRgb*bit=(QRgb*)raster->bits();

    auto flipDown=[=](QPointF p1,QPointF p2,QRgb color)
    {
        auto setPix=[=](int x,int y)
        {
            if(x>0&&x<rasterSize.width()&&y>0&&y<rasterSize.height())
            {
                if(bit[y*rasterSize.width()+x]==color)
                    bit[y*rasterSize.width()+x]=Qt::transparent;
                else
                    bit[y*rasterSize.width()+x]=color;
            }
        };


        QPointF d=p2-p1;

        if (d.x()==0){
            if (d.y()>0)
                for(int i=0;i<d.y();i++)
                    setPix(p1.x(),p1.y()+i);
            else
                for(int i=d.y();i<=0;i++)
                    setPix(p1.x(),p1.y()+i);
            return;
        }

        double k=(double)d.y()/d.x();
        for(int x=(d.x()<0?d.x():0);x<(d.x()>0?d.x():0);++x)
        {
            int y=x*k+p1.y()+0.5;
            for(int yy=y;yy<rasterSize.height();yy++){
                setPix(p1.x()+x,yy);
            }
        }
    };

    QPointF firstPoint=p.first(),previousPoint=firstPoint;
    for(int i=1;i<p.points();++i)
    {
        QPointF currentPoint=p.point(i);
        flipDown(previousPoint,currentPoint,p.getColor().rgb());
        previousPoint=currentPoint;
    }
    flipDown(p.last(),p.first(),p.getColor().rgb());
    return raster;
}

PolyCanvas::PolyCanvas(QWidget *parent) :
    QWidget(parent)
{
    viewportSize={500,500};
    viewport=new QPixmap(viewportSize);
    viewport->fill(Qt::white);

    kernel=new MouseDrawKernel(this);

    setMouseTracking(true);

    setWindowTitle("多边形绘图");
    resize(650,500);

    QPushButton*clearbutton=new QPushButton("清空",this);
    clearbutton->move(width()-clearbutton->width()-25,25);
    connect(clearbutton,&QPushButton::clicked,[=]{
        viewport->fill(Qt::white);
        update();
        polygons.clear();
    });

    QLineEdit*rgbedit=new QLineEdit("255,0,0",this);
    rgbedit->setGeometry(width()-clearbutton->width()-25,75,clearbutton->width(),rgbedit->height());
    QPushButton*changecolor=new QPushButton("更改颜色",this);
    changecolor->move(width()-clearbutton->width()-25,125);
    connect(changecolor,&QPushButton::clicked,[=]{
        QStringList colortxt=rgbedit->text().split(',');
        paintcolor=qRgb(colortxt[0].toInt(),colortxt[1].toInt(),colortxt[2].toInt());
        update();
    });

}

void PolyCanvas::update()
{
    viewport->fill(Qt::white);
    QPainter painter(viewport);
    foreach (Polygon2D p, kernel->getPolygons()) {
        QImage*img=rasterizePolygon(viewportSize,p);
        painter.drawImage(0,0,*img);
        delete img;
    }
    QWidget::update();
}

void PolyCanvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,*viewport);
}

void PolyCanvas::mouseMoveEvent(QMouseEvent *e)
{
    if(e->x()<viewportSize.width()&&e->y()<viewportSize.height())
    {
        kernel->mouseMoveEvent(e);
    }
    else
    {
        kernel->leaveEvent(e);
    }
    update();
}

void PolyCanvas::mousePressEvent(QMouseEvent *e)
{
    if(e->x()<viewportSize.width()&&e->y()<viewportSize.height())
    {
        kernel->mousePressEvent(e);
        update();
    }

}

void PolyCanvas::leaveEvent(QEvent *e)
{
    kernel->leaveEvent(e);
    update();
}

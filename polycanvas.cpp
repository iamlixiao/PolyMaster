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

    auto flipDown=[=](QPointF pf1,QPointF pf2,QRgb color)
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
        auto drawPix=[=](int x,int y,bool erase=false)
        {
            if(x>0&&x<rasterSize.width()&&y>0&&y<rasterSize.height())
            {
                if(erase)
                    bit[y*rasterSize.width()+x]=Qt::transparent;
                else
                    bit[y*rasterSize.width()+x]=color;
            }
        };

        QPoint p2(pf2.x(),pf2.y()),p1(pf1.x(),pf1.y());
        QPoint d=p2-p1;

        if (d.x()==0){
            if (d.y()>0)
            {
                for(int i=p1.y();i<=p2.y();i++)
                    drawPix(p1.x(),i);
            }
            else
                for(int i=p2.y();i<=p1.y();i++)
                    setPix(p1.x(),i);
            return;
        }

        double k=(double)d.y()/d.x();
        for(int x=(d.x()<0?d.x():0);x<(d.x()>0?d.x():0);++x)
        {
            int y=x*k+p1.y();
            for(int yy=y;yy<rasterSize.height();yy++){
                setPix(p1.x()+x,yy);
            }
        }
    };

    QPointF previousPoint=p.first();
    for(int i=1;i<p.points();++i)
    {
        QPointF currentPoint=p.point(i);
        flipDown(previousPoint,currentPoint,p.getColor().rgb());
        previousPoint=currentPoint;
    }
    flipDown(previousPoint,p.first(),p.getColor().rgb());
    return raster;
}

PolyCanvas::PolyCanvas(QWidget *parent) :
    QWidget(parent)
{
    viewportSize={500,500};
    viewport=new QPixmap(viewportSize);
    viewport->fill(Qt::white);

    PolygonKernel*kernel1=new MouseDrawKernel(viewportSize,this);
    PolygonKernel*kernel2=new CubeKernel(viewportSize,this);

    kernel=kernel1;
    kernel->setViewportSize(viewportSize);

    connect(kernel,SIGNAL(updated()),SLOT(update()));

    setMouseTracking(true);

    setWindowTitle("多边形绘图");
    resize(650,500);

    QPushButton*clearbutton=new QPushButton("重置",this);
    clearbutton->move(width()-clearbutton->width()-25,25);
    connect(clearbutton,&QPushButton::clicked,[=]{
        viewport->fill(Qt::white);
        kernel->reset();
    });

    QLabel*explain=new QLabel(kernel->getExplanation(),this);
    explain->move(width()-clearbutton->width()-25,175);
    explain->setFixedWidth(clearbutton->width());
    explain->setFixedHeight(height()-explain->geometry().top());
    explain->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    explain->setWordWrap(true);

    QPushButton*useKernel1=new QPushButton("绘制多边形",this);
    useKernel1->move(width()-clearbutton->width()-25,75);
    connect(useKernel1,&QPushButton::clicked,[=]{
        kernel=kernel1;
        connect(kernel,SIGNAL(updated()),SLOT(update()));
        explain->setText(kernel->getExplanation());
        update();
    });

    QPushButton*useKernel2=new QPushButton("3D立方体",this);
    useKernel2->move(width()-clearbutton->width()-25,125);
    connect(useKernel2,&QPushButton::clicked,[=]{
        kernel=kernel2;
        connect(kernel,SIGNAL(updated()),SLOT(update()));
        explain->setText(kernel->getExplanation());
        update();
    });

    update();
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
}

void PolyCanvas::mousePressEvent(QMouseEvent *e)
{
    if(e->x()<viewportSize.width()&&e->y()<viewportSize.height())
    {
        kernel->mousePressEvent(e);
    }

}

void PolyCanvas::leaveEvent(QEvent *e)
{
    kernel->leaveEvent(e);
}

void PolyCanvas::keyPressEvent(QKeyEvent *e)
{
    kernel->keyPressEvent(e);
}

void PolyCanvas::keyReleaseEvent(QKeyEvent *e)
{
    kernel->keyReleaseEvent(e);
}

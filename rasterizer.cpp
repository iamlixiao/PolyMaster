#include "rasterizer.h"
void setPix(QImage*canvas,QPointF pixel)
{
    QPoint p=QPoint(pixel.x(),pixel.y());
    if(canvas->rect().contains(p))
    {
        canvas->setPixel(p,~canvas->pixelIndex(p));
    }
}

void fillRegion(QImage*canvas,QPointF previousPoint,QPointF currentPoint){ //image, point0, point1

    QPointF d=currentPoint-previousPoint;

    if (d.x()==0){
        if (d.y()>0)
            for(int i=0;i<d.y();i++)
                setPix(canvas,previousPoint+QPointF(0,i));
        else
            for(int i=d.y();i<=0;i++)
                setPix(canvas,previousPoint+QPointF(0,i));
        return;
    }

    double k=(double)d.y()/d.x();
    for(int x=(d.x()<0?d.x():0);x<(d.x()>0?d.x():0);++x)
    {
        int y=x*k+previousPoint.y()+0.5;
        for(int yy=y;yy<canvas->height();yy++){
            setPix(canvas,QPointF(previousPoint.x()+x,yy));
        }
    }
}

Rasterizer::Rasterizer(int w, int h)
{
    QImage img=QImage(w,h,QImage::Format_Mono);
    raster.swap(img);
}

QImage Rasterizer::rasterize(Polygon2D p)
{
    raster.fill(Qt::color0);
    QPointF firstPoint=p.point(0),previousPoint=firstPoint;
    for(int i=1;i<p.size();++i)
    {
        QPointF currentPoint=p.point(i);

        fillRegion(&raster,previousPoint,currentPoint);

        previousPoint=currentPoint;
    }
    fillRegion(&raster,p.point(p.size()-1),firstPoint);
    return raster;
}

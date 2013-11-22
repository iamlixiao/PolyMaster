#include<QPainter>
#include "polycanvas.h"

PolyCanvas::PolyCanvas(QWidget *parent) :
    QWidget(parent)
{
}

void PolyCanvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawEllipse(5,5,100,300);
}

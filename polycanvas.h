#ifndef POLYCANVAS_H
#define POLYCANVAS_H

#include <QWidget>
#include<QPoint>

class PolyCanvas : public QWidget
{
    Q_OBJECT
    QList<QPoint>points;
    QImage*canvas;
public:
    explicit PolyCanvas(QWidget *parent = 0);

signals:

public slots:
protected:
    void paintEvent(QPaintEvent *);
};

#endif // POLYCANVAS_H

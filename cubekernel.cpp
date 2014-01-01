#include "cubekernel.h"

void CubeKernel::setTranslation(QVector3D p)
{
    viewPoint=p;
    setTranslation();
}

void CubeKernel::update()
{
    polygons.clear();
    double dx=viewportSize.width()/2.0,dy=viewportSize.height()/2.0;
    foreach(Polygon3D p,scene)
    {
        if(canSee(p))
        {
            QList<QVector3D> ce=p.renderOut(rotation,movement,aspect);
            QList<QPointF> cs;
            foreach(QVector3D e,ce)
            {
                cs.append(QPointF(e.x()*zs/e.z()+dx,e.y()*zs/e.z()+dy));
            }
            QColor pColor=p.getColor();
            float ill=illuminace(p)*75;
            if(ill>0)
            {
                polygons.append(Polygon2D(cs,p.getColor().lighter(100+ill)));
            }
            else
            {
                polygons.append(Polygon2D(cs,p.getColor().darker(100-2*ill)));
            }
        }
    }
    emit updated();
}

CubeKernel::CubeKernel(QSize s, QObject *parent) :
    PolygonKernel(s,parent)
{
    explanation="用键盘控制方块\n\nA/S/D/W/Q/E\n旋转\n\nJ/K/L/I/H/N\n平移";

    scene.append(Polygon3D({{-50,50,-50},{50,50,-50},{50,50,50},{-50,50,50}},Qt::red));
    scene.append(Polygon3D({{-50,-50,-50},{50,-50,-50},{50,-50,50},{-50,-50,50}},Qt::yellow));
    scene.append(Polygon3D({{50,-50,-50},{50,50,-50},{50,50,50},{50,-50,50}},Qt::green));
    scene.append(Polygon3D({{-50,-50,-50},{-50,50,-50},{-50,50,50},{-50,-50,50}},Qt::blue));
    scene.append(Polygon3D({{50,-50,-50},{50,50,-50},{-50,50,-50},{-50,-50,-50}},Qt::cyan));
    scene.append(Polygon3D({{50,-50,50},{50,50,50},{-50,50,50},{-50,-50,50}},Qt::magenta));

    setTranslation({0,-200,0});
    zs=260;

    rotation.rotate(45,0,0,1);
    rotation.rotate(25,1,0,0);

    update();

    connect(this,SIGNAL(reseted()),SLOT(recover()));

    rotateXY001Timer=new QTimer(this);
    rotateXY001Timer->setInterval(33);
    connect(rotateXY001Timer,&QTimer::timeout,[=]
    {
        rotation.rotate(3.6,0,0,1);
        update();
    });

    rotateXZ001Timer=new QTimer(this);
    rotateXZ001Timer->setInterval(33);
    connect(rotateXZ001Timer,&QTimer::timeout,[=]
    {
        rotation.rotate(3.6,0,1,0);
        update();
    });

    rotateYZ001Timer=new QTimer(this);
    rotateYZ001Timer->setInterval(33);
    connect(rotateYZ001Timer,&QTimer::timeout,[=]
    {
        rotation.rotate(3.6,1,0,0);
        update();
    });

    rotateXY001bTimer=new QTimer(this);
    rotateXY001bTimer->setInterval(33);
    connect(rotateXY001bTimer,&QTimer::timeout,[=]
    {
        rotation.rotate(-3.6,0,0,1);
        update();
    });

    rotateXZ001bTimer=new QTimer(this);
    rotateXZ001bTimer->setInterval(33);
    connect(rotateXZ001bTimer,&QTimer::timeout,[=]
    {
        rotation.rotate(-3.6,0,1,0);
        update();
    });

    rotateYZ001bTimer=new QTimer(this);
    rotateYZ001bTimer->setInterval(33);
    connect(rotateYZ001bTimer,&QTimer::timeout,[=]
    {
        rotation.rotate(-3.6,1,0,0);
        update();
    });

    moveX1Timer=new QTimer(this);
    moveX1Timer->setInterval(33);
    connect(moveX1Timer,&QTimer::timeout,[=]
    {
        movement.setX(movement.x()+1);
        update();
    });

    moveY1Timer=new QTimer(this);
    moveY1Timer->setInterval(33);
    connect(moveY1Timer,&QTimer::timeout,[=]
    {
        movement.setY(movement.y()+1);
        update();
    });

    moveZ1Timer=new QTimer(this);
    moveZ1Timer->setInterval(33);
    connect(moveZ1Timer,&QTimer::timeout,[=]
    {
        movement.setZ(movement.z()+1);
        update();
    });

    moveX1bTimer=new QTimer(this);
    moveX1bTimer->setInterval(33);
    connect(moveX1bTimer,&QTimer::timeout,[=]
    {
        movement.setX(movement.x()-1);
        update();
    });

    moveY1bTimer=new QTimer(this);
    moveY1bTimer->setInterval(33);
    connect(moveY1bTimer,&QTimer::timeout,[=]
    {
        movement.setY(movement.y()-1);
        update();
    });

    moveZ1bTimer=new QTimer(this);
    moveZ1bTimer->setInterval(33);
    connect(moveZ1bTimer,&QTimer::timeout,[=]
    {
        movement.setZ(movement.z()-1);
        update();
    });
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

void CubeKernel::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_A&&!rotateXY001Timer->isActive())
    {
        rotateXY001Timer->start();
    }
    else if(e->key()==Qt::Key_E&&!rotateXZ001Timer->isActive())
    {
        rotateXZ001Timer->start();
    }
    else if(e->key()==Qt::Key_S&&!rotateYZ001Timer->isActive())
    {
        rotateYZ001Timer->start();
    }
    else if(e->key()==Qt::Key_D&&!rotateXY001bTimer->isActive())
    {
        rotateXY001bTimer->start();
    }
    else if(e->key()==Qt::Key_Q&&!rotateXZ001bTimer->isActive())
    {
        rotateXZ001bTimer->start();
    }
    else if(e->key()==Qt::Key_W&&!rotateYZ001bTimer->isActive())
    {
        rotateYZ001bTimer->start();
    }
    else if(e->key()==Qt::Key_L)
    {
        moveX1Timer->start();
    }
    else if(e->key()==Qt::Key_H)
    {
        moveY1Timer->start();
    }
    else if(e->key()==Qt::Key_K)
    {
        moveZ1Timer->start();
    }
    else if(e->key()==Qt::Key_J)
    {
        moveX1bTimer->start();
    }
    else if(e->key()==Qt::Key_N)
    {
        moveY1bTimer->start();
    }
    else if(e->key()==Qt::Key_I)
    {
        moveZ1bTimer->start();
    }
}

void CubeKernel::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_A)
    {
        rotateXY001Timer->stop();
    }
    else if(e->key()==Qt::Key_E)
    {
        rotateXZ001Timer->stop();
    }
    else if(e->key()==Qt::Key_S)
    {
        rotateYZ001Timer->stop();
    }
    else if(e->key()==Qt::Key_D)
    {
        rotateXY001bTimer->stop();
    }
    else if(e->key()==Qt::Key_Q)
    {
        rotateXZ001bTimer->stop();
    }
    else if(e->key()==Qt::Key_W)
    {
        rotateYZ001bTimer->stop();
    }
    else if(e->key()==Qt::Key_L)
    {
        moveX1Timer->stop();
    }
    else if(e->key()==Qt::Key_H)
    {
        moveY1Timer->stop();
    }
    else if(e->key()==Qt::Key_K)
    {
        moveZ1Timer->stop();
    }
    else if(e->key()==Qt::Key_J)
    {
        moveX1bTimer->stop();
    }
    else if(e->key()==Qt::Key_N)
    {
        moveY1bTimer->stop();
    }
    else if(e->key()==Qt::Key_I)
    {
        moveZ1bTimer->stop();
    }
}

void CubeKernel::recover()
{
    movement=QVector3D();
    rotation=QMatrix4x4();
    rotation.rotate(45,0,0,1);
    rotation.rotate(25,1,0,0);

    update();
}

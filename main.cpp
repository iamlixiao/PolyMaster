#include<QtWidgets>
#include"polycanvas.h"
#include"polygon3d.h"
#include"scene3d.h"
int main(int argc, char**argv)
{
    QApplication app(argc,argv);
    Polygon3D mesh;
    mesh.addVertices({{0,0,0},{50,0,0},{50,0,50},{0,0,50}});
    Polygon3D mesh2;
    mesh2.addVertices({{50,0,0},{50,0,50},{50,50,50},{50,50,0}});
    Scene3D scene;
    scene.addPolygon({mesh,mesh2});
    scene.setViewPoint({0,-100,0});
    scene.setZs(50);
    scene.renderOut();
    PolyCanvas window;
    window.show();
    return app.exec();
}

#include<QtWidgets>
#include"polycanvas.h"

int main(int argc, char**argv)
{
    QApplication app(argc,argv);
    PolyCanvas window;
    window.show();
    return app.exec();
}

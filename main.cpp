#include <QApplication>
#include <iostream>
#include "canvas.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    Canvas *canvas = new Canvas;
    
    canvas->setWindowTitle(QObject::tr("Super Pele Soccer"));
    canvas->setWindowIcon(QIcon(":/imagens/icon.jpg"));
    canvas->resize(800, 600);
    canvas->show();
    return app.exec();
}





#include "userwindow.h"
#include <QApplication>
#include "includes.h"
//#include "headers.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    userwindow w;
    w.show();

    return a.exec();
}

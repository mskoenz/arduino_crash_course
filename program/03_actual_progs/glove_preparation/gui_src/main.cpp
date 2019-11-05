// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    20.06.2013 22:46:26 EDT
// File:    main.cpp


#include "main_widget.hpp"

#include <QApplication>


int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);
    q2_main_widget w;
    return app.exec();
}

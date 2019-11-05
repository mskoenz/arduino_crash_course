// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    21.06.2013 19:08:29 EDT
// File:    global.hpp

#ifndef __GLOBAL_HEADER
#define __GLOBAL_HEADER

#include <QtGui>

#include <logic.hpp>

class global_class: public QObject {
    Q_OBJECT
public slots:
    bool connected() {
        return logic.connected();
    }
};

extern global_class global;

#endif //__GLOBAL_HEADER

// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.07.2013 20:39:29 EDT
// File:    drop_button.hpp

#ifndef __DROP_BUTTON_HEADER
#define __DROP_BUTTON_HEADER

#include <QtGui>
#include <QtCore>
#include <algorithm>
#include <logic.hpp>

class drop_button : public QPushButton {
public:
    drop_button(QWidget *parent = NULL);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void set_id(id_type const & id);
    void set_new_id(int const & old_id, int const & new_id);
private:
    id_type id_;
};

#endif //__DROP_BUTTON_HEADER

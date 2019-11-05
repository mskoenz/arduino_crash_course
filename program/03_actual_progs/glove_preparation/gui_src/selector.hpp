// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.07.2013 20:43:06 EDT
// File:    selector.hpp

#ifndef __SELECTOR_HEADER
#define __SELECTOR_HEADER

#include "drop_button.hpp"
#include <QtGui>
#include <QtCore>
#include <algorithm>
#include <iostream>

class color_buffer {
public:
    color_buffer(): count_(0), max_(10), col_(10) {
        col_[0] = "Red";
        col_[1] = "Green";
        col_[2] = "Blue";
        col_[3] = "Orange";
        col_[4] = "Cyan";
        col_[5] = "Purple";
        col_[6] = "Gray";
        col_[7] = "Black";
        col_[8] = "Magenta";
        col_[9] = "Yellow";
    }
    QString operator()(id_type const & id) {
        return col_[id % max_];
    }
private:
    int count_;
    int max_;
    std::vector<QString> col_;
};

class selector: public QWidget {
Q_OBJECT
public:
    selector(QWidget * parent, id_type const & id);
    void setParent(QWidget * parent = NULL);
    void drop_handler(id_type const & id, QPoint const & p);
    void set_geometry(val_type & x_low, val_type & x_high, val_type & y_low, val_type & y_high);
    
    void raise();
    void lower();
    void hide();
    void show();
    void update();
    
    void mousePressEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    static int size;
    std::vector<drop_button> btn_;
    static id_type count;
    
signals:
    void selected(int const & id); 

public:
    id_type id_;
private:
    val_type * x_low_;
    val_type * x_high_;
    val_type * y_low_;
    val_type * y_high_;
    
};


#endif //__SELECTOR_HEADER

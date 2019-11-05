// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.07.2013 17:32:41 EDT
// File:    selector.cpp

#include "selector.hpp"
#include <vector>
#include <iostream>

int selector::size = 8;

color_buffer get_color;



selector::selector(QWidget * parent, id_type const & id): btn_(4)
                                                        , id_(id)
                                                        , x_low_(NULL)
                                                        , x_high_(NULL)
                                                        , y_low_(NULL)
                                                        , y_high_(NULL)
                                                         {
    std::for_each(btn_.begin(), btn_.end(), 
        [&](drop_button & b) {
            b.set_id(4*id + (count++)%4);
        }
    );
    setMouseTracking(true);
    setParent(parent);
}
void selector::setParent(QWidget * parent) {
    std::for_each(btn_.begin(), btn_.end(), 
        [&](drop_button & b) {
            b.setParent(parent);
            b.show();
        }
    );
    ((QWidget*)this)->setParent(parent);
}
void selector::set_geometry(val_type & x_low, val_type & x_high, val_type & y_low, val_type & y_high) {
    x_low_ = &x_low;
    x_high_ = &x_high;
    y_low_ = &y_low;
    y_high_ = &y_high;
    
    btn_[0].setGeometry(x_low , y_low , size, size);
    btn_[1].setGeometry(x_high - size, y_low, size, size);
    btn_[2].setGeometry(x_high - size, y_high - size, size, size);
    btn_[3].setGeometry(x_low, y_high - size, size, size);
    
    ((QWidget*)this)->setGeometry(x_low, y_low, x_high - x_low, y_high - y_low);
    
    QColor color(get_color(id_));
    color.setAlphaF(.2);
    
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, color);
    setAutoFillBackground(true);
    setPalette(Pal);
    show();
    
}
void selector::hide() {
    QWidget::hide();
    std::for_each(btn_.begin(), btn_.end(), 
        [&](drop_button & b) {
            b.hide();
        }
    );
}
void selector::show() {
    QWidget::show();
    std::for_each(btn_.begin(), btn_.end(), 
        [&](drop_button & b) {
            b.show();
        }
    );
}

void selector::drop_handler(id_type const & id, QPoint const & p) {
    btn_[id].move(std::max(0, p.x()) - size / 2, std::max(0, p.y()) - size / 2);
    
    if(id % 2 == 0) {
        btn_[id + 1].move(btn_[id + 1].x(), btn_[id].y());
        btn_[(id + 4 - 1) % 4].move(btn_[id].x(), btn_[(id + 4 - 1) % 4].y());
    } else {
        btn_[(id + 1) % 4].move(btn_[id].x(), btn_[(id + 1) % 4].y());
        btn_[id - 1].move(btn_[id - 1].x(), btn_[id].y());
    }
    
    *x_high_ = 0;
    *y_high_ = 0;
    *x_low_ = 255;
    *y_low_ = 255;
    
    std::for_each(btn_.begin(), btn_.end(), 
        [&](drop_button & b) {
            *x_high_ = std::max((int)*x_high_, b.x());
            *y_high_ = std::max((int)*y_high_, b.y());
            *x_low_ = std::min((int)*x_low_, b.x());
            *y_low_ = std::min((int)*y_low_, b.y());
        }
    );
    
    *x_high_ += size;
    *y_high_ += size;
    
    ((QWidget*)this)->setGeometry(*x_low_, *y_low_, *x_high_ - *x_low_, *y_high_ - *y_low_);
    
}
void selector::raise() {
    ((QWidget*)this)->raise();
    std::for_each(btn_.begin(), btn_.end(), 
        [&](drop_button & b) {
            b.raise();
        }
    );
}
void selector::lower() {
    ((QWidget*)this)->lower();
    std::for_each(btn_.begin(), btn_.end(), 
        [&](drop_button & b) {
            b.lower();
        }
    );
}
void selector::update() {
    btn_[0].move(*x_low_ , *y_low_);
    btn_[1].move(*x_high_ - size, *y_low_);
    btn_[2].move(*x_high_ - size, *y_high_ - size);
    btn_[3].move(*x_low_ , *y_high_ - size);
    
    ((QWidget*)this)->setGeometry(*x_low_, *y_low_, *x_high_ - *x_low_, *y_high_ - *y_low_);
}

void selector::mousePressEvent(QMouseEvent *event) {
    if(event->buttons() == Qt::RightButton)
        lower();
    
    if(event->buttons() == Qt::LeftButton) {
        raise();
        emit selected(id_);
    }
}
void selector::enterEvent(QEvent *event) {
    Q_UNUSED(event)
}

id_type selector::count = 0;



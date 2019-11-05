// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    20.06.2013 22:41:50 EDT
// File:    canvas.hpp

#ifndef __Q2_MAIN_WIDGET_HEADER
#define __Q2_MAIN_WIDGET_HEADER

#include "selector.hpp"

#include <QtGui>
#include <QtCore>
#include <vector>
#include <unordered_map>
#include <memory>
#include <iostream>

class canvas: public QWidget {
    Q_OBJECT
    public:
        canvas(QWidget *parent = NULL);
        void add_gesture(id_type const & id, val_type & x_low, val_type & x_high, val_type & y_low, val_type & y_high);
        void set_sensor(std::vector<QPoint> & sen);
        void update_sensor();
            
        void dragEnterEvent(QDragEnterEvent *event);
        void dropEvent(QDropEvent *event);
        void paintEvent(QPaintEvent *e);
        
        void swap(id_type const & i1, id_type const & i2);
    public slots:
        void hide_gesture(int const & id);
        void show_gesture(int const & id);
        void remove_gesture(int const & id);
        void update_gesture(int const & id);
        void raise_gesture(int const & id);
    signals:
        void selectionChanged(int const & id);
    
    private slots:
        void emitSelectionChanged(int const & id);
    private:
        std::unordered_map<id_type, std::shared_ptr<selector>> sel_;
        std::vector<QPoint> * sen_;
        QGridLayout grid_;
};


#endif //__Q2_MAIN_WIDGET_HEADER

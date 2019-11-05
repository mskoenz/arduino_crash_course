// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    20.06.2013 22:46:34 EDT
// File:    canvas.cpp

#include "canvas.hpp"
#include "setup.hpp"

#include <iostream>
#include <algorithm>

canvas::canvas(QWidget *parent): 
      QWidget(parent)
    {
    setAcceptDrops(true);
    
    setWindowTitle("canvas");
    
    setGeometry(100, 100, 300, 300);
    setMinimumSize(256, 256);
    setMaximumSize(256, 256);
    
    
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, QColor(canvas_background));
    setAutoFillBackground(true);
    setPalette(Pal);
}
void canvas::add_gesture(id_type const & id, val_type & x_low, val_type & x_high, val_type & y_low, val_type & y_high) {
    sel_[id] = std::shared_ptr<selector>(new selector(this, id));
    sel_[id]->set_geometry(x_low, x_high, y_low, y_high);
    
    connect(&(*sel_[id]), SIGNAL(selected(int)), this, SLOT(emitSelectionChanged(int)));
    
    sel_[id]->raise();
}
void canvas::set_sensor(std::vector<QPoint> & sen) {
    sen_ = &sen;
}
void canvas::update_sensor() {
    repaint();
}

void canvas::hide_gesture(int const & id) {
    sel_[id]->hide();
}
void canvas::show_gesture(int const & id) {
    sel_[id]->show();
}
void canvas::remove_gesture(int const & id) {
    sel_.erase(id);
    
}
void canvas::update_gesture(int const & id) {
    sel_[id]->update();
}
void canvas::raise_gesture(int const & id) {
    if(id != -1)
        sel_[id]->raise();
}
void canvas::dragEnterEvent(QDragEnterEvent *event) {
    //~ for(uint i = 0; i < event->mimeData()->formats().size(); ++i) {
        //~ QString n1 = event->mimeData()->formats()[i];
        //~ std::cout << n1.toStdString() << "  ";
        //~ QByteArray itemData = event->mimeData()->data(n1);
        //~ QDataStream dStr(&itemData, QIODevice::ReadOnly);
        
        //~ while(dStr.atEnd() != true) {
            //~ char c[1];
            //~ uint i = 1;
            //~ dStr.readRawData(c, i);
            //~ std::cout << c[0];
        //~ }
    //~ }
    
    if(event->mimeData()->hasFormat("point")) {
        event->acceptProposedAction();
    }
}
void canvas::dropEvent(QDropEvent *event) {
    QPoint pos = event->pos();
    QPoint dif;
    int sel_id, btn_id;
    
    QByteArray itemData = event->mimeData()->data("point");
    QDataStream dStr(&itemData, QIODevice::ReadOnly);
    dStr>>dif;
    dStr>>sel_id;
    dStr>>btn_id;
    
    sel_[sel_id]->drop_handler(btn_id, pos);
    repaint();
}

void canvas::paintEvent(QPaintEvent *e) {
    Q_UNUSED(e);
    
    QPainter painter(this);
    painter.setPen(QColor(canvas_line));
    painter.setBrush(QBrush(canvas_brush));
    painter.drawPolyline(sen_->data(), sen_->size());
    painter.drawEllipse(sen_->front(), 2, 2);
}

void canvas::swap(id_type const & i1, id_type const & i2) {
    //swap color
    QPalette temp(sel_[i1]->palette());
    sel_[i1]->setPalette(sel_[i2]->palette());
    sel_[i2]->setPalette(temp);
    //swap only pointer
    
    std::for_each(sel_[i1]->btn_.begin(), sel_[i1]->btn_.end(), 
        [&](drop_button & b) {
            b.set_new_id(sel_[i1]->id_, sel_[i2]->id_);
        }
    );
    std::for_each(sel_[i2]->btn_.begin(), sel_[i2]->btn_.end(), 
        [&](drop_button & b) {
            b.set_new_id(sel_[i2]->id_, sel_[i1]->id_);
        }
    );
    auto temp2 = sel_[i1]->id_;
    sel_[i1]->id_ = sel_[i2]->id_;
    sel_[i2]->id_ = temp2;
    
    sel_[i1].swap(sel_[i2]);
    
    
    update();
}

void canvas::emitSelectionChanged(int const & id) {
    emit selectionChanged(id);
}

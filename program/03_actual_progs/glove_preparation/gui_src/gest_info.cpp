// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.08.2013 17:00:59 CEST
// File:    gest_info.cpp

#include <gest_info.hpp>

q2_gest_info_widget::q2_gest_info_widget(QWidget *parent): QWidget(parent)
                                                         , id_(-1)
                                                         , id_box_(this)
                                                         {
    grid_.addWidget(&id_box_ , 0, 0, 1, 1);
    
    id_box_.setRange(0, 31);
    
    setLayout(&grid_);
    show();
    
    connect(&id_box_, SIGNAL(valueChanged(int)), this, SLOT(update_id(int)));
}

void q2_gest_info_widget::change_gest(int id) {
    if(id == -1) {
        id_ = 0;
        id_box_.setValue(250);
        return;
    }
    else {
        id_ = id;
        id_box_.setValue(logic.gest[id].id());
    }
}

void q2_gest_info_widget::update_name(QListWidgetItem * s) {
    if(s != NULL)
        logic.gest_meta[id_].name = s->text().toStdString();
}
void q2_gest_info_widget::update_id(int id) {
    if(id_ != -1)
        logic.gest[id_].id() = id;
}
void q2_gest_info_widget::set_focus(int i) {
    if(i == 0) {
        id_box_.setFocus();
        id_box_.selectAll();
    }
}

int q2_gest_info_widget::has_focus() {
    if(id_box_.hasFocus())
        return 0;
    return -1;
}

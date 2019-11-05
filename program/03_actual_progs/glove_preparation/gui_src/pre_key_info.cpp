// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    29.08.2013 16:18:21 CEST
// File:    pre_key_info.cpp

#include <pre_key_info.hpp>

q2_pre_key_info_widget::q2_pre_key_info_widget(QWidget *parent): QGroupBox("prekey", parent)
                                                         , id_(-1)
                                                         , id_box_(this)
                                                         , key_box_(this)
                                                         , mod_box_(this)
                                                         , acc_box_(this)
                                                         {
    grid_.addWidget(&id_box_ , 0, 0, 1, 1);
    grid_.addWidget(&key_box_, 1, 0, 1, 1);
    grid_.addWidget(&mod_box_, 2, 0, 1, 1);
    grid_.addWidget(&acc_box_, 3, 0, 1, 1);
    
    id_box_.setRange(0, 31);
    
    setLayout(&grid_);
    show();
    
    QStringList keys;
    for(auto it = logic.key_map.begin(); it != logic.key_map.end(); ++it)
        keys << QString(it->first.c_str());
    QCompleter * q1 = new QCompleter(keys, this);
    key_box_.setCompleter(q1);
    
    QStringList mods;
    for(auto it = logic.mod_map.begin(); it != logic.mod_map.end(); ++it)
        mods << QString(it->first.c_str());
    QCompleter * q2 = new QCompleter(mods, this);
    mod_box_.setCompleter(q2);
    
    QStringList accs;
    for(auto it = logic.acc_map.begin(); it != logic.acc_map.end(); ++it)
        accs << QString(it->first.c_str());
    QCompleter * q3 = new QCompleter(accs, this);
    acc_box_.setCompleter(q3);
    
    
    connect(&id_box_, SIGNAL(valueChanged(int)), this, SLOT(update_id(int)));
    connect(&key_box_, SIGNAL(textChanged(QString)), this, SLOT(update_key(QString)));
    connect(&mod_box_, SIGNAL(textChanged(QString)), this, SLOT(update_mod(QString)));
    connect(&acc_box_, SIGNAL(textChanged(QString)), this, SLOT(update_acc(QString)));
}

void q2_pre_key_info_widget::change_key(int id) {
    if(id == -1) {
        id_ = 0;
        id_box_.setValue(0);
        key_box_.setText("no key");
        mod_box_.setText("no mod");
        acc_box_.setText("all");
        return;
    }
    else {
        id_ = id;
        id_box_.setValue(logic.key_meta[id].pre_id);
        key_box_.setText(QString(logic.key_meta[id].pre_key.c_str()));
        mod_box_.setText(QString(logic.key_meta[id].pre_mod.c_str()));
        acc_box_.setText(QString(logic.key_meta[id].pre_acc.c_str()));
    }
}
void q2_pre_key_info_widget::update_id(int _id) {
    if(id_ != -1)
        logic.key_meta[id_].pre_id = _id;
}
void q2_pre_key_info_widget::update_key(QString s) {
    if(id_ != -1)
        logic.key_meta[id_].pre_key = s.toStdString();
}
void q2_pre_key_info_widget::update_mod(QString s) {
    if(id_ != -1)
        logic.key_meta[id_].pre_mod = s.toStdString();
}
void q2_pre_key_info_widget::update_acc(QString s) {
    if(id_ != -1)
        logic.key_meta[id_].pre_acc = s.toStdString();
}

void q2_pre_key_info_widget::set_focus(int i) {
    if(i == 0) {
        id_box_.setFocus();
        id_box_.selectAll();
    }
    else if(i == 1) {
        key_box_.setFocus();
        key_box_.selectAll();
    }
    else if(i == 2) {
        mod_box_.setFocus();
        mod_box_.selectAll();
    }
    else if(i == 3) {
        acc_box_.setFocus();
        acc_box_.selectAll();
    }
}

int q2_pre_key_info_widget::has_focus() {
    if(id_box_.hasFocus())
        return 0;
    if(key_box_.hasFocus())
        return 1;
    if(mod_box_.hasFocus())
        return 2;
    if(acc_box_.hasFocus())
        return 3;
    return -1;
}

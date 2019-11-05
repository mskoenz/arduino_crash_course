// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    28.08.2013 11:08:40 CEST
// File:    key_info.hpp

#ifndef __KEY_INFO_HEADER
#define __KEY_INFO_HEADER

#include <logic.hpp>
#include <QtGui>

class q2_key_info_widget: public QGroupBox {
    Q_OBJECT
public:
    q2_key_info_widget(QWidget *parent = NULL);
    void set_focus(int i);
    int has_focus();
public slots:
    void change_key(int id);
    void update_name(QListWidgetItem * s);
    void update_id(int id);
    void update_key(QString s);
    void update_mod(QString s);
    void update_acc(QString s);
private:
    int id_;
    QGridLayout grid_;
    QSpinBox id_box_;
    QLineEdit key_box_;
    QLineEdit mod_box_;
    QLineEdit acc_box_;
};

#endif //__KEY_INFO_HEADER

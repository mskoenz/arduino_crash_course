// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    26.08.2013 17:00:45 CEST
// File:    gest_info.hpp

#ifndef __GEST_INFO_HEADER
#define __GEST_INFO_HEADER

#include <logic.hpp>
#include <QtGui>

class q2_gest_info_widget: public QWidget {
    Q_OBJECT
public:
    q2_gest_info_widget(QWidget *parent = NULL);
    void set_focus(int i);
    int has_focus();
public slots:
    void change_gest(int id);
    void update_name(QListWidgetItem * s);
    void update_id(int id);
private:
    int id_;
    QGridLayout grid_;
    QSpinBox id_box_;
};

#endif //__GEST_INFO_HEADER

// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.07.2013 21:09:20 EDT
// File:    main_widget.hpp

#ifndef __MAIN_WIDGET_HEADER
#define __MAIN_WIDGET_HEADER

#include "canvas.hpp"
#include "gest_info.hpp"
#include "key_info.hpp"
#include "pre_key_info.hpp"

#include <QtGui>
#include <QtCore>

#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <iostream>
#include <logic.hpp>

class q2_main_widget: public QMainWindow {
        Q_OBJECT
    public:
        q2_main_widget(QWidget *parent = NULL);
        void timerEvent(QTimerEvent * event);
        void addGesture(id_type const & id);
        void removeGesture(id_type const & id);
        void addKey(id_type const & id);
        void removeKey(id_type const & id);
    public slots:
        void switch_timer();
        void update();
        
        void read_gest(id_type const & id);
        void read_all_gest();
        void write_gest(id_type const & id);
        void write_all_gest();
        void remove_all_gest();
        void write_to_eeprom();
        
        void load_arch();
        void save_arch();
        void quick_save_arch();
        
        void add_gest();
        void del_gest();
        void add_key();
        void del_key();
        
        void changeListSelection(int const & id);
        void checkBoxWorkAround(QListWidgetItem * item);
        void change_gest_selection(int const & row);
        void change_key_selection(int const & row);
        void del_key_or_gest();
        void add_key_or_gest();
        void shift_up();
        void shift_down();
        void tab_chain();
    private:
        std::vector<canvas> cvs_;
        QGridLayout grid_;
        QLabel freq_lbl_;
        
        QListWidget gest_list_;
        QPushButton add_gest_;
        QPushButton del_gest_;
        q2_gest_info_widget gest_info_;
        
        QListWidget key_list_;
        QPushButton add_key_;
        QPushButton del_key_;
        q2_key_info_widget key_info_;
        q2_pre_key_info_widget pre_key_info_;
        
        int timer_id_;
        
        QString path_name_;
};

#endif //__MAIN_WIDGET_HEADER

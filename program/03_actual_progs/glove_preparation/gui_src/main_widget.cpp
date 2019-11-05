// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.07.2013 21:09:23 EDT
// File:    main_widget.cpp

#include "main_widget.hpp"
#include "setup.hpp"

#include <sstream>
#include <chrono>

val_type y1_ = 100;
val_type y2_ = 156;
id_type id = 0;

std::vector<val_type> gest = {10, 100, 10, 100, 
                              10, 100, 10, 100, 
                              10, 100, 10, 100, 
                              10, 100, 10, 100, 
                              10, 100, 50, 60};

std::vector<std::vector<QPoint>> sen(5, std::vector<QPoint>(n_follow, QPoint(50, 50)));

extern color_buffer get_color;

q2_main_widget::q2_main_widget(QWidget *parent): QMainWindow(parent)
                                              , cvs_(5)
                                              , freq_lbl_(this)
                                              
                                              , gest_list_(this)
                                              , add_gest_("add", this)
                                              , del_gest_("delete", this)
                                              , gest_info_(this)
                                              
                                              , key_list_(this)
                                              , add_key_("add", this)
                                              , del_key_("delete", this)
                                              , key_info_(this)
                                              , pre_key_info_(this)
                                              
                                              , timer_id_(-1)
                                              , path_name_("untitled.hex")
                                              {
    
//------------------- set parents -------------------
    for(uint i = 0; i < cvs_.size(); ++i) {
        cvs_[i].setParent(this);
        cvs_[i].set_sensor(sen[i]);
    }
    
//------------------- layout -------------------
    
    QWidget * element6 = new QWidget(this);
    QGridLayout * element6_l = new QGridLayout();
    
    element6_l->addWidget(&gest_list_, 0, 0, 2, 2);
    element6_l->addWidget(&add_gest_,  2, 0, 1, 1);
    element6_l->addWidget(&del_gest_,  2, 1, 1, 1);
    
    element6_l->addWidget(&gest_info_, 0, 2, 1, 1);
    element6_l->addWidget(&freq_lbl_,  2, 2, 1, 1);
    
    element6->setLayout(element6_l);
    
    QWidget * element7 = new QWidget(this);
    QGridLayout * element7_l = new QGridLayout();
    
    element7_l->addWidget(&pre_key_info_, 0, 0, 1, 1);
    element7_l->addWidget(&key_info_,  0, 1, 1, 1);
    element7_l->addWidget(&key_list_,  1, 0, 2, 2);
    element7_l->addWidget(&add_key_,   3, 0, 1, 1);
    element7_l->addWidget(&del_key_,   3, 1, 1, 1);
    
    element7->setLayout(element7_l);
    
    grid_.addWidget(&cvs_[0], 0, 0, 1, 1);
    grid_.addWidget(&cvs_[1], 0, 1, 1, 1);
    grid_.addWidget(&cvs_[2], 0, 2, 1, 1);
    grid_.addWidget(&cvs_[3], 1, 0, 1, 1);
    grid_.addWidget(&cvs_[4], 1, 1, 1, 1);
    grid_.addWidget(element6, 1, 2, 1, 1);
    grid_.addWidget(element7, 0, 3, 2, 1);
    
    grid_.setRowStretch(10, 1);
    grid_.setColumnStretch(10, 1);
    
//------------------- menubar -------------------
    QMenuBar * menu = new QMenuBar(this);
    QMenu * main_m = new QMenu("file", this);
    
    main_m->addAction("open", this, SLOT(load_arch()),            QKeySequence(Qt::CTRL + Qt::Key_O));
    main_m->addAction("save", this, SLOT(quick_save_arch()),      QKeySequence(Qt::CTRL + Qt::Key_S));
    main_m->addAction("save as..", this, SLOT(save_arch()),       QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));
    main_m->addAction("close", this, SLOT(close()),               QKeySequence(Qt::CTRL + Qt::Key_Q));
    
    QMenu * dg_m = new QMenu("data glove", this);
    dg_m->addAction("download", this, SLOT(read_all_gest()),      QKeySequence(Qt::CTRL + Qt::Key_D));
    dg_m->addAction("upload", this, SLOT(write_all_gest()),       QKeySequence(Qt::CTRL + Qt::Key_U));
    dg_m->addAction("EEPROM save", this, SLOT(write_to_eeprom()));
    dg_m->addAction("toggle live", this, SLOT(switch_timer()),    QKeySequence(Qt::Key_S));
    
    
    menu->addMenu(main_m);
    menu->addMenu(dg_m);
    
    QWidget * proxi = new QWidget(this);
    proxi->setLayout(&grid_);
    
    setMenuBar(menu);
    setCentralWidget(proxi);
    setGeometry(10, 10, 300, 300);
    setWindowTitle(path_name_);
    show();
    
//------------------- divers -------------------
    
    std::cout << "wait" << std::endl;
    usleep(1000lu*1600);
    std::cout << "go" << std::endl;
    //~ switch_timer();
    
    //~ load_arch();
    //~ read_all_gest();
//------------------- connects -------------------
    
    for(uint i = 0; i < cvs_.size(); ++i) {
        connect(&gest_list_, SIGNAL(currentRowChanged(int)), &cvs_[i], SLOT(raise_gesture(int)));
        connect(&cvs_[i], SIGNAL(selectionChanged(int)), this, SLOT(changeListSelection(int)));
    }
    connect(&gest_list_, SIGNAL(currentRowChanged(int)), &gest_info_, SLOT(change_gest(int)));
    connect(&gest_list_, SIGNAL(itemChanged(QListWidgetItem *)), this, SLOT(checkBoxWorkAround(QListWidgetItem *)));
    connect(&gest_list_, SIGNAL(itemChanged(QListWidgetItem *)), &gest_info_, SLOT(update_name(QListWidgetItem *)));
    connect(&gest_list_, SIGNAL(currentRowChanged(int)), this, SLOT(change_key_selection(int)));
    
    connect(&key_list_, SIGNAL(currentRowChanged(int)), &key_info_, SLOT(change_key(int)));
    connect(&key_list_, SIGNAL(currentRowChanged(int)), &pre_key_info_, SLOT(change_key(int)));
    connect(&key_list_, SIGNAL(itemChanged(QListWidgetItem *)), &key_info_, SLOT(update_name(QListWidgetItem *)));
    connect(&key_list_, SIGNAL(currentRowChanged(int)), this, SLOT(change_gest_selection(int)));
    
//------------------- button connects -------------------
    
    connect(&add_gest_, SIGNAL(pressed()), this, SLOT(add_gest()));
    connect(&del_gest_, SIGNAL(pressed()), this, SLOT(del_gest()));
    
    connect(&add_key_, SIGNAL(pressed()), this, SLOT(add_key()));
    connect(&del_key_, SIGNAL(pressed()), this, SLOT(del_key()));
//------------------- key connects -------------------
    connect(&del_gest_, SIGNAL(pressed()), this, SLOT(del_gest()));
    connect(new QShortcut(QKeySequence(Qt::Key_Backspace), this), SIGNAL(activated()), this, SLOT(del_key_or_gest()));
    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_1), this), SIGNAL(activated()), this, SLOT(add_key_or_gest()));
    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Right), this), SIGNAL(activated()), &key_list_, SLOT(setFocus()));
    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Left), this), SIGNAL(activated()), &gest_list_, SLOT(setFocus()));
    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Up), this), SIGNAL(activated()), this, SLOT(shift_up()));
    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Down), this), SIGNAL(activated()), this, SLOT(shift_down()));
    connect(new QShortcut(QKeySequence(Qt::Key_Tab), this), SIGNAL(activated()), this, SLOT(tab_chain()));
}

//=================== event handler ===================
void q2_main_widget::checkBoxWorkAround(QListWidgetItem * item) {
    if(item->checkState() == Qt::Checked) {
        for(uint i = 0; i < cvs_.size(); ++i)
            cvs_[i].show_gesture(gest_list_.row(item));
    }
    else {
        for(uint i = 0; i < cvs_.size(); ++i)
            cvs_[i].hide_gesture(gest_list_.row(item));
    }
}
void q2_main_widget::changeListSelection(int const & id) {
    gest_list_.setCurrentRow(id);
}
void q2_main_widget::change_gest_selection(int const & row) {
    uint8_t & id = logic.key_meta[row].id;
    
    gest_list_.clearSelection();
    for(uint i = 0; i < logic.n_gest; ++i) {
        if(logic.gest[i].id() == id) {
            gest_list_.setCurrentRow(i);
            break;
        }
    }
    
}
void q2_main_widget::change_key_selection(int const & row) {
    uint8_t & id = logic.gest[row].id();
    
    key_list_.clearSelection();
    for(uint i = 0; i < logic.n_keys; ++i) {
        if(logic.key_meta[i].id == id) {
            key_list_.setCurrentRow(i);
            break;
        }
    }
    
}
void q2_main_widget::del_key_or_gest() {
    if(gest_list_.hasFocus()) {
        del_gest();
        return;
    }
    if(key_list_.hasFocus()) {
        del_key();
        return;
    }
}
void q2_main_widget::add_key_or_gest() {
    if(gest_list_.hasFocus()) {
        add_gest();
        return;
    }
    if(key_list_.hasFocus()) {
        add_key();
        return;
    }
}
void q2_main_widget::shift_up() {
    if(gest_list_.hasFocus()) {
        id_type row = gest_list_.currentRow();
        if(row != 0) {
            std::swap(logic.gest_meta[row], logic.gest_meta[row - 1]);
            std::swap(logic.gest[row], logic.gest[row - 1]);
            
            for(uint i = 0; i < cvs_.size(); ++i)
                cvs_[i].swap(row, row - 1);
            
            QString temp = gest_list_.item(row - 1)->text();
            gest_list_.item(row - 1)->setText(gest_list_.item(row)->text());
            gest_list_.item(row)->setText(temp);
            
            auto temp2 = gest_list_.item(row)->checkState();
            gest_list_.item(row)->setCheckState(gest_list_.item(row - 1)->checkState());
            gest_list_.item(row - 1)->setCheckState(temp2);
            
            gest_list_.setCurrentRow(row - 1);
        }
        return;
    }
    if(key_list_.hasFocus()) {
        id_type row = key_list_.currentRow();
        if(row != 0) {
            std::swap(logic.key_meta[row], logic.key_meta[row - 1]);
            
            QString temp = key_list_.item(row - 1)->text();
            key_list_.item(row - 1)->setText(key_list_.item(row)->text());
            key_list_.item(row)->setText(temp);
            
            key_list_.setCurrentRow(row - 1);
        }
        return;
    }
    
}
void q2_main_widget::shift_down() {
    if(gest_list_.hasFocus()) {
        id_type row = gest_list_.currentRow();
        if(row != logic.n_gest - 1) {
            
            std::swap(logic.gest_meta[row], logic.gest_meta[row + 1]);
            std::swap(logic.gest[row], logic.gest[row + 1]);
            
            for(uint i = 0; i < cvs_.size(); ++i)
                cvs_[i].swap(row, row + 1);
            
            QString temp = gest_list_.item(row + 1)->text();
            gest_list_.item(row + 1)->setText(gest_list_.item(row)->text());
            gest_list_.item(row)->setText(temp);
            
            auto temp2 = gest_list_.item(row)->checkState();
            gest_list_.item(row)->setCheckState(gest_list_.item(row + 1)->checkState());
            gest_list_.item(row + 1)->setCheckState(temp2);
            
            gest_list_.setCurrentRow(row + 1);
        }
        return;
    }
    if(key_list_.hasFocus()) {
        id_type row = key_list_.currentRow();
        if(row != logic.n_keys - 1) {
            std::swap(logic.key_meta[row], logic.key_meta[row + 1]);
            
            QString temp = key_list_.item(row + 1)->text();
            key_list_.item(row + 1)->setText(key_list_.item(row)->text());
            key_list_.item(row)->setText(temp);
            
            key_list_.setCurrentRow(row + 1);
        }
        return;
    }
    
}
void q2_main_widget::tab_chain() {
    if(key_list_.hasFocus()) {
        key_info_.set_focus(0);
        return;
    }
    if(key_info_.has_focus() == 0) {
        key_info_.set_focus(1);
        return;
    }
    if(key_info_.has_focus() == 1) {
        key_info_.set_focus(2);
        return;
    }
    if(key_info_.has_focus() == 2) {
        key_info_.set_focus(3);
        return;
    }
    if(key_info_.has_focus() == 3) {
        key_list_.setFocus();
        return;
    }
    if(gest_list_.hasFocus()) {
        gest_info_.set_focus(0);
        return;
    }
    if(gest_info_.has_focus() == 0) {
        gest_list_.setFocus();
        return;
    }
}

//=================== timer ===================
std::chrono::high_resolution_clock::time_point t1;
std::chrono::high_resolution_clock::time_point t2;
ustd::filter<int, ustd::tag::hysteresis<2>, ustd::tag::lowpass<100>> freq;
void q2_main_widget::timerEvent(QTimerEvent * event) {
    Q_UNUSED(event)
    
    t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t1 - t2);
    freq << 1/time_span.count();
    update();
    freq_lbl_.setNum(freq);
    t2 = t1;
}
void q2_main_widget::switch_timer() {
    if(timer_id_ == -1) {
        timer_id_ = startTimer(timer_period);
    }
    else {
        killTimer(timer_id_);
        timer_id_ = -1;
    }
}

//=================== read write ===================
void q2_main_widget::read_gest(id_type const & id) {
    logic.read_gest(id);
}
void q2_main_widget::read_all_gest() {
    std::cout << path_name_.toStdString() << std::endl;
    remove_all_gest();
    logic.read_all_gest();
    logic.read_all_keys();
    
    for(uint i = 0; i < logic.n_gest; ++i) {
        addGesture(i);
    }
    for(uint i = 0; i < logic.n_keys; ++i) {
        addKey(i);
    }
    
    path_name_ = "download.hex";
    setWindowTitle(path_name_);
}
void q2_main_widget::write_gest(id_type const & id) {
    logic.write_gest(id);
}
void q2_main_widget::write_all_gest() {
    logic.write_all_gest();
    logic.write_all_keys();
    write_to_eeprom();
}
void q2_main_widget::write_to_eeprom() {
    logic.send_cmd(core::write_to_eeprom);
    std::cout << "written to EEPROM" << std::endl;
}

//=================== archive ===================
void q2_main_widget::remove_all_gest() {
    
    gest_list_.clearSelection();
    key_list_.clearSelection();
    
    for(int id = logic.n_gest - 1; id >= 0; --id)
        removeGesture(id);
    
    logic.n_gest = 0;
    
    for(int id = logic.n_keys - 1; id >= 0; --id)
        removeKey(id);
    
    logic.n_keys = 0;
    
    std::cout << "deleted all" << std::endl;
    path_name_ = "untitled.hex";
    setWindowTitle(path_name_);
}
void q2_main_widget::load_arch() {
    QString path_name = QFileDialog::getOpenFileName(this, "Open Archive", "", "Files(*.hex)");
    if(path_name != "") {
        remove_all_gest();
        path_name_ = path_name;
        logic.read_archive(path_name_.toStdString());
        
        for(uint i = 0; i < logic.n_gest; ++i)
            addGesture(i);
        
        for(uint i = 0; i < logic.n_keys; ++i)
            addKey(i);
        
        setWindowTitle(path_name_);
    }
}
void q2_main_widget::save_arch() {
    QString path_name = QFileDialog::getSaveFileName(this, "Save Archive", "", "Files(*.hex)");
    if(path_name != "") {
        path_name_ = path_name;
        logic.write_archive(path_name_.toStdString());
        std::cout << "saved" << std::endl;
    }
}
void q2_main_widget::quick_save_arch() {
    if(path_name_ != "") {
        logic.write_archive(path_name_.toStdString());
        std::cout << "saved" << std::endl;
    }
}

//=================== add delete key/gest ===================
void q2_main_widget::addGesture(id_type const & id) {
    cvs_[0].add_gesture(id, logic.gest[id].low()[0], logic.gest[id].high()[0], y1_, y2_);
    for(uint i = 1; i < cvs_.size(); ++i) {
        cvs_[i].add_gesture(  id
                            , logic.gest[id].low()[2*i - 1]
                            , logic.gest[id].high()[2*i - 1]
                            , logic.gest[id].low()[2*i]
                            , logic.gest[id].high()[2*i]
                            );
    }
    QListWidgetItem* item =new QListWidgetItem(logic.gest_meta[id].name.c_str());
    item->setForeground(QColor(get_color(id)));
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
    item->setCheckState(Qt::Checked);
    
    gest_list_.addItem(item);
}
void q2_main_widget::removeGesture(id_type const & id) {
    for(uint i = 0; i < cvs_.size(); ++i) {
        cvs_[i].remove_gesture(id);
        cvs_[i].update();
    }
    auto del = gest_list_.takeItem(id);
    delete del;
}
void q2_main_widget::addKey(id_type const & id) {
    QListWidgetItem* item =new QListWidgetItem(logic.key_meta[id].name.c_str());
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    
    key_list_.addItem(item);
}
void q2_main_widget::removeKey(id_type const & id) {
    auto del = key_list_.takeItem(id);
    delete del;
}

void q2_main_widget::add_gest() {
    if(logic.n_gest < core::max_gest) {
        int row = gest_list_.currentRow();
        if(row != -1)
            logic.gest[logic.n_gest] = logic.gest[row];
        addGesture(logic.n_gest);
        ++logic.n_gest;
    }
}
void q2_main_widget::del_gest() {
    if(logic.n_gest > 0 and gest_list_.currentRow() != -1) {
        for(uint i = gest_list_.currentRow() + 1; i < logic.n_gest; ++i) {
            logic.gest[i - 1] = logic.gest[i];
            logic.gest_meta[i - 1] = logic.gest_meta[i];
            gest_list_.item(i - 1)->setText(gest_list_.item(i)->text());
        }
        --logic.n_gest;
        
        logic.gest[logic.n_gest] = gesture_class();
        logic.gest_meta[logic.n_gest] = gest_meta_struct();
        removeGesture(logic.n_gest);
        
    }
}
void q2_main_widget::add_key() {
    if(logic.n_keys < keyop::max_keys) {
        addKey(logic.n_keys);
        ++logic.n_keys;
    }
}
void q2_main_widget::del_key() {
    if(logic.n_keys > 0 and key_list_.currentRow() != -1) {
        for(uint i = key_list_.currentRow() + 1; i < logic.n_keys; ++i) {
            logic.key_meta[i - 1] = logic.key_meta[i];
            key_list_.item(i - 1)->setText(key_list_.item(i)->text());
        }
        --logic.n_keys;
        
        logic.key_meta[logic.n_keys] = key_meta_struct();
        removeKey(logic.n_keys);
        
    }
}

//=================== update ===================
void q2_main_widget::update() {
//------------------- update sensor position and tail -------------------
    logic.raw_value();
    
    for(size_t j = n_follow - 1; j > 0; --j) {
        sen[0][j] = sen[0][j - 1];
        sen[0][j].ry() += 2;
    }
    for(size_t i = 1; i < sen.size(); ++i)
        for(size_t j = n_follow - 1; j > 0; --j)
            sen[i][j] = sen[i][j - 1];
    
    sen[0][0] = QPoint(logic.sen[0], 128);
    for(uint i = 1; i < sen.size(); ++i) {
        sen[i][0] = QPoint(logic.sen[2*i - 1], logic.sen[2*i]);
    }
    for(uint i = 0; i < cvs_.size(); ++i) {
        cvs_[i].update_sensor();
    }
}

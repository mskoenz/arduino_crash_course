// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.07.2013 20:39:38 EDT
// File:    drop_button.cpp

#include "drop_button.hpp"


drop_button::drop_button(QWidget *parent): QPushButton(parent), id_(0) {
    //~ QPushButton::mousePressEvent(event);
}
void drop_button::set_id(id_type const & id) {
    id_ = id;
}
void drop_button::set_new_id(int const & old_id, int const & new_id) {
    id_ = id_ - 4*old_id + 4*new_id;
}

void drop_button::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    //~ QPushButton::mousePressEvent(event);    
}

void drop_button::mouseMoveEvent(QMouseEvent *event) {
    if(event->buttons() != Qt::LeftButton)
        return;
    
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData();
    
    QByteArray itemData;
    QDataStream dStr(&itemData, QIODevice::WriteOnly);
    dStr << event->pos();
    dStr << (int)id_/4;
    dStr << (int)id_%4;
    dStr << "\n";
    
    mimeData->setData("point", itemData);
    
    //~ std::vector<QString> mimeName = {"-51:-27:70:54me-icon-list", "text/uri-list", "UTF8_STRING", "text/plain", "COMPOUND_TEXT", "TEXT", "STRING", "text/plain;charset=utf-8"};
    
    //~ for(uint i = 0; i < mimeName.size(); ++i) {
        //~ QByteArray fileData = "file:///home/msk/Tri_ABC-AC-AB+A.svg\n";
        //~ mimeData->setData(mimeName[i], fileData);
    //~ }
    
    drag->setMimeData(mimeData);
    //~ drag->setPixmap(QPixmap("Quelldaten/1infD.png"));
    //~ drag->setHotSpot(QPoint(31, 31));
    
    Qt::DropAction dropAction = drag->exec();
    Q_UNUSED(dropAction)
}

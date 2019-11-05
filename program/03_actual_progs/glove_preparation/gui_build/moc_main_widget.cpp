/****************************************************************************
** Meta object code from reading C++ file 'main_widget.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui_src/main_widget.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_widget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_q2_main_widget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      31,   15,   15,   15, 0x0a,
      43,   40,   15,   15, 0x0a,
      62,   15,   15,   15, 0x0a,
      78,   40,   15,   15, 0x0a,
      98,   15,   15,   15, 0x0a,
     115,   15,   15,   15, 0x0a,
     133,   15,   15,   15, 0x0a,
     151,   15,   15,   15, 0x0a,
     163,   15,   15,   15, 0x0a,
     175,   15,   15,   15, 0x0a,
     193,   15,   15,   15, 0x0a,
     204,   15,   15,   15, 0x0a,
     215,   15,   15,   15, 0x0a,
     225,   15,   15,   15, 0x0a,
     235,   40,   15,   15, 0x0a,
     265,  260,   15,   15, 0x0a,
     306,  302,   15,   15, 0x0a,
     333,  302,   15,   15, 0x0a,
     359,   15,   15,   15, 0x0a,
     377,   15,   15,   15, 0x0a,
     395,   15,   15,   15, 0x0a,
     406,   15,   15,   15, 0x0a,
     419,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_q2_main_widget[] = {
    "q2_main_widget\0\0switch_timer()\0update()\0"
    "id\0read_gest(id_type)\0read_all_gest()\0"
    "write_gest(id_type)\0write_all_gest()\0"
    "remove_all_gest()\0write_to_eeprom()\0"
    "load_arch()\0save_arch()\0quick_save_arch()\0"
    "add_gest()\0del_gest()\0add_key()\0"
    "del_key()\0changeListSelection(int)\0"
    "item\0checkBoxWorkAround(QListWidgetItem*)\0"
    "row\0change_gest_selection(int)\0"
    "change_key_selection(int)\0del_key_or_gest()\0"
    "add_key_or_gest()\0shift_up()\0shift_down()\0"
    "tab_chain()\0"
};

void q2_main_widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        q2_main_widget *_t = static_cast<q2_main_widget *>(_o);
        switch (_id) {
        case 0: _t->switch_timer(); break;
        case 1: _t->update(); break;
        case 2: _t->read_gest((*reinterpret_cast< const id_type(*)>(_a[1]))); break;
        case 3: _t->read_all_gest(); break;
        case 4: _t->write_gest((*reinterpret_cast< const id_type(*)>(_a[1]))); break;
        case 5: _t->write_all_gest(); break;
        case 6: _t->remove_all_gest(); break;
        case 7: _t->write_to_eeprom(); break;
        case 8: _t->load_arch(); break;
        case 9: _t->save_arch(); break;
        case 10: _t->quick_save_arch(); break;
        case 11: _t->add_gest(); break;
        case 12: _t->del_gest(); break;
        case 13: _t->add_key(); break;
        case 14: _t->del_key(); break;
        case 15: _t->changeListSelection((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 16: _t->checkBoxWorkAround((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 17: _t->change_gest_selection((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 18: _t->change_key_selection((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 19: _t->del_key_or_gest(); break;
        case 20: _t->add_key_or_gest(); break;
        case 21: _t->shift_up(); break;
        case 22: _t->shift_down(); break;
        case 23: _t->tab_chain(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData q2_main_widget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject q2_main_widget::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_q2_main_widget,
      qt_meta_data_q2_main_widget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &q2_main_widget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *q2_main_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *q2_main_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_q2_main_widget))
        return static_cast<void*>(const_cast< q2_main_widget*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int q2_main_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

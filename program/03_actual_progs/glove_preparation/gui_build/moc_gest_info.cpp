/****************************************************************************
** Meta object code from reading C++ file 'gest_info.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gui_src/gest_info.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gest_info.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_q2_gest_info_widget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   21,   20,   20, 0x0a,
      43,   41,   20,   20, 0x0a,
      73,   21,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_q2_gest_info_widget[] = {
    "q2_gest_info_widget\0\0id\0change_gest(int)\0"
    "s\0update_name(QListWidgetItem*)\0"
    "update_id(int)\0"
};

void q2_gest_info_widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        q2_gest_info_widget *_t = static_cast<q2_gest_info_widget *>(_o);
        switch (_id) {
        case 0: _t->change_gest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->update_name((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->update_id((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData q2_gest_info_widget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject q2_gest_info_widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_q2_gest_info_widget,
      qt_meta_data_q2_gest_info_widget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &q2_gest_info_widget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *q2_gest_info_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *q2_gest_info_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_q2_gest_info_widget))
        return static_cast<void*>(const_cast< q2_gest_info_widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int q2_gest_info_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

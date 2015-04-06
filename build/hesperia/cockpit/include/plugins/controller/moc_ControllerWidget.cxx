/****************************************************************************
** Meta object code from reading C++ file 'ControllerWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../hesperia/cockpit/include/plugins/controller/ControllerWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ControllerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_cockpit__plugins__controller__ControllerWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      48,   47,   47,   47, 0x0a,
      63,   61,   47,   47, 0x0a,
      74,   47,   47,   47, 0x0a,
      94,   47,   47,   47, 0x0a,
     115,   47,   47,   47, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_cockpit__plugins__controller__ControllerWidget[] = {
    "cockpit::plugins::controller::ControllerWidget\0"
    "\0TimerEvent()\0v\0setHz(int)\0"
    "userButtonPressed()\0userButtonReleased()\0"
    "sendButtonReleased()\0"
};

void cockpit::plugins::controller::ControllerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ControllerWidget *_t = static_cast<ControllerWidget *>(_o);
        switch (_id) {
        case 0: _t->TimerEvent(); break;
        case 1: _t->setHz((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->userButtonPressed(); break;
        case 3: _t->userButtonReleased(); break;
        case 4: _t->sendButtonReleased(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData cockpit::plugins::controller::ControllerWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject cockpit::plugins::controller::ControllerWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_cockpit__plugins__controller__ControllerWidget,
      qt_meta_data_cockpit__plugins__controller__ControllerWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &cockpit::plugins::controller::ControllerWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *cockpit::plugins::controller::ControllerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *cockpit::plugins::controller::ControllerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_cockpit__plugins__controller__ControllerWidget))
        return static_cast<void*>(const_cast< ControllerWidget*>(this));
    if (!strcmp(_clname, "core::io::ContainerListener"))
        return static_cast< core::io::ContainerListener*>(const_cast< ControllerWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int cockpit::plugins::controller::ControllerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

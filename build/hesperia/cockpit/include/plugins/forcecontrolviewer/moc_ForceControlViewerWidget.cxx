/****************************************************************************
** Meta object code from reading C++ file 'ForceControlViewerWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../hesperia/cockpit/include/plugins/forcecontrolviewer/ForceControlViewerWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ForceControlViewerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_cockpit__plugins__forcecontrolviewer__ForceControlViewerWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      64,   63,   63,   63, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_cockpit__plugins__forcecontrolviewer__ForceControlViewerWidget[] = {
    "cockpit::plugins::forcecontrolviewer::ForceControlViewerWidget\0"
    "\0TimerEvent()\0"
};

void cockpit::plugins::forcecontrolviewer::ForceControlViewerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ForceControlViewerWidget *_t = static_cast<ForceControlViewerWidget *>(_o);
        switch (_id) {
        case 0: _t->TimerEvent(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData cockpit::plugins::forcecontrolviewer::ForceControlViewerWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject cockpit::plugins::forcecontrolviewer::ForceControlViewerWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_cockpit__plugins__forcecontrolviewer__ForceControlViewerWidget,
      qt_meta_data_cockpit__plugins__forcecontrolviewer__ForceControlViewerWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &cockpit::plugins::forcecontrolviewer::ForceControlViewerWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *cockpit::plugins::forcecontrolviewer::ForceControlViewerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *cockpit::plugins::forcecontrolviewer::ForceControlViewerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_cockpit__plugins__forcecontrolviewer__ForceControlViewerWidget))
        return static_cast<void*>(const_cast< ForceControlViewerWidget*>(this));
    if (!strcmp(_clname, "core::io::ContainerListener"))
        return static_cast< core::io::ContainerListener*>(const_cast< ForceControlViewerWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int cockpit::plugins::forcecontrolviewer::ForceControlViewerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

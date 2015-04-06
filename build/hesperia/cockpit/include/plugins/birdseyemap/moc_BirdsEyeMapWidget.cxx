/****************************************************************************
** Meta object code from reading C++ file 'BirdsEyeMapWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../hesperia/cockpit/include/plugins/birdseyemap/BirdsEyeMapWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BirdsEyeMapWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_cockpit__plugins__birdseyemap__BirdsEyeMapWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      62,   50,   49,   49, 0x08,
     101,   96,   49,   49, 0x08,
     134,  130,   49,   49, 0x08,
     150,   49,   49,   49, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_cockpit__plugins__birdseyemap__BirdsEyeMapWidget[] = {
    "cockpit::plugins::birdseyemap::BirdsEyeMapWidget\0"
    "\0item,column\0itemChanged(QTreeWidgetItem*,int)\0"
    "item\0selectedItemChanged(QString)\0val\0"
    "changeZoom(int)\0resetTrace()\0"
};

void cockpit::plugins::birdseyemap::BirdsEyeMapWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BirdsEyeMapWidget *_t = static_cast<BirdsEyeMapWidget *>(_o);
        switch (_id) {
        case 0: _t->itemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->selectedItemChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->changeZoom((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->resetTrace(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData cockpit::plugins::birdseyemap::BirdsEyeMapWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject cockpit::plugins::birdseyemap::BirdsEyeMapWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_cockpit__plugins__birdseyemap__BirdsEyeMapWidget,
      qt_meta_data_cockpit__plugins__birdseyemap__BirdsEyeMapWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &cockpit::plugins::birdseyemap::BirdsEyeMapWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *cockpit::plugins::birdseyemap::BirdsEyeMapWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *cockpit::plugins::birdseyemap::BirdsEyeMapWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_cockpit__plugins__birdseyemap__BirdsEyeMapWidget))
        return static_cast<void*>(const_cast< BirdsEyeMapWidget*>(this));
    if (!strcmp(_clname, "core::io::ContainerListener"))
        return static_cast< core::io::ContainerListener*>(const_cast< BirdsEyeMapWidget*>(this));
    if (!strcmp(_clname, "CameraAssignableNodesListener"))
        return static_cast< CameraAssignableNodesListener*>(const_cast< BirdsEyeMapWidget*>(this));
    if (!strcmp(_clname, "SelectableNodeDescriptorTreeListener"))
        return static_cast< SelectableNodeDescriptorTreeListener*>(const_cast< BirdsEyeMapWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int cockpit::plugins::birdseyemap::BirdsEyeMapWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

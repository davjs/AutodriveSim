/****************************************************************************
** Meta object code from reading C++ file 'EnvironmentViewerWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../hesperia/cockpit/include/plugins/environmentviewer/EnvironmentViewerWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EnvironmentViewerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_cockpit__plugins__environmentviewer__EnvironmentViewerWidget[] = {

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
      74,   62,   61,   61, 0x08,
     113,  108,   61,   61, 0x08,
     142,  108,   61,   61, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_cockpit__plugins__environmentviewer__EnvironmentViewerWidget[] = {
    "cockpit::plugins::environmentviewer::EnvironmentViewerWidget\0"
    "\0item,column\0itemChanged(QTreeWidgetItem*,int)\0"
    "item\0selectedItemChanged(QString)\0"
    "selectedItemChangedBackground(QString)\0"
};

void cockpit::plugins::environmentviewer::EnvironmentViewerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        EnvironmentViewerWidget *_t = static_cast<EnvironmentViewerWidget *>(_o);
        switch (_id) {
        case 0: _t->itemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->selectedItemChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->selectedItemChangedBackground((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData cockpit::plugins::environmentviewer::EnvironmentViewerWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject cockpit::plugins::environmentviewer::EnvironmentViewerWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_cockpit__plugins__environmentviewer__EnvironmentViewerWidget,
      qt_meta_data_cockpit__plugins__environmentviewer__EnvironmentViewerWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &cockpit::plugins::environmentviewer::EnvironmentViewerWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *cockpit::plugins::environmentviewer::EnvironmentViewerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *cockpit::plugins::environmentviewer::EnvironmentViewerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_cockpit__plugins__environmentviewer__EnvironmentViewerWidget))
        return static_cast<void*>(const_cast< EnvironmentViewerWidget*>(this));
    if (!strcmp(_clname, "core::io::ContainerListener"))
        return static_cast< core::io::ContainerListener*>(const_cast< EnvironmentViewerWidget*>(this));
    if (!strcmp(_clname, "CameraAssignableNodesListener"))
        return static_cast< CameraAssignableNodesListener*>(const_cast< EnvironmentViewerWidget*>(this));
    if (!strcmp(_clname, "SelectableNodeDescriptorTreeListener"))
        return static_cast< SelectableNodeDescriptorTreeListener*>(const_cast< EnvironmentViewerWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int cockpit::plugins::environmentviewer::EnvironmentViewerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

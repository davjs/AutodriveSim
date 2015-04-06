/****************************************************************************
** Meta object code from reading C++ file 'CockpitWindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../hesperia/cockpit/include/CockpitWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CockpitWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_cockpit__CockpitWindow[] = {

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
      24,   23,   23,   23, 0x0a,
      32,   23,   23,   23, 0x0a,
      58,   23,   23,   23, 0x0a,
      84,   23,   23,   23, 0x0a,
     112,  107,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_cockpit__CockpitWindow[] = {
    "cockpit::CockpitWindow\0\0close()\0"
    "maximizeActiveSubWindow()\0"
    "minimizeActiveSubWindow()\0"
    "resetActiveSubWindow()\0item\0"
    "showPlugIn(QListWidgetItem*)\0"
};

void cockpit::CockpitWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CockpitWindow *_t = static_cast<CockpitWindow *>(_o);
        switch (_id) {
        case 0: _t->close(); break;
        case 1: _t->maximizeActiveSubWindow(); break;
        case 2: _t->minimizeActiveSubWindow(); break;
        case 3: _t->resetActiveSubWindow(); break;
        case 4: _t->showPlugIn((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData cockpit::CockpitWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject cockpit::CockpitWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_cockpit__CockpitWindow,
      qt_meta_data_cockpit__CockpitWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &cockpit::CockpitWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *cockpit::CockpitWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *cockpit::CockpitWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_cockpit__CockpitWindow))
        return static_cast<void*>(const_cast< CockpitWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int cockpit::CockpitWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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

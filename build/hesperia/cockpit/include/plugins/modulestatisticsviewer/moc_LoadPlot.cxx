/****************************************************************************
** Meta object code from reading C++ file 'LoadPlot.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../hesperia/cockpit/include/plugins/modulestatisticsviewer/LoadPlot.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LoadPlot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_cockpit__plugins__modulestatisticsviewer__LoadPlot[] = {

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
      52,   51,   51,   51, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_cockpit__plugins__modulestatisticsviewer__LoadPlot[] = {
    "cockpit::plugins::modulestatisticsviewer::LoadPlot\0"
    "\0attachQueuedLPM()\0"
};

void cockpit::plugins::modulestatisticsviewer::LoadPlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LoadPlot *_t = static_cast<LoadPlot *>(_o);
        switch (_id) {
        case 0: _t->attachQueuedLPM(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData cockpit::plugins::modulestatisticsviewer::LoadPlot::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject cockpit::plugins::modulestatisticsviewer::LoadPlot::staticMetaObject = {
    { &QwtPlot::staticMetaObject, qt_meta_stringdata_cockpit__plugins__modulestatisticsviewer__LoadPlot,
      qt_meta_data_cockpit__plugins__modulestatisticsviewer__LoadPlot, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &cockpit::plugins::modulestatisticsviewer::LoadPlot::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *cockpit::plugins::modulestatisticsviewer::LoadPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *cockpit::plugins::modulestatisticsviewer::LoadPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_cockpit__plugins__modulestatisticsviewer__LoadPlot))
        return static_cast<void*>(const_cast< LoadPlot*>(this));
    return QwtPlot::qt_metacast(_clname);
}

int cockpit::plugins::modulestatisticsviewer::LoadPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtPlot::qt_metacall(_c, _id, _a);
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

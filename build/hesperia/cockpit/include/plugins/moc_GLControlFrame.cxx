/****************************************************************************
** Meta object code from reading C++ file 'GLControlFrame.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../hesperia/cockpit/include/plugins/GLControlFrame.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GLControlFrame.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_cockpit__plugins__GLControlFrame[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      43,   34,   33,   33, 0x05,
      74,   34,   33,   33, 0x05,

 // slots: signature, parameters, type, tag, flags
     103,   34,   33,   33, 0x08,
     121,   34,   33,   33, 0x08,
     139,   33,   33,   33, 0x08,
     153,   33,   33,   33, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_cockpit__plugins__GLControlFrame[] = {
    "cockpit::plugins::GLControlFrame\0\0"
    "newValue\0horizontalValueChanged(double)\0"
    "verticalValueChanged(double)\0"
    "newVValue(double)\0newHValue(double)\0"
    "resetHValue()\0resetVValue()\0"
};

void cockpit::plugins::GLControlFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GLControlFrame *_t = static_cast<GLControlFrame *>(_o);
        switch (_id) {
        case 0: _t->horizontalValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->verticalValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->newVValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->newHValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->resetHValue(); break;
        case 5: _t->resetVValue(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData cockpit::plugins::GLControlFrame::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject cockpit::plugins::GLControlFrame::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_cockpit__plugins__GLControlFrame,
      qt_meta_data_cockpit__plugins__GLControlFrame, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &cockpit::plugins::GLControlFrame::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *cockpit::plugins::GLControlFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *cockpit::plugins::GLControlFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_cockpit__plugins__GLControlFrame))
        return static_cast<void*>(const_cast< GLControlFrame*>(this));
    return QWidget::qt_metacast(_clname);
}

int cockpit::plugins::GLControlFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void cockpit::plugins::GLControlFrame::horizontalValueChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void cockpit::plugins::GLControlFrame::verticalValueChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

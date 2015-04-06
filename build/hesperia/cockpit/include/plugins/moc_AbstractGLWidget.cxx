/****************************************************************************
** Meta object code from reading C++ file 'AbstractGLWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../hesperia/cockpit/include/plugins/AbstractGLWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AbstractGLWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_cockpit__plugins__AbstractGLWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: signature, parameters, type, tag, flags
      49,   36,   35,   35, 0x05,
      77,   36,   35,   35, 0x05,
     117,  104,   35,   35, 0x05,
     145,  104,   35,   35, 0x05,
     185,  172,   35,   35, 0x05,
     213,  172,   35,   35, 0x05,
     244,  240,   35,   35, 0x05,
     263,  240,   35,   35, 0x05,
     287,  281,   35,   35, 0x05,
     308,  281,   35,   35, 0x05,
     336,  328,   35,   35, 0x05,
     359,  328,   35,   35, 0x05,

 // slots: signature, parameters, type, tag, flags
     381,   36,   35,   35, 0x0a,
     405,  104,   35,   35, 0x0a,
     429,  172,   35,   35, 0x0a,
     453,  240,   35,   35, 0x0a,
     468,  281,   35,   35, 0x0a,
     485,  328,   35,   35, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_cockpit__plugins__AbstractGLWidget[] = {
    "cockpit::plugins::AbstractGLWidget\0\0"
    "translationX\0translationXChanged(double)\0"
    "translationXChanged(float)\0translationY\0"
    "translationYChanged(double)\0"
    "translationYChanged(float)\0translationZ\0"
    "translationZChanged(double)\0"
    "translationZChanged(float)\0phi\0"
    "phiChanged(double)\0phiChanged(float)\0"
    "theta\0thetaChanged(double)\0"
    "thetaChanged(float)\0epsilon\0"
    "epsilonChanged(double)\0epsilonChanged(float)\0"
    "setTranslationX(double)\0setTranslationY(double)\0"
    "setTranslationZ(double)\0setPhi(double)\0"
    "setTheta(double)\0setEpsilon(double)\0"
};

void cockpit::plugins::AbstractGLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AbstractGLWidget *_t = static_cast<AbstractGLWidget *>(_o);
        switch (_id) {
        case 0: _t->translationXChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->translationXChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->translationYChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->translationYChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->translationZChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->translationZChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->phiChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->phiChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->thetaChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->thetaChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->epsilonChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->epsilonChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 12: _t->setTranslationX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->setTranslationY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->setTranslationZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->setPhi((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 16: _t->setTheta((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 17: _t->setEpsilon((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData cockpit::plugins::AbstractGLWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject cockpit::plugins::AbstractGLWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_cockpit__plugins__AbstractGLWidget,
      qt_meta_data_cockpit__plugins__AbstractGLWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &cockpit::plugins::AbstractGLWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *cockpit::plugins::AbstractGLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *cockpit::plugins::AbstractGLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_cockpit__plugins__AbstractGLWidget))
        return static_cast<void*>(const_cast< AbstractGLWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int cockpit::plugins::AbstractGLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void cockpit::plugins::AbstractGLWidget::translationXChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void cockpit::plugins::AbstractGLWidget::translationXChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void cockpit::plugins::AbstractGLWidget::translationYChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void cockpit::plugins::AbstractGLWidget::translationYChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void cockpit::plugins::AbstractGLWidget::translationZChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void cockpit::plugins::AbstractGLWidget::translationZChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void cockpit::plugins::AbstractGLWidget::phiChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void cockpit::plugins::AbstractGLWidget::phiChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void cockpit::plugins::AbstractGLWidget::thetaChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void cockpit::plugins::AbstractGLWidget::thetaChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void cockpit::plugins::AbstractGLWidget::epsilonChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void cockpit::plugins::AbstractGLWidget::epsilonChanged(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_END_MOC_NAMESPACE

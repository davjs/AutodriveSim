/****************************************************************************
** Meta object code from reading C++ file 'PlayerWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../hesperia/cockpit/include/plugins/player/PlayerWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PlayerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_cockpit__plugins__player__PlayerWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      40,   39,   39,   39, 0x0a,
      51,   39,   39,   39, 0x0a,
      58,   39,   39,   39, 0x0a,
      66,   39,   39,   39, 0x0a,
      75,   39,   39,   39, 0x0a,
      82,   39,   39,   39, 0x0a,
     103,   39,   39,   39, 0x0a,
     123,   39,   39,   39, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_cockpit__plugins__player__PlayerWidget[] = {
    "cockpit::plugins::player::PlayerWidget\0"
    "\0loadFile()\0play()\0pause()\0rewind()\0"
    "step()\0changeTimeScale(int)\0"
    "sendNextContainer()\0process()\0"
};

void cockpit::plugins::player::PlayerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PlayerWidget *_t = static_cast<PlayerWidget *>(_o);
        switch (_id) {
        case 0: _t->loadFile(); break;
        case 1: _t->play(); break;
        case 2: _t->pause(); break;
        case 3: _t->rewind(); break;
        case 4: _t->step(); break;
        case 5: _t->changeTimeScale((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->sendNextContainer(); break;
        case 7: _t->process(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData cockpit::plugins::player::PlayerWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject cockpit::plugins::player::PlayerWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_cockpit__plugins__player__PlayerWidget,
      qt_meta_data_cockpit__plugins__player__PlayerWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &cockpit::plugins::player::PlayerWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *cockpit::plugins::player::PlayerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *cockpit::plugins::player::PlayerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_cockpit__plugins__player__PlayerWidget))
        return static_cast<void*>(const_cast< PlayerWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int cockpit::plugins::player::PlayerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

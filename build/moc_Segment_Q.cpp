/****************************************************************************
** Meta object code from reading C++ file 'Segment_Q.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/Segment_Q.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Segment_Q.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Segment_Q_t {
    QByteArrayData data[9];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Segment_Q_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Segment_Q_t qt_meta_stringdata_Segment_Q = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Segment_Q"
QT_MOC_LITERAL(1, 10, 12), // "set_firstVal"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 5), // "start"
QT_MOC_LITERAL(4, 30, 13), // "set_secondVal"
QT_MOC_LITERAL(5, 44, 3), // "end"
QT_MOC_LITERAL(6, 48, 18), // "set_localIntensity"
QT_MOC_LITERAL(7, 67, 5), // "inten"
QT_MOC_LITERAL(8, 73, 19) // "set_globalIntensity"

    },
    "Segment_Q\0set_firstVal\0\0start\0"
    "set_secondVal\0end\0set_localIntensity\0"
    "inten\0set_globalIntensity"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Segment_Q[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       4,    1,   37,    2, 0x0a /* Public */,
       6,    1,   40,    2, 0x0a /* Public */,
       8,    1,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Float,    7,
    QMetaType::Void, QMetaType::Float,    7,

       0        // eod
};

void Segment_Q::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Segment_Q *_t = static_cast<Segment_Q *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set_firstVal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->set_secondVal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->set_localIntensity((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->set_globalIntensity((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Segment_Q::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Segment_Q.data,
      qt_meta_data_Segment_Q,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Segment_Q::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Segment_Q::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Segment_Q.stringdata0))
        return static_cast<void*>(const_cast< Segment_Q*>(this));
    return QWidget::qt_metacast(_clname);
}

int Segment_Q::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

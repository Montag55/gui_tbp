/****************************************************************************
** Meta object code from reading C++ file 'RangeWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/RangeWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RangeWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RangeWidget_t {
    QByteArrayData data[19];
    char stringdata0[226];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RangeWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RangeWidget_t qt_meta_stringdata_RangeWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "RangeWidget"
QT_MOC_LITERAL(1, 12, 17), // "firstValueChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 10), // "firstValue"
QT_MOC_LITERAL(4, 42, 18), // "secondValueChanged"
QT_MOC_LITERAL(5, 61, 11), // "secondValue"
QT_MOC_LITERAL(6, 73, 12), // "rangeChanged"
QT_MOC_LITERAL(7, 86, 3), // "min"
QT_MOC_LITERAL(8, 90, 3), // "max"
QT_MOC_LITERAL(9, 94, 13), // "sliderPressed"
QT_MOC_LITERAL(10, 108, 14), // "sliderReleased"
QT_MOC_LITERAL(11, 123, 13), // "setFirstValue"
QT_MOC_LITERAL(12, 137, 14), // "setSecondValue"
QT_MOC_LITERAL(13, 152, 10), // "setMinimum"
QT_MOC_LITERAL(14, 163, 10), // "setMaximum"
QT_MOC_LITERAL(15, 174, 8), // "setRange"
QT_MOC_LITERAL(16, 183, 14), // "setOrientation"
QT_MOC_LITERAL(17, 198, 15), // "Qt::Orientation"
QT_MOC_LITERAL(18, 214, 11) // "orientation"

    },
    "RangeWidget\0firstValueChanged\0\0"
    "firstValue\0secondValueChanged\0secondValue\0"
    "rangeChanged\0min\0max\0sliderPressed\0"
    "sliderReleased\0setFirstValue\0"
    "setSecondValue\0setMinimum\0setMaximum\0"
    "setRange\0setOrientation\0Qt::Orientation\0"
    "orientation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RangeWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,
       6,    2,   75,    2, 0x06 /* Public */,
       9,    0,   80,    2, 0x06 /* Public */,
      10,    0,   81,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   82,    2, 0x0a /* Public */,
      12,    1,   85,    2, 0x0a /* Public */,
      13,    1,   88,    2, 0x0a /* Public */,
      14,    1,   91,    2, 0x0a /* Public */,
      15,    2,   94,    2, 0x0a /* Public */,
      16,    1,   99,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void, 0x80000000 | 17,   18,

       0        // eod
};

void RangeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RangeWidget *_t = static_cast<RangeWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->firstValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->secondValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->rangeChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->sliderPressed(); break;
        case 4: _t->sliderReleased(); break;
        case 5: _t->setFirstValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setSecondValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setMinimum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setMaximum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->setOrientation((*reinterpret_cast< Qt::Orientation(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RangeWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RangeWidget::firstValueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (RangeWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RangeWidget::secondValueChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (RangeWidget::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RangeWidget::rangeChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (RangeWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RangeWidget::sliderPressed)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (RangeWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RangeWidget::sliderReleased)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject RangeWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RangeWidget.data,
      qt_meta_data_RangeWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RangeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RangeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RangeWidget.stringdata0))
        return static_cast<void*>(const_cast< RangeWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int RangeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void RangeWidget::firstValueChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RangeWidget::secondValueChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RangeWidget::rangeChanged(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RangeWidget::sliderPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void RangeWidget::sliderReleased()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE

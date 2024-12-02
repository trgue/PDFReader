/****************************************************************************
** Meta object code from reading C++ file 'slidepage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "SlidePage/slidepage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'slidepage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SlidePage_t {
    QByteArrayData data[8];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SlidePage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SlidePage_t qt_meta_stringdata_SlidePage = {
    {
QT_MOC_LITERAL(0, 0, 9), // "SlidePage"
QT_MOC_LITERAL(1, 10, 23), // "currentPageIndexChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 22), // "vScrollBarValueChanged"
QT_MOC_LITERAL(4, 58, 14), // "onStateChanged"
QT_MOC_LITERAL(5, 73, 16), // "QScroller::State"
QT_MOC_LITERAL(6, 90, 14), // "onTimerTimeOut"
QT_MOC_LITERAL(7, 105, 25) // "onCurrentPageIndexChanged"

    },
    "SlidePage\0currentPageIndexChanged\0\0"
    "vScrollBarValueChanged\0onStateChanged\0"
    "QScroller::State\0onTimerTimeOut\0"
    "onCurrentPageIndexChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SlidePage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   42,    2, 0x08 /* Private */,
       4,    1,   45,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    1,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void SlidePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SlidePage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->currentPageIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->vScrollBarValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onStateChanged((*reinterpret_cast< QScroller::State(*)>(_a[1]))); break;
        case 3: _t->onTimerTimeOut(); break;
        case 4: _t->onCurrentPageIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SlidePage::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SlidePage::currentPageIndexChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SlidePage::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SlidePage.data,
    qt_meta_data_SlidePage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SlidePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SlidePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SlidePage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SlidePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SlidePage::currentPageIndexChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'cos_tcpconnectmanger.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cos_tcpconnectmanger.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cos_tcpconnectmanger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Cos_TcpConnectManger_t {
    QByteArrayData data[12];
    char stringdata0[183];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Cos_TcpConnectManger_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Cos_TcpConnectManger_t qt_meta_stringdata_Cos_TcpConnectManger = {
    {
QT_MOC_LITERAL(0, 0, 20), // "Cos_TcpConnectManger"
QT_MOC_LITERAL(1, 21, 18), // "sig_connectSuccess"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 17), // "sig_connectFailed"
QT_MOC_LITERAL(4, 59, 14), // "sig_disconnect"
QT_MOC_LITERAL(5, 74, 18), // "sig_receiveMessage"
QT_MOC_LITERAL(6, 93, 16), // "onConnect_Server"
QT_MOC_LITERAL(7, 110, 19), // "ondisConnect_Server"
QT_MOC_LITERAL(8, 130, 11), // "sendMessage"
QT_MOC_LITERAL(9, 142, 3), // "msg"
QT_MOC_LITERAL(10, 146, 16), // "socket_Read_Data"
QT_MOC_LITERAL(11, 163, 19) // "socket_Disconnected"

    },
    "Cos_TcpConnectManger\0sig_connectSuccess\0"
    "\0sig_connectFailed\0sig_disconnect\0"
    "sig_receiveMessage\0onConnect_Server\0"
    "ondisConnect_Server\0sendMessage\0msg\0"
    "socket_Read_Data\0socket_Disconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Cos_TcpConnectManger[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    0,   61,    2, 0x06 /* Public */,
       5,    1,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   65,    2, 0x0a /* Public */,
       7,    0,   66,    2, 0x0a /* Public */,
       8,    1,   67,    2, 0x0a /* Public */,
      10,    0,   70,    2, 0x09 /* Protected */,
      11,    0,   71,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Cos_TcpConnectManger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Cos_TcpConnectManger *_t = static_cast<Cos_TcpConnectManger *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_connectSuccess(); break;
        case 1: _t->sig_connectFailed(); break;
        case 2: _t->sig_disconnect(); break;
        case 3: _t->sig_receiveMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->onConnect_Server(); break;
        case 5: _t->ondisConnect_Server(); break;
        case 6: _t->sendMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->socket_Read_Data(); break;
        case 8: _t->socket_Disconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Cos_TcpConnectManger::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Cos_TcpConnectManger::sig_connectSuccess)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Cos_TcpConnectManger::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Cos_TcpConnectManger::sig_connectFailed)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Cos_TcpConnectManger::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Cos_TcpConnectManger::sig_disconnect)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Cos_TcpConnectManger::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Cos_TcpConnectManger::sig_receiveMessage)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject Cos_TcpConnectManger::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Cos_TcpConnectManger.data,
      qt_meta_data_Cos_TcpConnectManger,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Cos_TcpConnectManger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Cos_TcpConnectManger::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Cos_TcpConnectManger.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Cos_TcpConnectManger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Cos_TcpConnectManger::sig_connectSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Cos_TcpConnectManger::sig_connectFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Cos_TcpConnectManger::sig_disconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Cos_TcpConnectManger::sig_receiveMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

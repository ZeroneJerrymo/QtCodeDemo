/****************************************************************************
** Meta object code from reading C++ file 'cos_groupchat.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cos_groupchat.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cos_groupchat.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Cos_GroupChat_t {
    QByteArrayData data[12];
    char stringdata0[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Cos_GroupChat_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Cos_GroupChat_t qt_meta_stringdata_Cos_GroupChat = {
    {
QT_MOC_LITERAL(0, 0, 13), // "Cos_GroupChat"
QT_MOC_LITERAL(1, 14, 11), // "sendMessage"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "ppppp"
QT_MOC_LITERAL(4, 33, 6), // "ppppp1"
QT_MOC_LITERAL(5, 40, 18), // "slot_btnpicClicked"
QT_MOC_LITERAL(6, 59, 26), // "slot_lineEditReturnpressed"
QT_MOC_LITERAL(7, 86, 13), // "updateMessage"
QT_MOC_LITERAL(8, 100, 19), // "slot_receiveMessage"
QT_MOC_LITERAL(9, 120, 18), // "slot_deleteMessage"
QT_MOC_LITERAL(10, 139, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(11, 161, 23) // "on_pushButton_2_clicked"

    },
    "Cos_GroupChat\0sendMessage\0\0ppppp\0"
    "ppppp1\0slot_btnpicClicked\0"
    "slot_lineEditReturnpressed\0updateMessage\0"
    "slot_receiveMessage\0slot_deleteMessage\0"
    "on_pushButton_clicked\0on_pushButton_2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Cos_GroupChat[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   67,    2, 0x0a /* Public */,
       4,    0,   68,    2, 0x0a /* Public */,
       5,    0,   69,    2, 0x0a /* Public */,
       6,    0,   70,    2, 0x0a /* Public */,
       7,    0,   71,    2, 0x09 /* Protected */,
       8,    1,   72,    2, 0x08 /* Private */,
       9,    1,   75,    2, 0x08 /* Private */,
      10,    0,   78,    2, 0x08 /* Private */,
      11,    0,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Cos_GroupChat::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Cos_GroupChat *_t = static_cast<Cos_GroupChat *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ppppp(); break;
        case 2: _t->ppppp1(); break;
        case 3: _t->slot_btnpicClicked(); break;
        case 4: _t->slot_lineEditReturnpressed(); break;
        case 5: _t->updateMessage(); break;
        case 6: _t->slot_receiveMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->slot_deleteMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->on_pushButton_clicked(); break;
        case 9: _t->on_pushButton_2_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Cos_GroupChat::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Cos_GroupChat::sendMessage)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Cos_GroupChat::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Cos_GroupChat.data,
      qt_meta_data_Cos_GroupChat,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Cos_GroupChat::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Cos_GroupChat::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Cos_GroupChat.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Cos_GroupChat::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Cos_GroupChat::sendMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
/****************************************************************************
** Meta object code from reading C++ file 'tcpserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../repo/thesis/SERVER/AudioStorOrientalServer/tcpserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TcpServer_t {
    QByteArrayData data[28];
    char stringdata0[386];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TcpServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TcpServer_t qt_meta_stringdata_TcpServer = {
    {
QT_MOC_LITERAL(0, 0, 9), // "TcpServer"
QT_MOC_LITERAL(1, 10, 15), // "messageReceived"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "std::string"
QT_MOC_LITERAL(4, 39, 7), // "message"
QT_MOC_LITERAL(5, 47, 8), // "removeIP"
QT_MOC_LITERAL(6, 56, 11), // "peeraddress"
QT_MOC_LITERAL(7, 68, 12), // "dataReceived"
QT_MOC_LITERAL(8, 81, 18), // "QList<QByteArray>&"
QT_MOC_LITERAL(9, 100, 4), // "data"
QT_MOC_LITERAL(10, 105, 15), // "controlReceived"
QT_MOC_LITERAL(11, 121, 7), // "control"
QT_MOC_LITERAL(12, 129, 18), // "connectionReceived"
QT_MOC_LITERAL(13, 148, 11), // "peerAddress"
QT_MOC_LITERAL(14, 160, 15), // "dataTransmitEnd"
QT_MOC_LITERAL(15, 176, 14), // "lengthReceived"
QT_MOC_LITERAL(16, 191, 7), // "dataLen"
QT_MOC_LITERAL(17, 199, 14), // "stepperRotated"
QT_MOC_LITERAL(18, 214, 15), // "onNewConnection"
QT_MOC_LITERAL(19, 230, 20), // "onSocketStateChanged"
QT_MOC_LITERAL(20, 251, 28), // "QAbstractSocket::SocketState"
QT_MOC_LITERAL(21, 280, 11), // "socketState"
QT_MOC_LITERAL(22, 292, 13), // "onSendControl"
QT_MOC_LITERAL(23, 306, 14), // "controlMessage"
QT_MOC_LITERAL(24, 321, 11), // "onReadyRead"
QT_MOC_LITERAL(25, 333, 22), // "updateSocketDeviceType"
QT_MOC_LITERAL(26, 356, 14), // "AndroidAddress"
QT_MOC_LITERAL(27, 371, 14) // "ArduinoAddress"

    },
    "TcpServer\0messageReceived\0\0std::string\0"
    "message\0removeIP\0peeraddress\0dataReceived\0"
    "QList<QByteArray>&\0data\0controlReceived\0"
    "control\0connectionReceived\0peerAddress\0"
    "dataTransmitEnd\0lengthReceived\0dataLen\0"
    "stepperRotated\0onNewConnection\0"
    "onSocketStateChanged\0QAbstractSocket::SocketState\0"
    "socketState\0onSendControl\0controlMessage\0"
    "onReadyRead\0updateSocketDeviceType\0"
    "AndroidAddress\0ArduinoAddress"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpServer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       5,    1,   82,    2, 0x06 /* Public */,
       7,    1,   85,    2, 0x06 /* Public */,
      10,    1,   88,    2, 0x06 /* Public */,
      12,    1,   91,    2, 0x06 /* Public */,
      14,    0,   94,    2, 0x06 /* Public */,
      15,    1,   95,    2, 0x06 /* Public */,
      17,    0,   98,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    0,   99,    2, 0x0a /* Public */,
      19,    1,  100,    2, 0x0a /* Public */,
      22,    1,  103,    2, 0x0a /* Public */,
      24,    0,  106,    2, 0x0a /* Public */,
      25,    2,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, 0x80000000 | 3,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, 0x80000000 | 3,   23,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   26,   27,

       0        // eod
};

void TcpServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TcpServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->messageReceived((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 1: _t->removeIP((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->dataReceived((*reinterpret_cast< QList<QByteArray>(*)>(_a[1]))); break;
        case 3: _t->controlReceived((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->connectionReceived((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 5: _t->dataTransmitEnd(); break;
        case 6: _t->lengthReceived((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->stepperRotated(); break;
        case 8: _t->onNewConnection(); break;
        case 9: _t->onSocketStateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 10: _t->onSendControl((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 11: _t->onReadyRead(); break;
        case 12: _t->updateSocketDeviceType((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TcpServer::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpServer::messageReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TcpServer::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpServer::removeIP)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TcpServer::*)(QList<QByteArray> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpServer::dataReceived)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TcpServer::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpServer::controlReceived)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TcpServer::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpServer::connectionReceived)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (TcpServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpServer::dataTransmitEnd)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (TcpServer::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpServer::lengthReceived)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (TcpServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpServer::stepperRotated)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TcpServer::staticMetaObject = { {
    &QTcpServer::staticMetaObject,
    qt_meta_stringdata_TcpServer.data,
    qt_meta_data_TcpServer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TcpServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TcpServer.stringdata0))
        return static_cast<void*>(this);
    return QTcpServer::qt_metacast(_clname);
}

int TcpServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void TcpServer::messageReceived(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TcpServer::removeIP(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TcpServer::dataReceived(QList<QByteArray> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TcpServer::controlReceived(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TcpServer::connectionReceived(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TcpServer::dataTransmitEnd()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void TcpServer::lengthReceived(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void TcpServer::stepperRotated()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

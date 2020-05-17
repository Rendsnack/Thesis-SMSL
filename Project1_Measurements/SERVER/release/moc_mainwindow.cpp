/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../repo/thesis/SERVER/AudioStorOrientalServer/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[36];
    char stringdata0[522];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "IpSelected"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 14), // "AndroidAddress"
QT_MOC_LITERAL(4, 38, 14), // "ArduinoAddress"
QT_MOC_LITERAL(5, 53, 15), // "messageReceived"
QT_MOC_LITERAL(6, 69, 11), // "std::string"
QT_MOC_LITERAL(7, 81, 7), // "message"
QT_MOC_LITERAL(8, 89, 8), // "removeIP"
QT_MOC_LITERAL(9, 98, 11), // "peerAddress"
QT_MOC_LITERAL(10, 110, 14), // "addAddressList"
QT_MOC_LITERAL(11, 125, 17), // "onControlReceived"
QT_MOC_LITERAL(12, 143, 7), // "control"
QT_MOC_LITERAL(13, 151, 10), // "selectPath"
QT_MOC_LITERAL(14, 162, 9), // "writeData"
QT_MOC_LITERAL(15, 172, 18), // "QList<QByteArray>&"
QT_MOC_LITERAL(16, 191, 4), // "data"
QT_MOC_LITERAL(17, 196, 9), // "defineLen"
QT_MOC_LITERAL(18, 206, 3), // "len"
QT_MOC_LITERAL(19, 210, 20), // "handleStepperControl"
QT_MOC_LITERAL(20, 231, 22), // "on_startRecord_clicked"
QT_MOC_LITERAL(21, 254, 21), // "on_stopRecord_clicked"
QT_MOC_LITERAL(22, 276, 29), // "on_ButtonSelectSignal_clicked"
QT_MOC_LITERAL(23, 306, 13), // "deviceChanged"
QT_MOC_LITERAL(24, 320, 5), // "index"
QT_MOC_LITERAL(25, 326, 25), // "on_TestSignalPlay_clicked"
QT_MOC_LITERAL(26, 352, 18), // "handleStateChanged"
QT_MOC_LITERAL(27, 371, 13), // "QAudio::State"
QT_MOC_LITERAL(28, 385, 8), // "newState"
QT_MOC_LITERAL(29, 394, 19), // "on_stepPlus_clicked"
QT_MOC_LITERAL(30, 414, 18), // "on_stepMin_clicked"
QT_MOC_LITERAL(31, 433, 24), // "on_StepSpin_valueChanged"
QT_MOC_LITERAL(32, 458, 4), // "arg1"
QT_MOC_LITERAL(33, 463, 24), // "on_automaticTest_clicked"
QT_MOC_LITERAL(34, 488, 16), // "androidIpChanged"
QT_MOC_LITERAL(35, 505, 16) // "arduinoIpChanged"

    },
    "MainWindow\0IpSelected\0\0AndroidAddress\0"
    "ArduinoAddress\0messageReceived\0"
    "std::string\0message\0removeIP\0peerAddress\0"
    "addAddressList\0onControlReceived\0"
    "control\0selectPath\0writeData\0"
    "QList<QByteArray>&\0data\0defineLen\0len\0"
    "handleStepperControl\0on_startRecord_clicked\0"
    "on_stopRecord_clicked\0"
    "on_ButtonSelectSignal_clicked\0"
    "deviceChanged\0index\0on_TestSignalPlay_clicked\0"
    "handleStateChanged\0QAudio::State\0"
    "newState\0on_stepPlus_clicked\0"
    "on_stepMin_clicked\0on_StepSpin_valueChanged\0"
    "arg1\0on_automaticTest_clicked\0"
    "androidIpChanged\0arduinoIpChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  119,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,  124,    2, 0x0a /* Public */,
       8,    1,  127,    2, 0x0a /* Public */,
      10,    1,  130,    2, 0x0a /* Public */,
      11,    1,  133,    2, 0x0a /* Public */,
      13,    0,  136,    2, 0x0a /* Public */,
      14,    1,  137,    2, 0x0a /* Public */,
      17,    1,  140,    2, 0x0a /* Public */,
      19,    0,  143,    2, 0x0a /* Public */,
      20,    0,  144,    2, 0x08 /* Private */,
      21,    0,  145,    2, 0x08 /* Private */,
      22,    0,  146,    2, 0x08 /* Private */,
      23,    1,  147,    2, 0x08 /* Private */,
      25,    0,  150,    2, 0x08 /* Private */,
      26,    1,  151,    2, 0x08 /* Private */,
      29,    0,  154,    2, 0x08 /* Private */,
      30,    0,  155,    2, 0x08 /* Private */,
      31,    1,  156,    2, 0x08 /* Private */,
      33,    0,  159,    2, 0x08 /* Private */,
      34,    1,  160,    2, 0x08 /* Private */,
      35,    1,  163,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, 0x80000000 | 6,    9,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 27,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int,   24,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->IpSelected((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->messageReceived((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 2: _t->removeIP((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->addAddressList((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 4: _t->onControlReceived((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->selectPath(); break;
        case 6: _t->writeData((*reinterpret_cast< QList<QByteArray>(*)>(_a[1]))); break;
        case 7: _t->defineLen((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->handleStepperControl(); break;
        case 9: _t->on_startRecord_clicked(); break;
        case 10: _t->on_stopRecord_clicked(); break;
        case 11: _t->on_ButtonSelectSignal_clicked(); break;
        case 12: _t->deviceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_TestSignalPlay_clicked(); break;
        case 14: _t->handleStateChanged((*reinterpret_cast< QAudio::State(*)>(_a[1]))); break;
        case 15: _t->on_stepPlus_clicked(); break;
        case 16: _t->on_stepMin_clicked(); break;
        case 17: _t->on_StepSpin_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->on_automaticTest_clicked(); break;
        case 19: _t->androidIpChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->arduinoIpChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAudio::State >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::IpSelected)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::IpSelected(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

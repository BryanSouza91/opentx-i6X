/****************************************************************************
** Meta object code from reading C++ file 'simulatorinterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.17)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../../../../../../src/simulation/simulatorinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simulatorinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.17. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SimulatorInterface_t {
    QByteArrayData data[66];
    char stringdata0[704];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SimulatorInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SimulatorInterface_t qt_meta_stringdata_SimulatorInterface = {
    {
QT_MOC_LITERAL(0, 0, 18), // "SimulatorInterface"
QT_MOC_LITERAL(1, 19, 7), // "started"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 7), // "stopped"
QT_MOC_LITERAL(4, 36, 9), // "heartbeat"
QT_MOC_LITERAL(5, 46, 5), // "loops"
QT_MOC_LITERAL(6, 52, 9), // "timestamp"
QT_MOC_LITERAL(7, 62, 12), // "runtimeError"
QT_MOC_LITERAL(8, 75, 5), // "error"
QT_MOC_LITERAL(9, 81, 9), // "lcdChange"
QT_MOC_LITERAL(10, 91, 15), // "backlightEnable"
QT_MOC_LITERAL(11, 107, 12), // "phaseChanged"
QT_MOC_LITERAL(12, 120, 5), // "phase"
QT_MOC_LITERAL(13, 126, 4), // "name"
QT_MOC_LITERAL(14, 131, 21), // "channelOutValueChange"
QT_MOC_LITERAL(15, 153, 5), // "index"
QT_MOC_LITERAL(16, 159, 5), // "value"
QT_MOC_LITERAL(17, 165, 5), // "limit"
QT_MOC_LITERAL(18, 171, 21), // "channelMixValueChange"
QT_MOC_LITERAL(19, 193, 20), // "virtualSwValueChange"
QT_MOC_LITERAL(20, 214, 15), // "trimValueChange"
QT_MOC_LITERAL(21, 230, 15), // "trimRangeChange"
QT_MOC_LITERAL(22, 246, 3), // "min"
QT_MOC_LITERAL(23, 250, 3), // "max"
QT_MOC_LITERAL(24, 254, 15), // "gVarValueChange"
QT_MOC_LITERAL(25, 270, 17), // "outputValueChange"
QT_MOC_LITERAL(26, 288, 4), // "type"
QT_MOC_LITERAL(27, 293, 4), // "init"
QT_MOC_LITERAL(28, 298, 5), // "start"
QT_MOC_LITERAL(29, 304, 11), // "const char*"
QT_MOC_LITERAL(30, 316, 8), // "filename"
QT_MOC_LITERAL(31, 325, 5), // "tests"
QT_MOC_LITERAL(32, 331, 4), // "stop"
QT_MOC_LITERAL(33, 336, 9), // "setSdPath"
QT_MOC_LITERAL(34, 346, 6), // "sdPath"
QT_MOC_LITERAL(35, 353, 12), // "settingsPath"
QT_MOC_LITERAL(36, 366, 13), // "setVolumeGain"
QT_MOC_LITERAL(37, 380, 12), // "setRadioData"
QT_MOC_LITERAL(38, 393, 4), // "data"
QT_MOC_LITERAL(39, 398, 14), // "setAnalogValue"
QT_MOC_LITERAL(40, 413, 7), // "uint8_t"
QT_MOC_LITERAL(41, 421, 7), // "int16_t"
QT_MOC_LITERAL(42, 429, 6), // "setKey"
QT_MOC_LITERAL(43, 436, 3), // "key"
QT_MOC_LITERAL(44, 440, 5), // "state"
QT_MOC_LITERAL(45, 446, 9), // "setSwitch"
QT_MOC_LITERAL(46, 456, 5), // "swtch"
QT_MOC_LITERAL(47, 462, 6), // "int8_t"
QT_MOC_LITERAL(48, 469, 7), // "setTrim"
QT_MOC_LITERAL(49, 477, 3), // "idx"
QT_MOC_LITERAL(50, 481, 13), // "setTrimSwitch"
QT_MOC_LITERAL(51, 495, 4), // "trim"
QT_MOC_LITERAL(52, 500, 15), // "setTrainerInput"
QT_MOC_LITERAL(53, 516, 11), // "inputNumber"
QT_MOC_LITERAL(54, 528, 13), // "setInputValue"
QT_MOC_LITERAL(55, 542, 18), // "rotaryEncoderEvent"
QT_MOC_LITERAL(56, 561, 5), // "steps"
QT_MOC_LITERAL(57, 567, 17), // "setTrainerTimeout"
QT_MOC_LITERAL(58, 585, 8), // "uint16_t"
QT_MOC_LITERAL(59, 594, 2), // "ms"
QT_MOC_LITERAL(60, 597, 13), // "sendTelemetry"
QT_MOC_LITERAL(61, 611, 33), // "setLuaStateReloadPermanentScr..."
QT_MOC_LITERAL(62, 645, 18), // "addTracebackDevice"
QT_MOC_LITERAL(63, 664, 10), // "QIODevice*"
QT_MOC_LITERAL(64, 675, 6), // "device"
QT_MOC_LITERAL(65, 682, 21) // "removeTracebackDevice"

    },
    "SimulatorInterface\0started\0\0stopped\0"
    "heartbeat\0loops\0timestamp\0runtimeError\0"
    "error\0lcdChange\0backlightEnable\0"
    "phaseChanged\0phase\0name\0channelOutValueChange\0"
    "index\0value\0limit\0channelMixValueChange\0"
    "virtualSwValueChange\0trimValueChange\0"
    "trimRangeChange\0min\0max\0gVarValueChange\0"
    "outputValueChange\0type\0init\0start\0"
    "const char*\0filename\0tests\0stop\0"
    "setSdPath\0sdPath\0settingsPath\0"
    "setVolumeGain\0setRadioData\0data\0"
    "setAnalogValue\0uint8_t\0int16_t\0setKey\0"
    "key\0state\0setSwitch\0swtch\0int8_t\0"
    "setTrim\0idx\0setTrimSwitch\0trim\0"
    "setTrainerInput\0inputNumber\0setInputValue\0"
    "rotaryEncoderEvent\0steps\0setTrainerTimeout\0"
    "uint16_t\0ms\0sendTelemetry\0"
    "setLuaStateReloadPermanentScripts\0"
    "addTracebackDevice\0QIODevice*\0device\0"
    "removeTracebackDevice"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SimulatorInterface[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      36,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  194,    2, 0x06 /* Public */,
       3,    0,  195,    2, 0x06 /* Public */,
       4,    2,  196,    2, 0x06 /* Public */,
       7,    1,  201,    2, 0x06 /* Public */,
       9,    1,  204,    2, 0x06 /* Public */,
      11,    2,  207,    2, 0x06 /* Public */,
      14,    3,  212,    2, 0x06 /* Public */,
      18,    3,  219,    2, 0x06 /* Public */,
      19,    2,  226,    2, 0x06 /* Public */,
      20,    2,  231,    2, 0x06 /* Public */,
      21,    3,  236,    2, 0x06 /* Public */,
      24,    2,  243,    2, 0x06 /* Public */,
      25,    3,  248,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      27,    0,  255,    2, 0x0a /* Public */,
      28,    2,  256,    2, 0x0a /* Public */,
      28,    1,  261,    2, 0x2a /* Public | MethodCloned */,
      28,    0,  264,    2, 0x2a /* Public | MethodCloned */,
      32,    0,  265,    2, 0x0a /* Public */,
      33,    2,  266,    2, 0x0a /* Public */,
      33,    1,  271,    2, 0x2a /* Public | MethodCloned */,
      33,    0,  274,    2, 0x2a /* Public | MethodCloned */,
      36,    1,  275,    2, 0x0a /* Public */,
      37,    1,  278,    2, 0x0a /* Public */,
      39,    2,  281,    2, 0x0a /* Public */,
      42,    2,  286,    2, 0x0a /* Public */,
      45,    2,  291,    2, 0x0a /* Public */,
      48,    2,  296,    2, 0x0a /* Public */,
      50,    2,  301,    2, 0x0a /* Public */,
      52,    2,  306,    2, 0x0a /* Public */,
      54,    3,  311,    2, 0x0a /* Public */,
      55,    1,  318,    2, 0x0a /* Public */,
      57,    1,  321,    2, 0x0a /* Public */,
      60,    1,  324,    2, 0x0a /* Public */,
      61,    0,  327,    2, 0x0a /* Public */,
      62,    1,  328,    2, 0x0a /* Public */,
      65,    1,  331,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::LongLong,    5,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::SChar, QMetaType::QString,   12,   13,
    QMetaType::Void, QMetaType::UChar, QMetaType::Int, QMetaType::Int,   15,   16,   17,
    QMetaType::Void, QMetaType::UChar, QMetaType::Int, QMetaType::Int,   15,   16,   17,
    QMetaType::Void, QMetaType::UChar, QMetaType::Int,   15,   16,
    QMetaType::Void, QMetaType::UChar, QMetaType::Int,   15,   16,
    QMetaType::Void, QMetaType::UChar, QMetaType::Int, QMetaType::Short,   15,   22,   23,
    QMetaType::Void, QMetaType::UChar, QMetaType::Int,   15,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::UChar, QMetaType::Int,   26,   15,   16,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 29, QMetaType::Bool,   30,   31,
    QMetaType::Void, 0x80000000 | 29,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   34,   35,
    QMetaType::Void, QMetaType::QString,   34,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::QByteArray,   38,
    QMetaType::Void, 0x80000000 | 40, 0x80000000 | 41,   15,   16,
    QMetaType::Void, 0x80000000 | 40, QMetaType::Bool,   43,   44,
    QMetaType::Void, 0x80000000 | 40, 0x80000000 | 47,   46,   44,
    QMetaType::Void, QMetaType::UInt, QMetaType::Int,   49,   16,
    QMetaType::Void, 0x80000000 | 40, QMetaType::Bool,   51,   44,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 41,   53,   16,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 40, 0x80000000 | 41,   26,   15,   16,
    QMetaType::Void, QMetaType::Int,   56,
    QMetaType::Void, 0x80000000 | 58,   59,
    QMetaType::Void, QMetaType::QByteArray,   38,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 63,   64,
    QMetaType::Void, 0x80000000 | 63,   64,

       0        // eod
};

void SimulatorInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SimulatorInterface *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->started(); break;
        case 1: _t->stopped(); break;
        case 2: _t->heartbeat((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 3: _t->runtimeError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->lcdChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->phaseChanged((*reinterpret_cast< qint8(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->channelOutValueChange((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 7: _t->channelMixValueChange((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 8: _t->virtualSwValueChange((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 9: _t->trimValueChange((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 10: _t->trimRangeChange((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint16(*)>(_a[3]))); break;
        case 11: _t->gVarValueChange((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 12: _t->outputValueChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 13: _t->init(); break;
        case 14: _t->start((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 15: _t->start((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 16: _t->start(); break;
        case 17: _t->stop(); break;
        case 18: _t->setSdPath((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 19: _t->setSdPath((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 20: _t->setSdPath(); break;
        case 21: _t->setVolumeGain((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 22: _t->setRadioData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 23: _t->setAnalogValue((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< int16_t(*)>(_a[2]))); break;
        case 24: _t->setKey((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 25: _t->setSwitch((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< int8_t(*)>(_a[2]))); break;
        case 26: _t->setTrim((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 27: _t->setTrimSwitch((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 28: _t->setTrainerInput((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< int16_t(*)>(_a[2]))); break;
        case 29: _t->setInputValue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])),(*reinterpret_cast< int16_t(*)>(_a[3]))); break;
        case 30: _t->rotaryEncoderEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->setTrainerTimeout((*reinterpret_cast< uint16_t(*)>(_a[1]))); break;
        case 32: _t->sendTelemetry((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 33: _t->setLuaStateReloadPermanentScripts(); break;
        case 34: _t->addTracebackDevice((*reinterpret_cast< QIODevice*(*)>(_a[1]))); break;
        case 35: _t->removeTracebackDevice((*reinterpret_cast< QIODevice*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SimulatorInterface::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulatorInterface::started)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SimulatorInterface::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulatorInterface::stopped)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SimulatorInterface::*)(qint32 , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulatorInterface::heartbeat)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SimulatorInterface::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulatorInterface::runtimeError)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SimulatorInterface::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulatorInterface::lcdChange)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SimulatorInterface::*)(qint8 , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulatorInterface::phaseChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SimulatorInterface::*)(quint8 , qint32 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulatorInterface::channelOutValueChange)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SimulatorInterface::*)(quint8 , qint32 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulatorInterface::channelMixValueChange)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (SimulatorInterface::*)(quint8 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulatorInterface::virtualSwValueChange)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (SimulatorInterface::*)(quint8 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulatorInterface::trimValueChange)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (SimulatorInterface::*)(quint8 , qint32 , qint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulatorInterface::trimRangeChange)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (SimulatorInterface::*)(quint8 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulatorInterface::gVarValueChange)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (SimulatorInterface::*)(int , quint8 , qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulatorInterface::outputValueChange)) {
                *result = 12;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SimulatorInterface::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SimulatorInterface.data,
    qt_meta_data_SimulatorInterface,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SimulatorInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SimulatorInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SimulatorInterface.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SimulatorInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 36)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 36;
    }
    return _id;
}

// SIGNAL 0
void SimulatorInterface::started()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SimulatorInterface::stopped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SimulatorInterface::heartbeat(qint32 _t1, qint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SimulatorInterface::runtimeError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SimulatorInterface::lcdChange(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SimulatorInterface::phaseChanged(qint8 _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SimulatorInterface::channelOutValueChange(quint8 _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SimulatorInterface::channelMixValueChange(quint8 _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void SimulatorInterface::virtualSwValueChange(quint8 _t1, qint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void SimulatorInterface::trimValueChange(quint8 _t1, qint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void SimulatorInterface::trimRangeChange(quint8 _t1, qint32 _t2, qint16 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void SimulatorInterface::gVarValueChange(quint8 _t1, qint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void SimulatorInterface::outputValueChange(int _t1, quint8 _t2, qint32 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

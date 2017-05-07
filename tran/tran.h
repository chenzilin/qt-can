#pragma once

#include <QObject>
#include <QTimerEvent>
#include <QSocketNotifier>

#include "../can/can.h"

#define PROPERTY_VALUE_CHANGED(name, v) do { if (m_##name!=(v)) { m_##name=(v); emit name##Changed(v);}}while(0)

class Tran : public QObject
{
    Q_OBJECT

public:
    Tran(const std::string &interface, bool block = true);

    void sendCan();

protected:
    virtual void timerEvent(QTimerEvent *e);

private:
    Can *m_can;
};

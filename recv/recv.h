#pragma once

#include <QObject>
#include <QTimerEvent>
#include <QSocketNotifier>

#include "../can/can.h"

#define PROPERTY_VALUE_CHANGED(name, v) do { if (m_##name!=(v)) { m_##name=(v); emit name##Changed(v);}}while(0)

class Recv : public QObject
{
    Q_OBJECT

public:
    Recv(const std::string &interface, bool block = true);

private slots:
    void onRecvCan(struct can_frame frame);

private:
    Can *m_can;
};

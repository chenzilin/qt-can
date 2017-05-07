#pragma once

#include <QObject>
#include <QTimerEvent>
#include <QSocketNotifier>

#include "can.h"

#define PROPERTY_VALUE_CHANGED(name, v) do { if (m_##name!=(v)) { m_##name=(v); emit name##Changed(v);}}while(0)

class CanRecv : public QObject
{
    Q_OBJECT

public:
    CanRecv(const std::string &interface, bool block = true);

private:
    Can *m_can;
};

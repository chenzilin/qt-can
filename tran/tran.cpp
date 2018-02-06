#include <QDebug>

#include "tran.h"

Tran::Tran(const std::string &interface, bool block)
    :m_can(new Can(interface, block))
{
    m_can->open();

    startTimer(2*1000);
}

void Tran::sendCan()
{
    struct CAN_0x0AA {
        uint8_t data1 : 8;
        uint8_t data2 : 8;
        uint16_t data3: 16;
        uint32_t data4: 32;
    } __attribute__((packed)) *can0AA;

    struct can_frame frame;
    frame.can_id = 0x0AA;
    frame.can_dlc = 8;

    can0AA = (struct CAN_0x0AA *)frame.data;
    can0AA->data1 = 1;
    can0AA->data2 = 1;
    can0AA->data3 = 2;
    can0AA->data4 = 4;

    m_can->send(frame);
}

void Tran::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    sendCan();
}

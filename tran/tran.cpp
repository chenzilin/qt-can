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
    } __attribute__((packed)) *canAA;


    struct can_frame frame;
    frame.can_id = 0xAA;
    frame.can_dlc = 8;

    canAA = (struct CAN_0x0AA *)frame.data;
    canAA->data1 = 1;
    canAA->data2 = 1;
    canAA->data3 = 2;
    canAA->data4 = 4;

    m_can->send(frame);
}

void Tran::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    sendCan();
}

#include <QDebug>

#include "recv.h"

Recv::Recv(const std::string &interface, bool block)
    :m_can(new Can(interface, block))
{
    if (m_can->open())
        connect(m_can, SIGNAL(readyRead(can_frame)), this, SLOT(onRecvCan(struct can_frame)));
}

void Recv::onRecvCan(struct can_frame frame)
{
    qWarning() << "can_id: " << frame.can_id;

    switch (frame.can_id & CAN_SFF_MASK) {
    case 0x0AA:
        qWarning() << "Recv standard Can Frame! ";
        break;
    default:
        break;
    }

    switch (frame.can_id & CAN_EFF_MASK) {
    case 0x0AA:
        qWarning() << "Recv extended Can Frame! ";
        break;
    default:
        break;
    }


}

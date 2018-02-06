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
    if (frame.can_id & CAN_ERR_FLAG) {
        qWarning() << "Recv error Can Frame!";
        return ;
    }

    switch (frame.can_id & CAN_SFF_MASK) {
    case 0x0AA:
        qWarning() << "Recv standard Can Frame! " << "can_id: " << 0x0AA;
        break;
    default:
        break;
    }

    switch (frame.can_id & CAN_EFF_MASK) {
    case 0x0AA:
        qWarning() << "Recv extended Can Frame! " << "can_id: " << 0x0AA;;
        break;
    default:
        break;
    }
}

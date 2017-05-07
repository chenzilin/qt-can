#include <QDebug>

#include "recv.h"

CanRecv::CanRecv(const std::string &interface, bool block)
    :m_can(new Can(interface, block))
{

}

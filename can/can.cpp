#include <QDebug>

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <linux/can.h>
#include <linux/sockios.h>
#include <linux/can/raw.h>

#include "can.h"

Can::Can(const std::string &interface, bool block)
    : m_fd(-1), m_block(block), m_interface(interface)
{
}

Can::~Can()
{
}

void Can::read(int fd)
{
    Q_UNUSED(fd);
    struct can_frame frame;

    auto readCan = [=](auto pframe) {

        int nbytes;
        nbytes = ::read(m_fd, pframe, sizeof(struct can_frame));
        if (nbytes < 0) {
            qWarning() << "Can raw socket read error: " << nbytes;
            return false;
        } else if (nbytes == 0) {
            // no more data
            return false;
        } else if (nbytes < (int)sizeof(struct can_frame)) {
            qWarning() << "Read incomplete CAN frame!\n";
            return false;
        }
        return true;
    };

    while (readCan(&frame)) {
        // error frame
        if (frame.can_id & CAN_ERR_FLAG)
            continue;

        qDebug() << "can_id:" << frame.can_id
                 << "can_dlc:" << frame.can_dlc;
        emit readyRead(frame);
    }
}

bool Can::open()
{
    struct ifreq ifr;
    struct sockaddr_can addr;

    if ((m_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {    // open a socket,raw socket protocol,not BCM
        qWarning() << "Open raw socket failed!";
        return false;
    }

    if (!m_block) {

        int flags = -1;
        if ((flags = fcntl(m_fd, F_GETFL, 0)) < 0) {
            qWarning() << "Get raw socket flags failed!";
            goto err0;
        }
        flags |= O_NONBLOCK;
        if (fcntl(m_fd, F_SETFL, flags) < 0) {
            qWarning() << "Set raw socket flags failed!";
            goto err0;
        }
    }

    strcpy(ifr.ifr_name, m_interface.c_str());
    if (ioctl(m_fd, SIOCGIFINDEX, &ifr) < 0) {
        qWarning() << "ioctl failed!";
        goto err0;
    }
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (bind(m_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        qWarning() << "bind failed!";
        goto err0;
    }

    qDebug() << "Can device open success,"
             << "\nFd =: " << m_fd
             << "\naddr.ifindex =: " << addr.can_ifindex;

    m_canNotifier = new QSocketNotifier(m_fd, QSocketNotifier::Read, this);
    connect(m_canNotifier, SIGNAL(activated(int)), SLOT(read(int)));

    return true;

err0:
    ::close(m_fd);

    return false;
}

bool Can::send(const struct can_frame canFrame)
{
    if(::write(m_fd, &canFrame, sizeof(struct can_frame)) < 0) {
        qWarning() << "Write can frame failed!";
        return false;
    }

    return true;
}

void Can::close()
{
    if (m_fd > 0) {
        ::close(m_fd);
        m_fd = -1;
    }

    if (m_canNotifier) {
        delete m_canNotifier;
        m_canNotifier = NULL;
    }
}

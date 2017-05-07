#pragma once

#include <string>
#include <linux/can.h>

#include <QObject>
#include <QSocketNotifier>

/*
 * 0 = disabled,
 * 1 = enabled (default)
 */
#define CONFIG_RECV_OWN_MSG  1

class Can: public QObject
{
    Q_OBJECT

public:
    Can(const std::string &interface, bool block = true);
    ~Can();

    bool open();
    void close();
    bool send(const struct can_frame canFrame);

signals:
    void readyRead(struct can_frame canFrame);

private slots:
    void read(int fd);

private:
    int m_fd;
    bool m_block;
    std::string m_interface;

    QSocketNotifier *m_canNotifier;
};

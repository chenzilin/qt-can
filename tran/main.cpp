#include <QDebug>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QGuiApplication>
#include <QCommandLineParser>
#include <QQmlApplicationEngine>

#include "tran.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QCommandLineParser parser;
    QCommandLineOption canOption(QStringList() << "d" << "can device name", "specify can device", "can", "vcan0");
    parser.addOption(canOption);
    parser.process(app);

    QString can = "vcan0";
    if (parser.isSet(canOption)) {
        can = parser.value(canOption);
        qDebug() << can;
    }

    Tran tran(can.toStdString());
    Q_UNUSED(tran);

    QQuickView viewer;
    viewer.setSource(QUrl("qrc:///main.qml"));
    viewer.show();

    return app.exec();
}

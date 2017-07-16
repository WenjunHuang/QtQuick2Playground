#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "VideoListModel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<VideoListModel>("an.qt.CModel",1,0,"VideoListModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/video_list_xml.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

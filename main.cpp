#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "backendmanager.h"
#include "loguru.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    loguru::init(argc, argv);
    loguru::add_file("important.log", loguru::Truncate, loguru::Verbosity_MAX);

    BackendManager backendManager;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

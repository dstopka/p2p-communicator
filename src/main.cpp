#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "include/Controller.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    std::unique_ptr<QCoreApplication> app = std::make_unique<QGuiApplication>(argc, argv);
    std::unique_ptr<QQmlApplicationEngine> engine = std::make_unique<QQmlApplicationEngine>();

    qmlRegisterType<Controller>("pl.p2p", 1, 0, "Controller");

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(engine.get(), &QQmlApplicationEngine::objectCreated,
                     app.get(), [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
    engine->load(url);

    return app->exec();
}

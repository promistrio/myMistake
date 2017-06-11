    #include <QGuiApplication>
    #include <QQmlApplicationEngine>

    #include <QQmlContext>

    #include "currentphotopointer.h"

    int main(int argc, char *argv[])
    {


        QGuiApplication app(argc, argv);

        CurrentPhotoPointer photoPointer;
        photoPointer.addPointer(0, 55.7463816, 37.55232);

        QQmlApplicationEngine engine;

        QQmlContext* ctx = engine.rootContext();
        ctx->setContextProperty("photoPointer", &photoPointer);


        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

        if (engine.rootObjects().isEmpty())
            return -1;

        return app.exec();
    }

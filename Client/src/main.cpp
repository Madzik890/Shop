#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <memory>

#include "view/productview.hpp"
#include "view/shoppingcartview.hpp"
#include "controller/ishopcontroller.hpp"
#include "controller/restshopcontroller.hpp"

static std::unique_ptr<Controller::IShopController> ShopController;

inline void createQmlItems() noexcept
{
    ShopController = std::unique_ptr<Controller::IShopController>(new Controller::RestShopController());
}

inline void registerQmlItems() noexcept
{
    qmlRegisterType<View::ProductView>("ProductView", 1, 0, "ProductView");
    qmlRegisterType<View::ShoppingCartView>("ShoppingCartView", 1, 0, "ShoppingCartView");
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/ui/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
    &app, [url](QObject * obj, const QUrl & objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);

    createQmlItems();
    registerQmlItems();

    engine.rootContext()->setContextProperty("ShopController", ShopController.get());
    engine.load(url);

    return app.exec();
}

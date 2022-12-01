#include "restshopcontroller.hpp"

#include <QtDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

using namespace Controller;

RestShopController::RestShopController(QObject *parent) noexcept
    : IShopController(parent),
      _manager(std::make_unique<QNetworkAccessManager>())
{

}

void RestShopController::setAddress(const QString &address)
{
    _address = address;
}

void RestShopController::requestProducts()
{
    constexpr const char *URL = "/getProducts";
    const QNetworkRequest request(QUrl(_address + URL));
    auto socket = _manager->get(request);

    QObject::connect(socket, &QNetworkReply::readyRead, this, &RestShopController::onReadyReadRequestProducts);
}

void RestShopController::postShoppingCart()
{
    constexpr const char *URL = "/order";
}

void RestShopController::addToShoppingCart(const QString &name, const double price, const double weight)
{
    const auto product = Model::Product(name, price, weight);
    _shoppingCart[product]++;
    emit onAppendShoppingCart(product);
}

void RestShopController::removeToShoppingCart(const QString &name, const double price, const double weight)
{
    const auto product = Model::Product(name, price, weight);
    _shoppingCart.remove(product);
    emit onRemoveShoppingCart(product);
}

void RestShopController::onReadyReadRequestProducts()
{
    auto signal = sender();
    auto socket = dynamic_cast<QNetworkReply *>(signal);

    Q_ASSERT(signal);

    const auto data = socket->readAll();
    const auto doc = QJsonDocument::fromJson(data);
    const auto array = doc.array();

    emit onClearProducts();

    for (const auto object : array) {
        try {
            const Model::Product product(object.toObject());
            emit onAppendProduct(product);

        } catch (const std::exception &ex) {
            qCritical() << ex.what();
        }
    }

    socket->deleteLater();
    QObject::disconnect(socket, &QNetworkReply::readyRead, this, &RestShopController::onReadyReadRequestProducts);
}

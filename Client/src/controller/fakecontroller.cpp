#include "fakecontroller.hpp"

#include <QMetaObject>
#include <QtDebug>

using namespace Controller;

void FakeController::setAddress(const QString &address)
{
    (void)address;
}

void FakeController::requestProducts()
{
    QMetaObject::invokeMethod(this, [ = ]() {
        emit onClearProducts();

        const QVector<Model::Product> products = {
            {Model::Product("A", 1.0, 1.23)},
            {Model::Product("B", 2.0, 2.23)},
            {Model::Product("C", 3.0, 3.23)}
        };

        for (const auto &product : products) {
            emit onAppendProduct(product);
        }
    });
}

void FakeController::postShoppingCart()
{

}

void FakeController::addToShoppingCart(const QString &name, const double price, const double weight)
{
    const auto product = Model::Product(name, price, weight);
    emit onAppendShoppingCart(product);
}

void FakeController::removeToShoppingCart(const QString &name, const double price, const double weight)
{
    const auto product = Model::Product(name, price, weight);
    emit onRemoveShoppingCart(product);
}

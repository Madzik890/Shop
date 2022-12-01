#ifndef ISHOPCONTROLLER_H
#define ISHOPCONTROLLER_H

#include <QObject>
#include <QVector>

#include "model/product.hpp"

namespace Controller
{
    class IShopController : public QObject
    {
            Q_OBJECT
        public:
            explicit IShopController(QObject *parent = nullptr) noexcept : QObject(parent) { }
            virtual ~IShopController() noexcept = default;

        public://methods
            Q_INVOKABLE virtual void setAddress(const QString &address) = 0;

        public://method for api requests
            Q_INVOKABLE virtual void requestProducts() = 0;
            Q_INVOKABLE virtual void postShoppingCart() = 0;

            Q_INVOKABLE virtual void addToShoppingCart(const QString &name, const double price, const double weight) = 0;
            Q_INVOKABLE virtual void removeToShoppingCart(const QString &name, const double price, const double weight) = 0;

        signals://products api signals
            void onAppendProduct(const Model::Product &product);
            void onClearProducts();

        signals://shopping cart api signals
            void onAppendShoppingCart(const Model::Product &product);
            void onRemoveShoppingCart(const Model::Product &product);

            void onClearShoppingCart();
    };
}

#endif // ISHOPCONTROLLER_H

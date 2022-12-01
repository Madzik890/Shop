#ifndef RESTSHOPCONTROLLER_H
#define RESTSHOPCONTROLLER_H

#include "ishopcontroller.hpp"
#include "model/product.hpp"

#include <QNetworkAccessManager>
#include <QMap>

namespace Controller
{
    class RestShopController : public IShopController
    {
            Q_OBJECT
        public:
            explicit RestShopController(QObject *parent = nullptr) noexcept;
            ~RestShopController() noexcept = default;

        public://methods
            void setAddress(const QString &address) override;

        public://method for api requests
            void requestProducts() override;
            void postShoppingCart() override;

            void addToShoppingCart(const QString &name, const double price, const double weight) override;
            void removeToShoppingCart(const QString &name, const double price, const double weight) override;

        private slots:
            void onReadyReadRequestProducts();
            //void onReadyReadPost();

        private:
            QString _address = "http://localhost:7212";
            QMap<Model::Product, int> _shoppingCart = {};

        private:
            std::unique_ptr<QNetworkAccessManager> _manager;
    };
}

#endif // RESTSHOPCONTROLLER_H

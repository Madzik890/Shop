#ifndef FAKECONTROLLER_HPP
#define FAKECONTROLLER_HPP

#include "ishopcontroller.hpp"

#include <QHash>

namespace Controller
{
    class FakeController : public IShopController
    {
            Q_OBJECT
        public:
            explicit FakeController(QObject *parent = nullptr) noexcept : IShopController(parent) { }
            ~FakeController() noexcept = default;

        public://methods
            void setAddress(const QString &address) override;

        public://method for api requests
            void requestProducts() override;
            void postShoppingCart() override;

            void addToShoppingCart(const QString &name, const double price, const double weight) override;
            void removeToShoppingCart(const QString &name, const double price, const double weight) override;
    };
}

#endif // FAKECONTROLLER_HPP

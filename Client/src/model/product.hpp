#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QByteArray>
#include <QMetaType>
#include <QJsonObject>

namespace Model
{
    class Product
    {
        public:
            inline bool operator<(const Product &product) noexcept
            {
                return _price > product._price;
            }

            inline bool operator==(const Model::Product &a) noexcept
            {
                return getName() == a.getName() && getPrice() == a.getPrice() && getWeight() == a.getWeight();
            }

            Product() = default;
            Product(const QJsonObject &object);
            Product(const QString &name, const double &price, const double &weight) noexcept;
            ~Product() noexcept = default;

            void setName(const QString &name) noexcept;
            void setPrice(const double &price) noexcept;
            void setWeight(const double &weight) noexcept;

            const QString getName() const noexcept;
            double getPrice() const noexcept;
            double getWeight() const noexcept;

        private:
            QString _name = "";
            double _price = 0.f;
            double _weight = 0.0;
    };
}

inline bool operator<(const Model::Product &a, const Model::Product &b) noexcept
{
    return a.getName() < b.getName() && a.getPrice() < b.getPrice() && a.getWeight() < b.getWeight();
}

Q_DECLARE_METATYPE(Model::Product);

#endif // PRODUCT_H

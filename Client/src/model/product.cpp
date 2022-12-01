#include "product.hpp"

#include <stdexcept>


using namespace Model;

Product::Product(const QString &name, const double &price, const double &weight) noexcept
    : _name(name),
      _price(price),
      _weight(weight)
{

}

Product::Product(const QJsonObject &object)
{
    if (object.isEmpty()) {
        throw std::invalid_argument("Data is invalid!");
    }

    _name = object["name"].toString();
    _price = object["price"].toDouble();
    _weight = object["weight"].toDouble();
}

void Product::setName(const QString &name) noexcept
{
    _name = name;
}

void Product::setPrice(const double &price) noexcept
{
    _price = price;
}

void Product::setWeight(const double &weight) noexcept
{
    _weight = weight;
}

const QString Product::getName() const noexcept
{
    return _name;
}

double Product::getPrice() const noexcept
{
    return _price;
}

double Product::getWeight() const noexcept
{
    return _weight;
}

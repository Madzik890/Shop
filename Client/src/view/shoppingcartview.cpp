#include "shoppingcartview.hpp"

#include <QtDebug>

using namespace View;

ShoppingCartView::ShoppingCartView(QObject *parent) noexcept
    : QAbstractListModel(parent)
{

}

int ShoppingCartView::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return _shoppingCart.size();
}

QVariant ShoppingCartView::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    const auto item = _shoppingVector[index.row()];

    switch (role) {
        case NameRole:
            return QVariant(item.getName());

        case PriceRole:
            return QVariant(item.getPrice());

        case WeightRole:
            return QVariant(item.getWeight());

        case AmountRole:
            return QVariant(_shoppingCart[item]);
    }

    return QVariant();
}

QHash<int, QByteArray> ShoppingCartView::roleNames() const
{
    QHash<int, QByteArray> names;
    names[NameRole] = "name";
    names[PriceRole] = "price";
    names[WeightRole] = "weight";
    names[AmountRole] = "amount";
    return names;
}

void ShoppingCartView::setShopController(Controller::IShopController *shopController) noexcept
{
    Q_ASSERT(shopController);
    _shoppingCart.clear();

    beginResetModel();

    QObject::connect(shopController, &Controller::IShopController::onAppendShoppingCart, this, [ = ](const Model::Product & product) {
        beginResetModel();
        const auto amount = ++_shoppingCart[product];

        if (amount == 1) {
            const auto index = _shoppingCart.size() - 1;
            beginInsertRows(QModelIndex(), index, index);
            endInsertRows();
            _shoppingVector.push_back(product);
        }

        endResetModel();
    });

    QObject::connect(shopController, &Controller::IShopController::onRemoveShoppingCart, this, [ = ](const Model::Product & product) {
        const auto vecSize = _shoppingVector.size();

        for (int i = 0; i < vecSize; i++) {
            if (_shoppingVector[i] == product) {
                beginRemoveRows(QModelIndex(), i, i);
                endRemoveRows();
                _shoppingVector.remove(i);
                _shoppingCart.remove(product);
                break;
            }
        }
    });

    QObject::connect(shopController, &Controller::IShopController::onClearShoppingCart, this, [ = ]() {
        const auto lastIndex = _shoppingCart.size() - 1;
        beginResetModel();
        beginRemoveRows(QModelIndex(), 0, lastIndex);
        endRemoveRows();
        endResetModel();
    });

    endResetModel();
}

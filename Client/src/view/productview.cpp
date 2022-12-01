#include "productview.hpp"

#include <algorithm>
#include <QtDebug>

using namespace View;

ProductView::ProductView(QObject *parent) noexcept
    : QAbstractListModel(parent)
{

}

int ProductView::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return _products.size();
}

QVariant ProductView::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    const auto item = _products.at(index.row());

    switch (role) {
        case NameRole:
            return QVariant(item.getName());

        case PriceRole:
            return QVariant(item.getPrice());

        case WeightRole:
            return QVariant(item.getWeight());
    }

    return QVariant();
}

QHash<int, QByteArray> ProductView::roleNames() const
{
    QHash<int, QByteArray> names;
    names[NameRole] = "name";
    names[PriceRole] = "price";
    names[WeightRole] = "weight";
    return names;
}

void ProductView::setShopController(Controller::IShopController *shopController) noexcept
{
    Q_ASSERT(shopController);
    _products.clear();

    beginResetModel();

    QObject::connect(shopController, &Controller::IShopController::onAppendProduct, this, [ = ](const Model::Product & product) {
        _products.push_back(product);
        const auto index = _products.size();
        beginResetModel();
        beginInsertRows(QModelIndex(), index, index);
        endInsertRows();
        endResetModel();
    });

    QObject::connect(shopController, &Controller::IShopController::onClearProducts, this, [ = ]() {
        const auto lastIndex = _products.size() - 1;
        beginResetModel();
        beginRemoveRows(QModelIndex(), 0, lastIndex);
        endRemoveRows();
        endResetModel();

        _products.clear();
    });

    endResetModel();
}

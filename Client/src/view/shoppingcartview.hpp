#ifndef SHOPPINGCARTVIEW_HPP
#define SHOPPINGCARTVIEW_HPP

#include <QAbstractListModel>
#include <QMap>

#include "controller/ishopcontroller.hpp"

namespace View
{
    class ShoppingCartView : public QAbstractListModel
    {
            Q_OBJECT Q_PROPERTY(Controller::IShopController *shopController WRITE setShopController)
        public:
            enum { NameRole = Qt::UserRole, PriceRole, WeightRole, AmountRole };
            explicit ShoppingCartView(QObject *parent = nullptr) noexcept;
            ~ShoppingCartView() noexcept = default;

            int rowCount(const QModelIndex &parent = QModelIndex()) const override;
            QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
            QHash<int, QByteArray> roleNames() const override;

        public:
            void setShopController(Controller::IShopController *shopController) noexcept;

        private:
            QMap<Model::Product, int> _shoppingCart = {};
            QVector<Model::Product> _shoppingVector = {};
    };
}

#endif // SHOPPINGCARTVIEW_HPP

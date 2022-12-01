#ifndef PRODUCTVIEW_HPP
#define PRODUCTVIEW_HPP

#include <QAbstractListModel>
#include <QVector>

#include "controller/ishopcontroller.hpp"

namespace View
{
    class ProductView : public QAbstractListModel
    {
            Q_OBJECT Q_PROPERTY(Controller::IShopController *shopController WRITE setShopController)
        public:
            enum { NameRole = Qt::UserRole, PriceRole, WeightRole };
            explicit ProductView(QObject *parent = nullptr) noexcept;
            ~ProductView() noexcept = default;

            int rowCount(const QModelIndex &parent = QModelIndex()) const override;

            QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
            QHash<int, QByteArray> roleNames() const override;

        public:
            void setShopController(Controller::IShopController *shopController) noexcept;

        private:
            QVector<Model::Product> _products = {};
    };
}

#endif // PRODUCTVIEW_HPP

import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import ProductView 1.0

Rectangle {
    border.width: 1

    ProductView {
        id: products
        shopController: ShopController
    }

    Component {
        id: productDelegate

        Item {
            height: 120

            Column {
                Text { text: '<b>Produkt:</b> ' + model.name }
                Text { text: '<b>Cena:</b> ' + model.price + ' zł' }
                Text { text: '<b>Waga:</b> ' + model.weight + ' kg' }

                Button {
                    text: "Dodaj do koszyka"
                    onClicked: {
                        ShopController.addToShoppingCart(model.name, model.price, model.weight);
                    }
                }
            }
        }
    }

    ListView {
        id: table
        implicitWidth: parent.width
        implicitHeight: parent.height
        clip: true
        model: products
        delegate: productDelegate
    }    
}

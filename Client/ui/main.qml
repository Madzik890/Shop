import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Shop")

    header: ToolBar {
           RowLayout {
               anchors.fill: parent
               ToolButton {
                   text: qsTr("Lista produktów")
                   onClicked: {
                       ShopController.requestProducts();
                       layout.currentIndex = 0
                   }
               }
               ToolButton {
                   text: qsTr("Koszyk")
                   onClicked: layout.currentIndex = 1
               }
               ToolButton {
                   text: qsTr("Ustawienia")
                   onClicked: layout.currentIndex = 2
               }
           }
       }

       StackLayout {
           id: layout
           anchors.fill: parent

           ProductList {
               width: parent.width
               height: parent.height
           }

           ShoppingCart {
               width: parent.width
               height: parent.height
           }
       }
}

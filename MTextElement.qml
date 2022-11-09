import QtQuick 2.15

Item {
    id : rootItem
    property alias nameText: labelId.text
    property alias valueText: valueLabelId.text
    width : rowId.implicitWidth +20
    height: rowId.implicitHeight +20

    Row {
        id : rowId
        x : 10; y : 10
        spacing: 10


           Rectangle {
               id : text
               width : labelId.implicitWidth +20
               height: labelId.implicitHeight +20
               color : "beige"

               Text {
                   id : labelId
                   anchors.centerIn: parent

               }
           }

           Rectangle {
               id : value
               color : "white"
               width: valueLabelId.implicitWidth +20
               height: valueLabelId.implicitHeight+20

               Text {
                   id : valueLabelId
                   anchors.centerIn: parent
               }
           }
    }

}

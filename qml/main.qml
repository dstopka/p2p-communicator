import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: window
    visible: true
    width: 640
    height: 480
    minimumHeight: 480
    minimumWidth: 640
    title: qsTr("Hello World")

    ListView {
        id: connections
        y: 0
        width: 0.3*parent.width
        height: parent.height - 150
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 0
        delegate: Item {
            x: 5
            width: 80
            height: 40
            Row {
                id: row1
                spacing: 10
                Rectangle {
                    width: 40
                    height: 40
                    color: colorCode
                }

                Text {
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
            }
        }


//        model: ListModel {
//            ListElement {
//                name: "Grey"
//                colorCode: "grey"
//            }

//            ListElement {
//                name: "Red"
//                colorCode: "red"
//            }

//            ListElement {
//                name: "Blue"
//                colorCode: "blue"
//            }

//            ListElement {
//                name: "Green"
//                colorCode: "green"
//            }
//        }
    }

    Rectangle {
        id: newConnection
        x: 0
        y: 0
        width: 0.3*parent.width
        height: 150
        color: "#000000"
    }

    ListView {
        id: messages
        y: 0
        width: 0.5*parent.width
        height: parent.height
        anchors.left: connections.right
        delegate: Item {
            x: 5
            width: 80
            height: 40
            Row {
                id: row2
                spacing: 10
                Rectangle {
                    width: 40
                    height: 40
                    color: colorCode
                }

                Text {
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
            }
        }
//        model: ListModel {
//            ListElement {
//                name: "Grey"
//                colorCode: "grey"
//            }

//            ListElement {
//                name: "Red"
//                colorCode: "red"
//            }

//            ListElement {
//                name: "Blue"
//                colorCode: "blue"
//            }

//            ListElement {
//                name: "Green"
//                colorCode: "green"
//            }
//        }
    }

    ListView {
        id: files
        y: 0
        width: 128
        height: parent.height
        anchors.left: messages.right
        delegate: Item {
            x: 5
            width: 80
            height: 40
            Row {
                id: row3
                spacing: 10
                Rectangle {
                    width: 40
                    height: 40
                    color: colorCode
                }

                Text {
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
            }
        }
//        model: ListModel {
//            ListElement {
//                name: "Grey"
//                colorCode: "grey"
//            }

//            ListElement {
//                name: "Red"
//                colorCode: "red"
//            }

//            ListElement {
//                name: "Blue"
//                colorCode: "blue"
//            }

//            ListElement {
//                name: "Green"
//                colorCode: "green"
//            }
//        }
    }
}

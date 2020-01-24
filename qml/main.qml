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
        height: parent.height - 100
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
        Rectangle {
            id: bgConnections
            anchors.fill: parent
            color: "#3b3b3b"
            z: -1
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
        height: 100
        color: "#3b3b3b"
        Rectangle {
                id: borderBottomNewConnection
                width: parent.width
                height: 1
                anchors.bottom: parent.bottom
                color: "#636363"
            }

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
                    text: qsTr(name)
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
            }
        }
        Rectangle {
            id: bgMessages
            anchors.fill: parent
            color: "#2e2e2e"
            z: -1
            Rectangle {
                    id: borderLeftBgMessages
                    width: 1
                    height: parent.height
                    anchors.left: parent.left
                    color: "#000000"
                }

                Rectangle {
                    id: borderRightBgMessages
                    width: 1
                    height: parent.height
                    anchors.right: parent.right
                    color: "#000000"
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
        width: 0.2*parent.width
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
        Rectangle {
            id: bgFiles
            anchors.fill: parent
            color: "#3b3b3b"
            z: -1
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

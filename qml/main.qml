import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.13

Window {
    id: window
    visible: true
    width: 640
    height: 480
    minimumHeight: 480
    minimumWidth: 640
    title: qsTr("p2p chat")

    //--------------------

    Rectangle {
        id: bgConnections
        color: "#3b3b3b"
        y: 0
        width: 0.3*parent.width
        height: parent.height
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 0

         ListView {
            id: connections
            anchors.fill: parent
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
        }

         Rectangle {
             id: newConnection
             x: 0
             y: 0
             width: parent.width
             height: 100
             color: "#3b3b3b"
             z: 1
             Rectangle {
                     id: borderBottomNewConnection
                     width: parent.width
                     height: 1
                     anchors.bottom: parent.bottom
                     color: "#636363"
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

    //--------------------



    //--------------------

    Rectangle {
        id: bgMessages
        y: 0
        width: 0.5*parent.width
        height: parent.height
        anchors.right: bgFiles.left
        color: "#2e2e2e"

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

        ListView {
                id: messages
                height: parent.height-50
                anchors.top: parent.top
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
        }

        Rectangle {
                id: messagesTextArea
                width: parent.width
                height: 50
                anchors.bottom: parent.bottom
                color: "#2e2e2e"
                Rectangle {
                    id: borderTopMessagesTextArea
                    width: parent.width
                    height: 1
                    anchors.top: parent.top
                    color: "#636363"
                }

                Rectangle {
                    id: bgMessageInput
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    height: parent.height *0.8
                    width: parent.width *0.8
                    radius: 5
                    color: "#242424"
                    ScrollView {
                        id: flickable
                        anchors.fill: parent
                        TextArea {
                            id: messageArea
                            text: "Type your message..."
                            verticalAlignment: TextEdit.AlignVCenter
                            wrapMode: TextArea.Wrap
                            font.pixelSize: 14
                            selectByMouse: true
                            onActiveFocusChanged: {
                                messageArea.text=""
                            }
                            Keys.onReturnPressed: {
                                messageArea.text = ""
                            }
                        }


                    }
                }



        }

    }

    //--------------------

    Rectangle {
        id: bgFiles

        color: "#3b3b3b"
        y: 0
        width: 0.2*parent.width
        height: parent.height
        anchors.right: parent.right

        ListView {
            id: files
            anchors.fill: parent
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
        }
    }
}

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

    MouseArea {
            anchors.fill: parent
            onClicked: forceActiveFocus()
            z:-2
        }

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
                height: parent.height-70
                width: parent.width
                anchors.top: parent.top
                spacing: 5
                model: ListModel {
                    id: messagesModel
                }
                delegate: Rectangle {
                    anchors.topMargin: 10
                    width: messages.width * 0.6
                    height: mssg.contentHeight +12
                    color: msgType == 'sent' ? "#428bad" : "#4db3a3"
                    radius: 8
                    anchors.right: msgType == 'sent' ? parent.right : undefined
                    anchors.left: msgType == 'received' ? parent.left : undefined
                    anchors.rightMargin: msgType == 'sent' ? 10 : undefined
                    anchors.leftMargin: msgType == 'received' ? 10 : undefined
                            TextArea {
                                anchors.fill: parent
                                anchors.leftMargin: 5
                                id: mssg
                                color: 'white'
                                text: msg
                                font.pixelSize: 10
                                wrapMode: Text.Wrap
                                verticalAlignment: Text.AlignVCenter
                                readOnly: true
                            }
                    }
        }

        Rectangle {
                id: messagesTextArea
                width: parent.width
                height: 70
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
                        id: borderLeftMessagesTextArea
                        width: 1
                        height: parent.height
                        anchors.left: parent.left
                        color: "#000000"
                }

                Rectangle {
                        id: borderRightMessagesTextArea
                        width: 1
                        height: parent.height
                        anchors.right: parent.right
                        color: "#000000"
                }

                    ScrollView {
                        id: messageInput
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 15
                        height: parent.height *0.67
                        width: parent.width-70
                        TextArea {
                            id: messageArea
                            placeholderText: "Type your message..."
                            verticalAlignment: TextEdit.AlignVCenter
                            wrapMode: TextArea.Wrap
                            font.pixelSize: 14
                            selectByMouse: true
                            color: "#adadad"
                            background: Rectangle {
                                height: parent.height
                                width: parent.width
                                id: bgMessageInput
                                radius: 5
                                color: "#242424"
                                border.color: '#1f1f1f'
                                border.width: 1
                            }
                            onActiveFocusChanged: {
                                messageArea.text=""
                            }
                            Keys.onReturnPressed: {
                                if (messageArea.text != ""){
                                messagesModel.append({'msgType':'sent', 'msg':qsTr(messageArea.text)})
                                }
                            }
                    }
                }
                Rectangle {
                    id: sendButton
                    anchors.left: messageInput.right
                    anchors.leftMargin: 15
                    anchors.verticalCenter: parent.verticalCenter
                    implicitWidth: 25
                    implicitHeight: 25
                    color: "#636363"
                    radius: 12.5
                    border.color: "#242424"
                    border.width: 1
                    Text {
                        text: ">"
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    MouseArea {
                        id: sendMouseArea
                        hoverEnabled: true
                        anchors.fill: parent
                        onEntered: {
                            parent.color = "#adadad"
                        }
                        onExited: {
                            parent.color = "#636363"
                        }
                        onClicked: {
                            if (messageArea.text != ""){
                            messagesModel.append({'msgType':'sent', 'msg':qsTr(messageArea.text)})
                            forceActiveFocus()
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

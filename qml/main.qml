import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.13

//---------MAIN WINDOW---------------

Window {
    id: window
    visible: true
    width: 640
    height: 480
    minimumHeight: 480
    minimumWidth: 640
    title: qsTr("p2p chat")

    //---------CONNECTIONS PANNEL---------------

    Rectangle {
        id: bgConnections
        color: "#3b3b3b"
        y: 0
        width: 0.3*parent.width
        height: parent.height
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 0

        //---------CONNECTIONS LIST---------------

         ListView {
            id: connections
            width: parent.width
            height: parent.height - 100
            anchors.bottom: parent.bottom
            model: ListModel {
                id: connectionsModel
            }
            delegate: Rectangle {
                height: 50
                width: parent.width
                color: "#3b3b3b"
                Rectangle {
                      width: parent.width
                      height: 1
                      anchors.bottom: parent.bottom
                      color: "#636363"
                }
                Label {
                    id: aliasLabel
                    anchors.top: parent.top
                    text: als
                    color: "#adadad"
                }
                Label {
                    id: ipLabel
                    anchors.top: aliasLabel.bottom
                    text: ip + ":"
                    color: "#adadad"
                }
                Label {
                    id: portLabel
                    anchors.top: aliasLabel.bottom
                    anchors.left: ipLabel.right
                    text: port
                    color: "#adadad"
                }
            }

         }

        //---------NEW CONNECTION---------------

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


             Label {
                id: newConnectionLabel
                text: "New connection"
                color: 'white'
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 3
             }


             TextField {
                 id: newAliasInput
                 anchors.top: newConnectionLabel.bottom
                 anchors.topMargin: 3
                 anchors.horizontalCenter: parent.horizontalCenter
                 width: parent.width * 0.8
                 height: 22
                 placeholderText: "Name"
                 font.pixelSize: 10
                 verticalAlignment: TextInput.AlignVCenter
                 horizontalAlignment: TextInput.AlignHCenter
                 color: "#adadad"
                 background: Rectangle {
                     radius: 8
                     color: "#2e2e2e"
                     border.color: "#242424"
                     border.width: 1
                 }
             }



            TextField {                
                id: newIpInput
                anchors.top: newAliasInput.bottom
                anchors.topMargin: 3
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.1
                placeholderText: "IP Adress"
                height: 22
                width: parent.width * 0.55 -1
                font.pixelSize: 10
                verticalAlignment: TextInput.AlignVCenter
                horizontalAlignment: TextInput.AlignHCenter
                color: "#adadad"
                validator: RegExpValidator { regExp: /([0-9]{1,3}\.){3}[0-9]{1,3}/ }
                background: Rectangle {
                    radius: 8
                    color: "#2e2e2e"
                    border.color: "#242424"
                    border.width: 1
                }
            }


            TextField {
                id: newPortInput
                anchors.top: newAliasInput.bottom
                anchors.topMargin: 3
                anchors.left: newIpInput.right
                anchors.leftMargin: 2
                placeholderText: "Port"
                height: 22
                width: parent.width * 0.25 -1
                font.pixelSize: 10
                verticalAlignment: TextInput.AlignVCenter
                horizontalAlignment: TextInput.AlignHCenter
                color: "#adadad"
                validator: RegExpValidator { regExp: /[0-9]{1,5}/ }
                background: Rectangle {
                    radius: 8
                    color: "#2e2e2e"
                    border.color: "#242424"
                    border.width: 1
                }
            }


            Rectangle {
                id: newConnectionButton
                anchors.top: newPortInput.bottom
                anchors.topMargin: 3
                anchors.horizontalCenter: parent.horizontalCenter
                implicitWidth: newConnectionButtonText.contentWidth + 20
                implicitHeight: 22
                color: "#636363"
                radius: 8
                border.color: "#242424"
                border.width: 1
                Text {
                    id: newConnectionButtonText
                    text: "Connect"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 10
                    color: '#ffffff'
                }
                MouseArea {
                    id: newConnectionButtonMouseArea
                    hoverEnabled: true
                    anchors.fill: parent
                    onEntered: {
                        parent.color = "#adadad"
                        newConnectionButtonText.color = "#242424"
                    }
                    onExited: {
                        parent.color = "#636363"
                        newConnectionButtonText.color = "#ffffff"
                    }
                    onClicked: {
                        if(newPortInput.acceptableInput && newAliasInput.text !== "" && newIpInput.acceptableInput)
                            connectionsModel.append({'ip':newIpInput.text, 'port':newPortInput.text, 'als':newAliasInput.text})
                        }
                    }
                }
            }


         }


    //---------MESSAGES PANNEL---------------

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

        //---------MESSAGES LIST---------------

        ScrollView {
            height: parent.height - 80
            width: parent.width
            anchors.top: parent.top

            ListView {
                id: messages
                anchors.fill: parent
                spacing: 5
                model: ListModel {
                    id: messagesModel
                }
                delegate: Rectangle {
                    anchors.topMargin: 10
                    width: messages.width * 0.6
                    height: mssg.contentHeight + 12
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
                onCountChanged: {
                               var newIndex = count - 1 // last index
                               positionViewAtEnd()
                               currentIndex = newIndex
                           }
                }
        }

        //---------MESSAGES INPUT---------------

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
                            //onActiveFocusChanged: {
                            //    messageArea.text=""
                            //}
                            Keys.onReturnPressed: {
                                if (messageArea.text != ""){
                                messagesModel.append({'msgType':'sent', 'msg':qsTr(messageArea.text)})
                                messageArea.text=""
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
                            messageArea.text=""
                            //forceActiveFocus()
                            }
                        }
                    }
                }
        }

    }

    //---------SENT FILES PANNEL---------------

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

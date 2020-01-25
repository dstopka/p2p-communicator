import QtQuick 2.0

Component {
    Rectangle {
                width: messages.width * 0.8
                height: 40

                color: 'white'
                Text {
                    property string msg: _msg
                    color: 'black'
                    text: msg
                }
            }
}

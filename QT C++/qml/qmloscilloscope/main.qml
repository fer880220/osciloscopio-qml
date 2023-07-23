

import QtQuick 2.0


Item {
    id: main
    width: 600
    height: 400

    ControlPanel {
        id: controlPanel
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 5

        onSignalSourceChanged: {scopeView.axisX().max = sampleCount;}

        onRefreshRateChanged: scopeView.changeRefreshRate(rate);
        onAntialiasingEnabled: scopeView.antialiasing = enabled;
        onOpenGlChanged: {
            scopeView.openGL = enabled;
        }
    }
    Rectangle{
        //anchors.bottom: scopeView.top
        id:rectAzul
        height: parent.height * 0.15
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: controlPanel.right
        color: scopeView.backgroundColor
        opacity: 0.5

        Text {
            id: textInterval
            anchors.centerIn: parent
            text: "Intervalo:"
            font.pointSize: 14
            color: "white"
            opacity: 1
        }

    }

    //![2]
    ScopeView {
        id: scopeView
        anchors.top: rectAzul.bottom
        anchors.bottom: parent.bottom
        //height: parent.height * 0.8
        anchors.right: parent.right
        anchors.left: controlPanel.right
        //height: main.height

        onOpenGLSupportedChanged: {
            if (!openGLSupported) {
                controlPanel.openGLButton.enabled = false
                controlPanel.openGLButton.currentSelection = 0
            }
        }
    }
    //![2]

}

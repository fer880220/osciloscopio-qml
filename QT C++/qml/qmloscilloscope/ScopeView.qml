/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import QtCharts 2.1
import QtQml 2.2

//![1]
ChartView {
    id: chartView
    animationOptions: ChartView.NoAnimation
    theme: ChartView.ChartThemeDark
    property bool openGL: true
    property bool openGLSupported: true

    onOpenGLChanged: {
        if (openGLSupported) {
            series("signal 1").useOpenGL = openGL;

        }
    }
    Component.onCompleted: {
        if (!series("signal 1").useOpenGL) {
            openGLSupported = false
            openGL = false
        }
        dataSource.setSeries( chartView.series(0) )
    }

    MouseArea{
        hoverEnabled: true
        Rectangle{
            // anchors.fill: parent
            property real x0: 0
            property real y0: 0
            onX0Changed: x = x0
            onY0Changed: y = y0
            id: indiRect
            color: "blue"
            opacity: 0.2

            function move(x1,  y1){
                var xMin = Math.min(x1,x) , yMin = Math.min(y1,y),
                        xMax = Math.max(x1,x) , yMax = Math.max(y1,y);
                x = xMin; y = yMin;
                if(x1 > x0 ){
                    width = x1 - x0 ;
                }else{
                    width = x0 - x1 ;
                    x = x1
                }
                if(y1 > y0 ){
                    height = y1 - y0 ;
                }else{
                    height = y0 - y1 ;
                    y = y1
                }


            }

            //z : 2
        }
        anchors.fill: parent
        property int x0: 0
        property int y0: 0
        property int state: 0
        onPressed: {x0 = mouseX}
        onClicked: {
            if (state == 0 && (mouse.modifiers & Qt.ShiftModifier)){
                indiRect.x0 = mouseX; indiRect.y0 = mouseY;
                indiRect.width = indiRect.height = 0 ;
                state = 1;

            }
            else if(state == 1 ){
                state = 2

            }else if(state == 2){
                indiRect.width = 0
                state = 0
            }
        }

        onWheel: {
            if (wheel.modifiers & Qt.ControlModifier){
                if(wheel.angleDelta.y > 0 ){
                    if(axisX.max - axisX.min > 100)
                        axisX.max -= 100
                }
                else
                    axisX.max += 100
            }else{
                if(wheel.angleDelta.y > 0 ){
                    if(axisX.max - axisX.min > 10)
                        axisX.max -= 10
                }
                else
                    axisX.max += 10
            }

        }
        onPositionChanged:{
            if(state == 1){
                indiRect.move(mouseX , mouseY)
                var points = axisX.max - axisX.min
                var pixelsPerPoint = plotArea.width / points
                var intervaloPix = indiRect.width / pixelsPerPoint*Math.pow(10 , -5) / 4
                textInterval.text = "Intervalo: " + String(intervaloPix).substring(0,9)
                        + " s, frec.: "+parseInt(1/intervaloPix) + " Hz"
                //console.log(String(intervaloPix).substring(0,8) )

            }
        }
        onMouseXChanged:{
            if(pressed){
                var d = x0-  mouseX
                x0 = mouseX
                if(d > 0)
                    chartView.scrollRight( d )
                else
                    chartView.scrollLeft( -1 * d )

                //console.log(axisX.min , axisX.max)
            }



        }
    }



    ValueAxis {
        id: axisY1
        min: 0
        max: 3.3
    }

    ValueAxis {
        id: axisX
        min: 0
        max: 1000
    }
    function setMin(min){
        axisX.min = min
    }
    function setMax(max){
        axisX.max = max
    }

    Connections{
        target: dataSource
        onCPointsChanged:{ axisX.max = dataSource.cPoints}
    }

    LineSeries {
        id: lineSeries1
        name: "signal 1"
        axisX: axisX
        axisY: axisY1
        useOpenGL: chartView.openGL
    }



    function setAnimations(enabled) {
        if (enabled)
            chartView.animationOptions = ChartView.SeriesAnimations;
        else
            chartView.animationOptions = ChartView.NoAnimation;
    }

    function changeRefreshRate(rate) {
        //refreshTimer.interval = 1 / Number(rate) * 1000;
    }
}

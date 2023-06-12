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

import QtQuick 2.1
import QtQuick.Layouts 1.0

ColumnLayout {
    property alias openGLButton: openGLButton
    //property alias antialiasButton: true
    spacing: 8
    Layout.fillHeight: true
    signal animationsEnabled(bool enabled)
    signal seriesTypeChanged(string type)
    signal refreshRateChanged(variant rate);
    signal signalSourceChanged(int sampleCount);
    signal antialiasingEnabled(bool enabled)
    signal openGlChanged(bool enabled)

    Text {
        text: dataSource.percent  + "%"
        font.pointSize: 18
        color: "white"
    }

    MultiButton {
        text: ""
        items: ["Stop", "Run"]
        currentSelection: 1
        onSelectionChanged: {
            if(currentSelection == 0){
                dataSource.beginCollect()
                //text = "Stop"
            }else{
                dataSource.endCollect()
                //text = "Run"
            }
        }
    }

    MultiButton {
        id: openGLButton
        text: "OpenGL: "
        items: ["false", "true"]
        currentSelection: 1
        onSelectionChanged: openGlChanged(currentSelection == 1);
    }



    MultiButton {
        id: sampleCountButton
        text: "Samples: "
        items: ["6", "24","128", "1000", "10000", "100000"]
        currentSelection: 2
        onSelectionChanged: signalSourceChanged( selection );
    }   
}

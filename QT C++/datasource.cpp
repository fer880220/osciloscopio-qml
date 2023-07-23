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

#include "datasource.h"

#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtCore/QDebug>
#include <QtCore/QtMath>
#include "tft43A.h"

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

#define UN_MILLON 500000

DataSource::DataSource(QQuickView *appViewer, QObject *parent) :
    QObject(parent),
    m_appViewer(appViewer),
    m_index(-1),
    m_series(nullptr),
    mPercent(0),
    maxPoints(UN_MILLON)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();
    qRegisterMetaType< QVector<QPointF> >();

    mVector.reserve( UN_MILLON );

    connect(&hiloRecibidor, SIGNAL(dataReady(QVector<QPointF>)) ,
            this, SLOT(onDataReady(QVector<QPointF>)));
}

DataSource::~DataSource()
{
    hiloRecibidor.bCorriendo = false ;
    hiloRecibidor.exit();
}

void DataSource::update()
{    
        // Use replace instead of clear + append, it's optimized for performance
        m_series->replace(mVector);
}

void DataSource::setSeries(QAbstractSeries *series)
{
    m_series = (QXYSeries*)series ;

}

void DataSource::onDataReady(QVector<QPointF> v)
{
    if(mVector.size() < maxPoints){
        QVector<QPointF> v2;
        int len = v.size();
        for(int i = 0 ; i < len ; i++)
            v2.push_back(QPointF(i,v[i].ry()));
        m_series->replace(v2);

        mVector += v ;

        qreal percent = mVector.size() * 1.0 /maxPoints * 100 ;
        setPercent( percent ) ;
    }
    else{
        endCollect();
        emit percentChanged(100);
        emit cPointsChanged(mVector.size());
    }

}

void DataSource::beginCollect()
{
    maxPoints = UN_MILLON ;
    foreach (QVector<QPointF> row, m_data)
        row.clear();
    m_data.clear();

    mVector.clear();

    hiloRecibidor.bCorriendo = true ;
    hiloRecibidor.start();
}

void DataSource::endCollect()
{
    hiloRecibidor.bCorriendo = false ;
    hiloRecibidor.exit();
    maxPoints = mVector.size() ;
    m_series->replace(mVector);
   // update();
}



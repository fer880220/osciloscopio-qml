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

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QtCore/QObject>
#include <QtCharts/QAbstractSeries>
#include<hilorecibidor.h>
#include <QtCharts/QXYSeries>
QT_BEGIN_NAMESPACE
class QQuickView;
QT_END_NAMESPACE



QT_CHARTS_USE_NAMESPACE

class DataSource : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int percent READ percent WRITE setPercent NOTIFY percentChanged)
    Q_PROPERTY(int cPoints READ cPoints  NOTIFY cPointsChanged)
public:
    explicit DataSource(QQuickView *appViewer, QObject *parent = 0);
     ~DataSource();
//Q_SIGNALS:
signals:
    //void mVectorFull();
    void percentChanged(int);
    void cPointsChanged(int);
public slots:   

    void setSeries(QAbstractSeries *series);
    void onDataReady(QVector<QPointF> v);
//slots implementados 2023
    void beginCollect();
    void endCollect();

    qreal percent(){return mPercent ;}
    void setPercent(qreal p){ mPercent = p ; emit percentChanged(p);}

    int cPoints(){return mVector.size();}
private:
    QQuickView *m_appViewer;
    QList<QVector<QPointF> > m_data;
    int m_index;
    bool goodConn;
    QXYSeries  *m_series;
    HiloRecibidor hiloRecibidor;
    QVector<QPointF> mVector ;
    int mPercent;
    int maxPoints;

     void update();
};

#endif // DATASOURCE_H

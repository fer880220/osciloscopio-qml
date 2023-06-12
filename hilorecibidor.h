#ifndef HILORECIBIDOR_H
#define HILORECIBIDOR_H

#include <QObject>
#include<QThread>
#include<QVector>
#include<QPointF>

class HiloRecibidor : public QThread
{
    Q_OBJECT
public:
    bool bCorriendo;
    HiloRecibidor();
    ~HiloRecibidor();
    void run();
private:
    bool goodConn;
signals:
    void dataReady(QVector<QPointF> v);
};

#endif // HILORECIBIDOR_H

#include "hilorecibidor.h"
#include "tft43A.h"


HiloRecibidor::HiloRecibidor()
{
    goodConn = TFT_startComm();
}

HiloRecibidor::~HiloRecibidor()
{
    TFT_closeComm();
}
#define BYTES_TO_READ 1000
void HiloRecibidor::run()
{
    QVector<QPointF> points;
    int j = 0 ;
    double vals[2];
    int len;
    points.reserve(BYTES_TO_READ);
    while(this->bCorriendo){
        //msleep(1000/60);
        if(goodConn){
            points.clear();
            for(int i = 0 ; i < BYTES_TO_READ ; i++){
                TFT_read(vals, len);
                points.append(QPointF(j+i, vals[0]));
            }
            j += BYTES_TO_READ ;
            emit dataReady( points );

        }
    }
}

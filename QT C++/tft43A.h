#ifndef TFT43A_H
#define TFT43A_H


 bool TFT_startComm();
 bool TFT_closeComm();

 void TFT_read(double *buf, int &ibuf);
 void TFT_send( char*buf,
                        unsigned short int *param,
                        int cbuf,int cparam);
#endif // TFT43A_H


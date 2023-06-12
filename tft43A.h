#ifndef TFT43A_H
#define TFT43A_H




//---------------------------------------------------------------
#include <windows.h>
//typedef enum {ACK=6,NAK=0x15,NOREAD=0}TREAD;

//-------------------------------------------------------------

 bool TFT_startComm();
 bool TFT_closeComm();

 void TFT_read(double *buf, int &ibuf);
 void TFT_send(HANDLE hCom, char*buf,
                        unsigned short int *param,
                        int cbuf,int cparam);
#endif // TFT43A_H


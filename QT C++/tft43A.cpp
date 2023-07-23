#include<QDebug>
#include "tft43A.h"
#include <windows.h>
//---------------------------------------------------------------
OVERLAPPED osReader;
HANDLE hCom;
void TFT_send(char*buf,
                       unsigned short int *param,
                       int cbuf, int cparam)
{//DC1|len|...DATA...|bcc
    DWORD written;
    unsigned char dc1=0x11;
    unsigned char bcc=0,len=cbuf+cparam*2,i;
    WriteFile(hCom, &dc1, 1, &written, NULL);
    bcc+= dc1;
    WriteFile(hCom, &len, 1, &written, NULL);
    bcc+=len;
    for(i=0; i < cbuf; i++) // #GD -> dibujar l'inea
    {
      WriteFile(hCom, &buf[i], 1, &written, NULL);
      bcc+=buf[i];
    }
    for(i=0;i<cparam;i++)
    {
        len=param[i];
        WriteFile(hCom, &len, 1, &written, NULL);
        bcc+=len;
        len=param[i]>>8;
        WriteFile(hCom, &len, 1, &written, NULL);
        bcc+=len;
    }
    WriteFile(hCom, &bcc, 1, &written, NULL);
}
//---------------------------------------------------------------


  bool TFT_startComm()
  {
    DCB setting={0};
    osReader.Offset=0;
    osReader.OffsetHigh=0;
   osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
   if (osReader.hEvent == NULL)
      return 0;
   /*Serial<id=0x24819a5b4f0, open=True>
    * (port='COM5', baudrate=115200, bytesize=8,
    * parity='N', stopbits=1, timeout=None, xonxoff=False, rtscts=False, dsrdtr=False)
*/
    hCom=CreateFile(TEXT("COM5"),
                                  GENERIC_READ,0,
                                  NULL, OPEN_EXISTING,
                                  0,//0= no overlaped; 1 = overlaped
                                  NULL);
    GetCommState(hCom, &setting); // obtener config actual

    setting.DCBlength= 28;
    setting.BaudRate= 115200;
    setting.fBinary= 1;
	setting.fDtrControl= 1;
	setting.fRtsControl= 1;
	setting.ByteSize= 8;
	setting.ErrorChar= 4294967289;
    setting.EofChar= 64;
	
    setting.fParity= 0;
    setting.fOutxCtsFlow= 0;    
	setting.fOutxDsrFlow= 0;    
    setting.fDsrSensitivity= 0;
    setting.fTXContinueOnXoff= 0;
    setting.fOutX= 0;   
	setting.fInX= 0;
    setting.fErrorChar= 0;    
	setting.fNull= 0;    
    setting.fAbortOnError= 0;
    setting.fDummy2= 0;    
	setting.wReserved= 0;
    setting.XonLim= 0;    
	setting.XoffLim= 0;    
    setting.Parity= 0;    
	setting.StopBits= 0;
    setting.XonChar= 0;    
	setting.XoffChar= 0;    
    setting.EvtChar= 0;    
	setting.wReserved1= 0;


    SetCommState(hCom, &setting); // establecer  new config.
    return true;
  }
  bool TFT_closeComm()
  {
        return CloseHandle(hCom);
  }
//-----------------------------------------------------------------
  void TFT_read(double *buf, int &ibuf)
  {
      DWORD dwRead;
      const double fact16 = 3.3/65535,
              fact12 = 0.0032258064516129;
      ibuf=0;
      unsigned char lpBuf[20]={0};

      if (!ReadFile(hCom, lpBuf, 2, &dwRead, &osReader))
           //"MALA LECTURA");
           return ;

      lpBuf[2] = lpBuf[1];lpBuf[1] = lpBuf[0];lpBuf[0] = lpBuf[2];

      //qDebug()<<""<<lpBuf[0]<<lpBuf[1]<<lpBuf[2]<<lpBuf[3]<<lpBuf[4];
      //qDebug()<<"qreal: "<<*((quint16*)lpBuf) * fact16 ;
    buf[0] = *((quint16*)lpBuf) * fact16;
    ibuf = 1 ;

  }

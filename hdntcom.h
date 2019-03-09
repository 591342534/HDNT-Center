#ifndef HDNTCOM_H
#define HDNTCOM_H

#include "hdntcom_global.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtSerialPort/qserialport.h>
#include <QThread>
#include <functional>
#include "workthread.h"

class SerialSetInfo{
public:
    QString ComName;
    QString BaudRate;
    QString DataBit;
    QString StopBit;
    QString Parity;
    QString Protocol;
};

class HDNTCOMSHARED_EXPORT hdntCom:public QThread
{
    Q_OBJECT
public:
    hdntCom(QObject *parent);
    ~hdntCom();

    int Init(SerialSetInfo *SerialSetParm);  //Init the serial port
    int Open();  //open
    int Close();

    int Write(QByteArray *Dat);
    QByteArray Read();

    bool isOpen();
    QByteArray ComData;
    uint8_t *uComData;
    uint16_t ComDataLength;

    QSerialPort * m_serial = nullptr;
    QSerialPort * mth_serial = nullptr;

    bool mThreadRun=true;

    bool OpenFlag=false;


    void setCallback(std::function<void(void)> func);
private slots:
    void ReceiveComData(void);

signals:
    void SendReceiveData(QByteArray Dat);
    void Sg_ComReady(void);

private:



    std::function<void(void)> m_func;
    uint8_t BufferNum=2;
    bool SolveFlag=true;
    QByteArray Buffer1,Buffer2;

    QThread *Th_ComWork;
    WorkThread *m_ComThread;

protected:
    void run();
};

#endif // HDNTCOM_H

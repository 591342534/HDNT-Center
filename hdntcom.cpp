#include "hdntcom.h"
#include <QDebug>

hdntCom::hdntCom(QObject *parent)
    //: QThread(parent)
{
    m_serial =new QSerialPort;
    m_ComThread=new WorkThread(this);
}
hdntCom::~hdntCom()
{
    delete m_serial;
}

int hdntCom::Init(SerialSetInfo *SerialSetParm){
    m_serial->setPortName(SerialSetParm->ComName);
    m_serial->setBaudRate(SerialSetParm->BaudRate.toInt());

    switch (SerialSetParm->DataBit.toInt()) {
    case 5: m_serial->setDataBits(QSerialPort::Data5); break;
    case 6: m_serial->setDataBits(QSerialPort::Data6); break;
    case 7: m_serial->setDataBits(QSerialPort::Data7); break;
    case 8: m_serial->setDataBits(QSerialPort::Data8);; break;
    default:
        break;
    }

    if(SerialSetParm->Parity=="None"){m_serial->setParity(QSerialPort::NoParity);}
    else if(SerialSetParm->Parity=="Even"){m_serial->setParity(QSerialPort::EvenParity);}
    else if(SerialSetParm->Parity=="Odd"){m_serial->setParity(QSerialPort::OddParity);}
    else if(SerialSetParm->Parity=="Mark"){m_serial->setParity(QSerialPort::MarkParity);}
    else if(SerialSetParm->Parity=="Space"){m_serial->setParity(QSerialPort::SpaceParity);}

    switch (SerialSetParm->StopBit.toInt()) {
    case 1:m_serial->setStopBits(QSerialPort::OneStop);break;
    case 2:m_serial->setStopBits(QSerialPort::TwoStop);break;
    default:
        break;
    }

    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    return true;
}
int hdntCom::Open(){
    if (m_serial->open(QIODevice::ReadWrite)) {
        OpenFlag=true;
        auto func = [&](){ReceiveComData();};
        m_ComThread->setCallback(func);

        Th_ComWork=new QThread;
        m_ComThread->moveToThread(Th_ComWork);
        Th_ComWork->start();
        connect(m_serial, SIGNAL(readyRead()), m_ComThread, SLOT(Slot_RecieveDat()));

        return true;
    }else {
        OpenFlag=false;
        return false;

    }

}
int hdntCom::Close(){
    if (m_serial->isOpen()) {
        m_serial->close();
        OpenFlag=false;
        return true;
    }else{
        return false;
    }
}

int hdntCom::Write(QByteArray *Dat){
    if (m_serial->isOpen()) {
        m_serial->write(Dat->data(), Dat->size());
    }
    return true;
}
QByteArray hdntCom::Read(){

    return m_serial->readAll();
}
void hdntCom::ReceiveComData(void){
    ComData.clear();
    ComData =m_serial->readAll();
    ComDataLength=ComData.length();
    emit Sg_ComReady();
    qDebug()<<"Com Thread:"<<QThread::currentThreadId();
}

bool hdntCom::isOpen(){
    if(m_serial->isOpen()){
        return true;
    }else{
        return false;
    }
}

void hdntCom::run(){
    mth_serial =new QSerialPort;
    mth_serial=m_serial;
    mth_serial->open(QIODevice::ReadWrite);
    connect(mth_serial,SIGNAL(readyRead()),this,SLOT(ReceiveComData()));//有数据就读
}
void hdntCom::setCallback(std::function<void(void)> func)
{
    m_func = func;
}

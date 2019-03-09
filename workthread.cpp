#include "workthread.h"

WorkThread::WorkThread(QObject *parent)
{
   m_func=nullptr;
}

void WorkThread::setCallback(std::function<void(void)> func){
    m_func=func;
}


void WorkThread::Slot_RecieveDat(){
   m_func();
}

#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QObject>
#include <QtCore/qglobal.h>
#include <functional>

class WorkThread:public QObject
{
    Q_OBJECT
public:
    WorkThread(QObject *parent);
    void setCallback(std::function<void(void)> func);

public slots:
    void Slot_RecieveDat();

signals:


private:
    std::function<void(void)> m_func;
};

#endif // WORKTHREAD_H

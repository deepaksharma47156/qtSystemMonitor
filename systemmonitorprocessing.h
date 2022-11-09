#ifndef SYSTEMMONITORPROCESSING_H
#define SYSTEMMONITORPROCESSING_H

#include <QObject>
#include <QTimer>



struct systemProperty
{
    Q_GADGET
    Q_PROPERTY(QString cpuload MEMBER aqs_cpuload)
    Q_PROPERTY(QString thread MEMBER aqs_totalThreads)
    Q_PROPERTY(QString process MEMBER aqs_totalProcess)
    Q_PROPERTY(QString memoryavailable MEMBER aqs_memoryAvailableKb)
    Q_PROPERTY(QString memoryused MEMBER aqs_memoryUsedKb)
    Q_PROPERTY(QString disktotal MEMBER aqs_diskInfoTotalMB)
    Q_PROPERTY(QString diskfree MEMBER aqs_diskInfoAvailableMB)
    Q_PROPERTY(QString diskused MEMBER aqs_diskInfoUsedMB)

public:

    QString aqs_cpuload;
    QString aqs_totalThreads;
    QString aqs_totalProcess;
    QString aqs_memoryAvailableKb;
    QString aqs_memoryUsedKb;
    QString aqs_diskInfoTotalMB;
    QString aqs_diskInfoAvailableMB;
    QString aqs_diskInfoUsedMB;

};

class systemMonitorProcessing:public QObject
{
    Q_OBJECT
    /*it can be done individually for each property and notify
     * will be updated on chagne but i am updating the param in struct*/
    Q_PROPERTY(systemProperty systemProp READ getSystemProp WRITE setSystemProp NOTIFY systemPropChanged)

public :
    systemMonitorProcessing();

signals :
    void systemPropChanged();

public slots:
    void processSystemmonitorParam();

private :
    QTimer *timer ;
    void initRefresh();
    void setSystemProp(systemProperty a_sysProp);
    void updateCPUInfo();
    void updateThreadAndProcessInfo();
    void updateMemoryInfo();
    void updateDiskInfo();
    systemProperty getSystemProp();
    systemProperty x_systemProp;

};

#endif // SYSTEMMONITORPROCESSING_H

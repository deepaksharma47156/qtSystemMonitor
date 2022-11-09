#include "systemmonitorprocessing.h"
#include<QDebug>
#include <QProcess>
#include <QStorageInfo>
#include<QThread>

/*****Macros*********/
#define KBBYTE_TO_MB_CONVERTER (1024*)
#define BYTE_TO_MB_CONVERTER (1024*1024)
#define PERIODIC_PROPERTY_REFRESH_MS (2000)
#define EnableDebugLog 1


systemMonitorProcessing::systemMonitorProcessing()
{

    x_systemProp.aqs_cpuload = "NA";
    x_systemProp.aqs_totalThreads = "NA";
    x_systemProp.aqs_totalProcess = "NA";
    x_systemProp.aqs_memoryAvailableKb = "NA";
    x_systemProp.aqs_memoryUsedKb = "NA";
    x_systemProp.aqs_diskInfoTotalMB = "NA";
    x_systemProp.aqs_diskInfoAvailableMB = "NA";
    x_systemProp.aqs_diskInfoUsedMB = "NA";

    initRefresh();


}

void systemMonitorProcessing::initRefresh()
{
    /*timer to periodically refresh the system param */
    timer = new QTimer(this);
    if(NULL != timer)
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(processSystemmonitorParam()));
        timer->start(PERIODIC_PROPERTY_REFRESH_MS);
    }
    else
    { /*in case timer creation fail then display the data */
        processSystemmonitorParam();
    }

}

void systemMonitorProcessing::processSystemmonitorParam()
{

   /*refresh system information */
    systemProperty a_sysProp;
    updateCPUInfo();
    updateThreadAndProcessInfo();
    updateMemoryInfo();
    updateDiskInfo();

    /*update to QML */
    setSystemProp(a_sysProp);

}

void systemMonitorProcessing::setSystemProp(systemProperty a_sysProp)
{
 qDebug()<<a_sysProp.aqs_cpuload;
   /*x_systemProp already populated in processSystemmonitorParam,
    * only emit signal is to update parram in QML */
    emit systemPropChanged();

}

systemProperty systemMonitorProcessing::getSystemProp() {
    return x_systemProp;
}


/*cpu load using top command */
void systemMonitorProcessing::updateCPUInfo()
{
    QString qs_cpuload ;
    QProcess p;
    /*cpu load */
    p.start("sh", QStringList() << "-c" << "top -bn1 | grep  %Cpu | awk '{print 100-($8+$10)}'");
    p.waitForFinished();

    qs_cpuload = p.readAllStandardOutput();
    if(100 >= QString(qs_cpuload).toInt() || 0 >= QString(qs_cpuload).toInt())
    {
        x_systemProp.aqs_cpuload = qs_cpuload;
    }
    else
    {
        /*display the oldervalue when data is wrong */
    }
  p.close();

}

/*finding process and thread information from PS command */
void systemMonitorProcessing::updateThreadAndProcessInfo()
{
    QProcess p;

      /*total process and thread information */
      p.start("sh", QStringList() << "-c" <<"ps -A --no-headers |wc -l");
      p.waitForFinished();
      x_systemProp.aqs_totalProcess = p.readAllStandardOutput();

      p.start("sh", QStringList() << "-c" <<"ps -AL --no-headers |wc -l");
      p.waitForFinished();

      x_systemProp.aqs_totalThreads = p.readAllStandardOutput();
#if EnableDebugLog
      qDebug()<<" totalProcess "<< x_systemProp.aqs_totalProcess
             <<" totalThreads "<<x_systemProp.aqs_totalThreads;
#endif
        p.close();

}

/*meminfo using /proc/meminfo */
void systemMonitorProcessing::updateMemoryInfo()
{

    QProcess p;
      /*meminfo */
      p.start("awk", QStringList() << "/MemTotal/ { print $2 }" << "/proc/meminfo");
      p.waitForFinished();
      x_systemProp.aqs_memoryAvailableKb = p.readAllStandardOutput();

       /*cached memory can also be accounted as it can be freed from kernel any time*/
      p.start("awk", QStringList() << "/MemFree/ { print $2 }" << "/proc/meminfo");
      p.waitForFinished();
      x_systemProp.aqs_memoryUsedKb = p.readAllStandardOutput();
#if EnableDebugLog
      qDebug() <<"memory total KB "<<x_systemProp.aqs_memoryAvailableKb
              <<"memory free KB "<<x_systemProp.aqs_memoryUsedKb;
#endif

      p.close();
}
/*updating disk info param
 /proc/meminfo can also be used to get memory but using QstorageInfo libs*/
void systemMonitorProcessing::updateDiskInfo()
{

    QStorageInfo qs_storage = QStorageInfo::root();

    if (true == qs_storage.isReadOnly())
    {
        qDebug() << "isReadOnly:" << qs_storage.isReadOnly();
    }
    else
    {
        x_systemProp.aqs_diskInfoTotalMB = QString::number(qs_storage.bytesTotal()/BYTE_TO_MB_CONVERTER);

        x_systemProp.aqs_diskInfoAvailableMB = QString::number(qs_storage.bytesAvailable()/BYTE_TO_MB_CONVERTER );
        x_systemProp.aqs_diskInfoUsedMB = QString::number((qs_storage.bytesTotal() - qs_storage.bytesAvailable())/BYTE_TO_MB_CONVERTER );
#if EnableDebugLog
        qDebug() << "Total Size :" << x_systemProp.aqs_diskInfoTotalMB << " MB"
                 << "Available Size:" << x_systemProp.aqs_diskInfoAvailableMB << " MB"
                 << "Used Size:" <<x_systemProp.aqs_diskInfoUsedMB << " MB";
#endif
    }
}



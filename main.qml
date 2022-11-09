import QtQuick 2.15
import QtQuick.Window 2.15

import org.sampleapp.example 1.0

Window {
    width : parentColumn.implicitWidth +50
    height: parentColumn.implicitHeight +50
    visible: true
    color : "black"
    title: qsTr("System Monitor application")

    Systemmonitor{
        id:systemmonitor

    }

    Column
    {
        id  : parentColumn
        spacing: 20


        /* CPU load */
        MTextElement{
            nameText: "CPU Load"
            valueText: systemmonitor.systemProp.cpuload

        }
        /*Number of process and Threads */
        Row
        {
            /* Total process */
            MTextElement{
                nameText: "Total Process"
                valueText: systemmonitor.systemProp.process

            }
            /* Total Threads*/
            MTextElement{
                nameText: "Total Threads"
                valueText: systemmonitor.systemProp.thread

            }
        }

        /*Total available memory and used memrory */
        Row
        {
            /* Total available memory */
            MTextElement{
                nameText: "Available Memory KB"
                valueText: systemmonitor.systemProp.memoryavailable

            }
            /* Total used memory */
            MTextElement{
                nameText: "Used Memory KB"
                valueText: systemmonitor.systemProp.memoryused

            }
        }

        /*Disk Information */
        Row
        {
            /* Total Disk space */
            MTextElement{
                nameText: "Total Disk Space MB"
                valueText: systemmonitor.systemProp.disktotal

            }
            /* Total available space */
            MTextElement{
                nameText: "Available Space MB"
                valueText: systemmonitor.systemProp.diskused

            }

            /* Total used space */
            MTextElement{
                nameText: "Used Space MB "
                valueText: systemmonitor.systemProp.diskfree

            }
        }

    }


}

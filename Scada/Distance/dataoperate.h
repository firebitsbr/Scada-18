#ifndef DATAOPERATE_H
#define DATAOPERATE_H

#include <QString>
#include <QTime>

class DataOperate
{
public:
    DataOperate();
    ~DataOperate();
   static double getDistance(QString data);                   //�����ȡ����
   static QString getMac(QString data);                       //mac��ַ��ȡ����
   static double getTime();
};

#endif // DATAOPERATE_H

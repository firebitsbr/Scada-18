
/*
**  @description:
**	�Ǳ������࣬���ڴ����Ǳ������࣬�������Ǳ�Ļ�������
**  @parameter:NULL
**
**  @return value:NULL
**
**  author:teddy.tu
**  date:
**
**  Copyright(C) teddy.tu
**  All rights reserved.
*/ 
#ifndef QMETER_H
#define QMETER_H

#include <QtWidgets/QWidget>
#include <qpoint.h>

class QMeter : public QWidget
{
	Q_OBJECT

public:
	//�Ǳ�����
	enum Type{
		EngineMeter = 1,	  //Enginemeter
		FuelLevel	= 2,	 // fuelLevel
        Meter		= 3,     //dial
        Thermometer	= 4,     //thermo-graph
        Lamp		= 5      //pilot lamp
	};
	//����״̬
	enum State{
		NoData = 0,		  //������
		Normal = 1,		  //��������
		Warning = 2,	  //Ԥ��
		Alarm = 3		  //����
	};
	QMeter(QString name ,QString title,Type type = Meter, QWidget *parent = 0);
	virtual ~QMeter();

	Type getType() {return m_type;}
	State getState() {return m_state;}
	QString getName() {return m_name;}
	QString getTitle() { return m_title;}
	QString getChannel() { return m_channel;}
	double getValue() {return m_value;}
	double getScale() {return m_scale;}
	QPoint getCenter() {return m_center;}
	bool getVisiable() {return m_visible;}

	//virtual double Radius() const = 0;  
	//virtual int getComponents() const = 0;
 //   virtual QString getUnits()const = 0;
	//virtual int Precision() const =0;
	//virtual double Rate() const = 0;
	//virtual int startAngle() const =0 ;
 //   virtual int endAngle() const = 0;
	//virtual double Factor() const =0;
	//virtual int InnerScaleSteps() =0;
	//virtual int Strech() =0;
	//virtual void changeValue(int ) = 0;

protected:
	virtual void paintEvent(QPaintEvent *) = 0;	  //���麯���������Ǳ�����QWidget��paintEvent
signals:
	void ScaleChanged(double);
	void stateChanged();
	void visiableChanged();
public slots:
	virtual void setType(Type) = 0;
	virtual void setState(State) = 0;
	virtual void setName(QString) = 0;
	virtual void setTitle(QString) = 0;
	virtual void setChannel(QString) = 0;
	virtual void setValue(double) = 0;
	virtual void setScale(double) = 0 ;
	virtual void setCenter(QPoint) = 0;
	virtual void setCenter(double,double) = 0;
	virtual void setMeterVisible(bool) = 0;   
protected:

	QString m_name;			 //�Ǳ�����ֻ�����ַ�������
	Type m_type;			 //�Ǳ�����
	State  m_state;			 //����״̬
	QString m_title;		 //�Ǳ���ʾ���� (���������ĺ��ֺ��ַ�������
	QString m_channel;		 //��ȡ����ͨ�� ����Ӳ������
	double m_value;			 //�Ǳ�ǰֵ
	double m_scale;			 //��ʾ����
	QPoint m_center;		 //���ĵ�
	bool m_visible;		     //�Ƿ�����

};

#endif // QMETER_H

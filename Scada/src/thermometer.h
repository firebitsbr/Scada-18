#ifndef THERMOMETER_H
#define THERMOMETER_H

#include "qmeter.h"
#include <qpen.h>
class ThermoMeter : public QMeter
{
	Q_OBJECT

public:
	enum Scale{
		Major = 1,
		Minor = 2
	};
	ThermoMeter(QString name = "ThermoMeter", QString title = QStringLiteral("�¶ȼ�"), QMeter::Type type = QMeter::Thermometer, QWidget *parent = 0);
	~ThermoMeter();
	int getWidth() const {return m_width;}
	int getHeight() const { return m_heigth;}
	int MinValue() const {return m_minValue;}
	int MaxValue() const {return m_maxValue;}
	QColor LiquidColor() const {return m_liquidColor;}
	double ScaleSteps(Scale);
	/*double MinorScaleSteps() {return m_minorSteps;}*/
	int ScaleLength(Scale) const;
	int ScaleWidth(Scale) const;
private:
	int m_width;		//�����Ǳ�Ŀ�ܿ��
	int m_heigth;		//�����Ǳ�Ŀ�ܸ߶�
	int m_minValue;		//��С����
	int m_maxValue;		//�������
	int m_majorSteps;	//��̶ȵĲ���
	double m_minorSteps; //С�̶ȵĲ��� (=m_majorSteps/m_minorNum) 
	int m_minorNum;		 //С�̶���
	int m_majorLength;	 //��̶ȳ���
	int m_minorLength;	 //С�̶ȳ��� 
	int m_majorWidth;	 //��̶ȿ��
	int m_minorWidth;	 //С�̶ȿ��
	QColor m_liquidColor; //�¶ȼ�Һ����ɫ

	void paintEvent(QPaintEvent *);
	void setAxis(QPainter *);
	virtual void drawContexts(QPainter *painter,QRect r,const QString str,
		int pixsize = 10, int flags = Qt::AlignCenter,QPen pen = QPen(Qt::green));
public slots:
	virtual void setType(Type);
	virtual void setState(State) ;
	virtual void setName(QString);
	virtual void setTitle(QString) ;
	virtual void setChannel(QString);
	virtual void setValue(double);
	virtual void setScale(double) ;
	virtual void setCenter(QPoint) ;
	virtual void setCenter(double,double);
	virtual void setMeterVisible(bool);
	void setWidth(int);
	void setHeight(int);
	void setMinValue(int);
	void setMaxValue(int);
	void setScaleSteps(Scale,double);
	void setScaleLength(Scale,int);
	void setScaleWidth(Scale,int);
	void setLiuidColor(QColor);
};


#endif // THERMOMETER_H

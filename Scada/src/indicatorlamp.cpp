
/********************************************************************
**	File Name:indicatorlamp.cpp
**  Description:
**  Create the indicator widget
**  Author:		teddy.tu(tudongdong1989@gmail.com)
**	
**	Remark:		teddy.tu
**  Date:     2015/4/17
**	Version:	1.0.0
**  Copyright(C) teddy.tu
**  All rights reserved.
********************************************************************/ 

#include "indicatorlamp.h"
#include <qpainter.h>
#include "InfoMsg.h"
#include <QPixmap>
#include <QImage>
#include <QDir>
#include <QMessageBox>
#include "parameter.h"

IndicatorLamp::IndicatorLamp(QString name,QString title, QMeter::Type type, QWidget *parent)
	: QMeter(name,title,type,parent),m_radius(100)
{
	/*set the background color*/
	QPalette p = palette();
	p.setBrush(QPalette::Background,Qt::black);
	setPalette(p);
	setAutoFillBackground(true);

	m_radius = 30;						    //�뾶
	//m_title = QStringLiteral("ָʾ��");	//����
	m_lampColor = Qt::darkGray;			   //ָʾ����ɫ
	//setMinimumSize(220,220);			   //�����С����
	setMaximumHeight(120);
	//sizeHint();
    m_value = 1;
    m_visible = true;
    lower_warning = 1;                  //��ֵ���ã�Ĭ��Ϊ�����ź����룬0--������ 1--������
    lower_alarm = 1;
    high_warning = 1;
    high_alarm = 1;

    isDigit = true;                     //true -- ����������  false -- ģ��������
    isDrawLamp = false;                // true -- ����ָʾ��   false -- �����źŵ�ͼƬ
    setPixmapPath(":/brake");
	m_timer = new QTimer(this);
    //setCursor(Qt::BlankCursor);   //�������
    //resize(100,100);
	setState(QMeter::NoData);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(twinkle()));    //���ñ�����˸
}

IndicatorLamp::IndicatorLamp(const IndicatorLamp &lamp)
	:QMeter(lamp.m_name,lamp.m_title,lamp.m_type,lamp.parentWidget())
{
	m_radius = lamp.m_radius;
	m_lampColor = lamp.m_lampColor;
	m_timer = lamp.m_timer;
}

IndicatorLamp::~IndicatorLamp()
{
   if(m_timer)
       delete m_timer;
}

void IndicatorLamp::paintEvent(QPaintEvent *)
{
    InfoMsg info;
    QPainter painter(this);
    //m_state = QMeter::Warning;
    //����������
    setAxis(&painter);

    if(!isDrawLamp)                                             //�����Ǳ�ͼƬ
    {
        if(!showPixMap)
        {
            if(m_state == QMeter::Normal)
                setPixmapPath(GREEN_LAMP);
            else if(m_state == QMeter::Warning)
                setPixmapPath(YELLOW_LAMP);
            else if(m_state == QMeter::Alarm)
                setPixmapPath(RED_LAMP);
        }
        //info.info_log("filepath:%s \n", pixmapPath.toStdString().c_str());
        QRect rect(-m_radius, -m_radius, m_radius << 1, m_radius << 1);
        painter.setBrush(Qt::red);
        drawPixmap(&painter, rect);
    }
    else                                                        //�����Ǳ�
    {
	    int w = width();
	    painter.setRenderHint(QPainter::Antialiasing);
	    //���û���
	    painter.setPen(Qt::NoPen);
	    //������߿�
	    drawOutFrame(&painter,m_radius,QColor(Qt::white));
	    //�����ڿ�
	    drawInnerFrame(&painter,m_radius*0.85,QColor(Qt::white));
	    //����ָʾ����ɫ
	    drawInnerColor(&painter,m_radius*0.8,m_lampColor);
	    //�����Ǳ�����
	    drawContexts(&painter,QRect(-w,m_radius+5,w*2,40),m_title,24,Qt::AlignCenter,QPen(m_lampColor));
	}

    if(!m_visible)
    {
        painter.setBrush(Qt::black);
        //painter.setPen(Qt::red);
        painter.drawRect(-m_radius,-m_radius,m_radius<<1,m_radius<<1);
    }
}
//��������ϵͳ
void IndicatorLamp::setAxis(QPainter *painter)
{
	int w = width();
	int h = height();
	int side = qMin(w,h);
	painter->translate(w/2,h/2);
	painter->scale(side/220.0,side/220.0); 

	/*painter->setPen(Qt::gray);
	painter->drawRect(-110,-110,220,220);*/
	painter->translate(m_center.x(),m_center.y()-10);
	
	/*painter->setPen(Qt::red);
	painter->drawRect(-m_radius,-m_radius,m_radius<<1,m_radius<<1);
	painter->setPen(Qt::green);
	painter->drawLine(-m_radius-5,0,m_radius+5,0);
	painter->drawLine(0,-m_radius-5,0,m_radius+5);*/
	
}
//������߿�
void IndicatorLamp::drawOutFrame(QPainter *painter,int radius,QColor color)
{
	painter->save();
    int red = color. red();
	int green = color.green();
	int blue = color.blue();
	QLinearGradient lg(0, -m_radius, 0, m_radius);
    lg.setColorAt(0, color);
    lg.setColorAt(1, QColor(red*0.65, green*0.65, blue*0.65));
    painter->setBrush(lg);
    painter->drawEllipse(-radius, -radius, radius << 1, radius << 1);

	painter->restore();
}
//�����ڱ߿�
void IndicatorLamp::drawInnerFrame(QPainter *painter,int radius,QColor color)
{
	painter->save();
	int red = color. red();
	int green = color.green();
	int blue = color.blue();
    QLinearGradient lg2(0, -radius, 0, radius);
    lg2.setColorAt(0, QColor(red*0.65, green*0.65, blue*0.65));
    lg2.setColorAt(1, color);
    painter->setBrush(lg2);
    painter->drawEllipse(-radius, -radius, radius << 1, radius << 1);
	painter->restore();
}
//����ָʾ���ڲ���ɫ
void IndicatorLamp::drawInnerColor(QPainter *painter,int radius, QColor color)
{
	painter->save();
	int red = color. red();
	int green = color.green();
	int blue = color.blue();
	QRadialGradient rg(0,0,radius);
	rg.setColorAt(0,QColor(red,green,blue));
	rg.setColorAt(0.8,QColor(red*0.8,green*0.8,blue*0.8));
	rg.setColorAt(1,QColor(red*0.65,green*0.65,blue*0.65));
	painter->setBrush(rg);
	painter->drawEllipse(-radius,-radius,radius<<1,radius<<1);
	painter->restore();
}
//�����ı�
void IndicatorLamp::drawContexts(QPainter *painter,QRect r, const QString str, int pixsize, int flags,QPen pen )
{
	painter->save();
	QFont font;
	font.setPixelSize(pixsize);
	font.setBold(true);
	painter->setFont(font);
	painter->setPen(pen);
	painter->drawText(r,flags, str);
	painter->restore();
}
//����ͼƬ
void IndicatorLamp::drawPixmap(QPainter *painter, QRect rect)
{
    painter->save();
    painter->drawPixmap(rect, pixmap);
    painter->restore();
}

void IndicatorLamp::drawPixmap(QPainter *painter, QRect r, QPixmap p)
{
    painter->save();
    painter->drawPixmap(r, p);
    painter->restore();
                                             
}

//plubic slots
void IndicatorLamp::setType(QMeter::Type type)
{
	m_type = type;
	update();
}

void IndicatorLamp::setState(QMeter::State state)
{
	m_state = state;
	stateChanged();
}

void IndicatorLamp::setName(QString name)
{
	m_name = name;
	update();
}

void IndicatorLamp::setTitle(QString title)
{
	m_title = title;
	update();
}

void IndicatorLamp::setChannel(QString channel)
{
	m_channel = channel;
	update();
}

void IndicatorLamp::setScale(double scale)
{
	m_scale = scale;
	m_radius *= m_scale;
	update();
}

void IndicatorLamp::setCenter(QPoint point)
{
	setCenter((double)point.x(),(double)point.y());
}

void IndicatorLamp::setCenter(double x, double y)
{
	m_center = QPoint(x,y);
	update();
}
void IndicatorLamp::setMeterVisible(bool visible)
{
	m_visible = visible;
	update();
}

void IndicatorLamp::setLampColor(QColor color)
{
	m_lampColor = color;
	update();
}

void IndicatorLamp::setRadius(int r)
{
	m_radius = r;
	update();
}

void IndicatorLamp::setIsDigit(bool digit)
{
   isDigit = digit;
   update();
}

void IndicatorLamp::setValue(double val)
{
     m_value  = val;
     if(val <= lower_warning || val >= high_warning)
         m_state = QMeter::Warning;
     else if(val <= lower_alarm || val >= high_warning)
         m_state = QMeter::Alarm;
     else
         m_state = QMeter::Normal;

     if(isDigit && m_state == QMeter::Warning) 
         m_state = QMeter::Alarm;
         
     stateChanged();
     update();
}

void IndicatorLamp::stateChanged()
{
    InfoMsg info;
	QColor color;
	switch(m_state)
	{
	case QMeter::NoData:
		color = QColor(Qt::gray);
		break;
	case QMeter::Normal:
		color = QColor(Qt::green);
        if(!RUNNING)
            m_visible = false;

        if(m_timer->isActive())
            m_timer->stop();
        break;
	case QMeter::Warning:
		color = QColor(Qt::yellow);
        m_timer->start(500);
        break;
	case QMeter::Alarm:
		color = QColor(Qt::red);
        m_timer->start(300);
		break;
	}
    
	setLampColor(color);
	update();
}
void IndicatorLamp::setLowerWarning(double value)
{
    lower_warning = value;
    update();
}

void IndicatorLamp::setHighWarning(double value)
{
    high_warning = value;
    update();
}

void IndicatorLamp::setLowerAlarm(double value)
{
    lower_alarm = value;
    update();
}

void IndicatorLamp::setHighAlarm(double value)
{
    high_warning = value;
    update();
}

void IndicatorLamp::setPixmapPath(QString path)
{
    pixmapPath = path;
    showPixMap = pixmap.load(path);
    update();
}

void IndicatorLamp::setLimitValue(LIMIT limit, double value)
{
    switch(limit)
    {
    case 1:
        setLowerWarning(value);
        break;
    case 2:
        setHighWarning(value);
        break;
    case 3:
        setLowerAlarm(value);
        break;
    case 4:
        setHighAlarm(value);
        break;
    }
}

void IndicatorLamp::setDrawPixMap(bool flag)
{
     isDrawLamp = flag;
     update();
}

void IndicatorLamp::twinkle()
{
	m_visible = !m_visible;
    update();
}

double IndicatorLamp::getLimitValue(LIMIT limit) const
{
   switch(limit)
   {
   case LOWERWARNING:
       return lower_warning;
       break;
   case HIGHWARNING:
       return high_warning;
       break;
   case LOWERALARM:
       return lower_alarm;
       break;
   case HIGHALARM:
       return high_alarm;
       break;
   }
   return 0;
}
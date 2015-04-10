
/*
**  @description:
**  �������ʵ���ļ�����������������
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
#include "qmeter.h"
QMeter::QMeter(QString name,QString title, Type type,QWidget *parent)
	: m_name(name),m_title(title),m_type(type),QWidget(parent)
{
	m_state = NoData;
	//m_title = QStringLiteral("�Ǳ�");
	m_channel = "NULL";
	m_value = 0;
	m_scale = 1.0;
	m_center = QPoint(0,0);
	m_visible = true;
}

QMeter::~QMeter()
{

}

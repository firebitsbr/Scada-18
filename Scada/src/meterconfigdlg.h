#ifndef MeterConfigDlg_H
#define MeterConfigDlg_H

#include <QWidget>
#include "qbasemeter.h"
#include "ui_meterconfigdlg.h"

class MeterConfigDlg : public QWidget
{
	Q_OBJECT

public:
	MeterConfigDlg(QBaseMeter *meter = NULL, QWidget *parent = 0);
	~MeterConfigDlg();
	void initConfig(QBaseMeter *);
	void setMeter(QBaseMeter *meter);
private:
	Ui::MeterConfigDlg ui;
	QBaseMeter *m_meter;
	bool m_flags;      //�״������Ǳ����������־λ��true--�״���������Ǳ��л���false -- ���õ�ǰ�Ǳ�����
	void connectUI();
public slots:           
	void on_titleLineEditChanged();
	void on_titleVisiabled(bool);
	void on_unitsLineEditChanged();
	void on_unitsVisiabled(bool); 

	void on_minValueChanged(int);
	void on_maxValueChanged(int);
	void on_rateChecked(bool);
	void on_rateValueChanged(const QString);

	/*void on_pageChanged(int);
	void on_posChanged(int);*/
	void on_startAngleChanged(int);
	void on_endAngleChanged(int);
	void on_radiusChanged(int);
	void on_centerXChanged(int);
	void on_centerYChanged(int);

	void on_majorNumChanged(int);
	void on_majorLengthChanged(int);
	void on_majorWidthChanged(int);
	void on_middleNumChanged(int);
	void on_middleLengthChanged(int);
	void on_middleWidthChanged(int);
	void on_minorNumChanged(double);
	void on_minorLengthChanged(int);
	void on_minorWidthChanged(int);
	void on_middleVisiable(bool);

	void selectedMeter();
	void selectedMeter(QMeter *);
};

#endif // MeterConfigDlg_H

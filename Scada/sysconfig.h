#ifndef SYSCONFIG_H
#define SYSCONFIG_H

#include <QWidget>
#include "ui_sysconfig.h"
#include "connectdb.h"
#include <qmap.h>
#include <QComboBox.h>
#include <QTableWidgetItem>
#include "channel.h"
#include <qset.h>
#include <QStatusBar>

class SysConfig : public QWidget
{
	Q_OBJECT

public:
	SysConfig(QWidget *parent = 0);
	~SysConfig();
	void clearAllData(QString tableName,QString database="scada");
    QMap<int, QString> getChannelMap(); 

private:
	Ui::SysConfig SysConfigUI;

	unsigned int mask;							//Ԥ���ͱ�����־λ
	QMap<int,QString> m_channelIdMap;			//id��������ͨ��hash��
	
    QSet<QString> m_setChannelList;				//δ����ͨ���б�
	ConnectDB	*con;							//���ݿ�����
	int MaxRow;									//tablewidget�����������ȡ��ͨ������
	int MaxColumn;								//�ֶ���
	int comboRow;								//�Ƿ����m_channelComboBox����ǰλ��
	static const int comboColumn = 1;			//����m_channelComboBox������
	int SelectionRow;							//������ѡ���ͨ��������
	QComboBox *m_channelComboBox;				//��tableWidget������ͨ��
	//bool b_channelSelected;

	void createUI();
	void connectUI();
	void initTableWidget();
	bool insertData(int row, int column, QString str);
	bool insertData(int row, int column, int index);
	void setGroupBoxState(int mask);
	bool createConfigureDB();
	bool createHistoryDB();
	void WriteData();
	void ReadData();
	void setData(int row);
    

protected:
	//void resizeEvent(QResizeEvent *);

signals:
	void updateData();
	void setChannel(QString channelName,bool b_flag);
    void errorMsg(const QString msg);

private slots:
	void on_setChannel(QString channelName);
	void on_dataNameChanged(QString);
	void on_DataUintChanged(QString);
	void on_MeterTypeChanged(int);

    void on_SensorType(QString);
    void on_InputDataType(int);
    void on_SensorMax(QString);
    void on_SensorMin(QString);
    void on_InhibitTime(QString);
    void on_InhibitTimeUint(int);
	//void on_tableItemSelect(int);
	void on_WarningChecked(bool);
	void on_LowerWarningChecked(bool);
	void on_HighWarningChecked(bool);
	void on_AlarmChecked(bool);
	void on_LowerAlarmChecked(bool);
	void on_HighAlarmChecked(bool);
	void on_LowerWarningChanged(const QString);
	void on_HighWarningChanged(const QString);
	void on_LowerAlarmChanged(const QString);
	void on_HighAlarmChanged(const QString);

	void on_OkPushButtonClicked();
	void on_CancelPushButtonClicked();
	void on_AppliedPushButtonClicked();

	void on_tableWidgetCellDoubleClicked(int row, int column);
	void on_cellClicked(int row, int column);
	void on_channelcomboBoxActivated(QString);
};

#endif // SYSCONFIG_H

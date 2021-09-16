#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include <qtcpsocket.h>
#include <qtcpserver.h>


class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = Q_NULLPTR);

public slots:
	void onConnectButtonClicked();
	void onSendMessageButtonClicked();
	void onSocketReadyRead();

	void onServerNewConnection();
	void onClientDisconnected();
	void onClientReadyRead();

private:
    Ui::QtWidgetsApplication1Class ui;
	QTcpSocket * socket;
	QTcpServer * server;
};

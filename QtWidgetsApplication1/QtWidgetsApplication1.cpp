#include "QtWidgetsApplication1.h"

QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	socket = new QTcpSocket(this);
	QObject::connect(socket, SIGNAL(clicked()), this, SLOT(onConnectButtonClicked()));
	QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));

	server = new QTcpServer(this);
	QObject::connect(server, SIGNAL(newConnection()), this, SLOT(onServerNewConnection()));
	server->listen(QHostAddress::AnyIPv4, 4321);

}

void QtWidgetsApplication1::onConnectButtonClicked() {
	QString ip = ui.IPLineEdit->text();
	QString port = ui.portLineEdit->text();

	bool ok;
	int portAsInt = port.toInt(&ok);
	if (ok) {
		socket->connectToHost(ip, portAsInt);
	}
}

void QtWidgetsApplication1::onSendMessageButtonClicked() {
	if (socket->state() == QTcpSocket::ConnectedState) {
		socket->write("Coucou !\n");
	}
}

void QtWidgetsApplication1::onSocketReadyRead() {
	QByteArray data = socket->read(socket->bytesAvailable());
	QString str(data);
	ui.connectionStatusLabel->setText("Status connexion: Message recu = " + str);
}

void QtWidgetsApplication1::onServerNewConnection(){
	ui.connectionStatusLabel->setText("Un client s'est connecte");
	QTcpSocket * client = server->nextPendingConnection();
	QObject::connect(client, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));
	QObject::connect(client, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));

}

void QtWidgetsApplication1::onClientReadyRead() {
	QTcpSocket * obj = qobject_cast<QTcpSocket*>(sender());
	QByteArray data = socket->read(socket->bytesAvailable());
	QString str(data);
	ui.messageLabel->setText(data);
	obj->write(data);
}

void QtWidgetsApplication1::onClientDisconnected() {
	QTcpSocket * obj = qobject_cast<QTcpSocket*>(sender());
	QObject::disconnect(obj, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));
	QObject::disconnect(obj, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
	obj->deleteLater();
}
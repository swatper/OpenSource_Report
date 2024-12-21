#include "Client.h"
#include "ui_Client.h"

Client::Client(QWidget *parent) : QMainWindow(parent), ui(new Ui::Client){
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    fd_flag = connectToHost("127.0.0.1"); // localhost
    if (!fd_flag)
        ui->textEdit->insertPlainText("Socket connect fail\n");
}
Client::~Client(){
    delete ui;
}
bool Client::connectToHost(QString host){
    socket->connectToHost(host, 8888); // ip, port
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    return socket->waitForConnected();
}
bool Client::writeData(QByteArray data){
    if (socket->state() == QAbstractSocket::ConnectedState){
        socket->write(data); // write the data itself
        return socket->waitForBytesWritten();
    }
    else{
        return false;
    }
}
void Client::on_pushButton_clicked(){
    if (fd_flag){
        QString sendData;
        sendData = ui->lineEdit->text();
        send_flag =
            writeData(sendData.toStdString().c_str());
        if (!send_flag)
            ui->textEdit->insertPlainText("Socket send fail\n");
    }
}
void Client::readyRead(){
    QTcpSocket *socket = static_cast<QTcpSocket *>(sender());
    while (socket->bytesAvailable() > 0){
        ui->textEdit->insertPlainText(QString(socket -> readAll()) + "\r\n");
    }
}
int main(int argc, char **argv){
    QApplication app(argc, argv);
    Client *window = new Client();
    window->show();
    return app.exec();
}
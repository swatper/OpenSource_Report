#include "Server.h"
#include "ui_Server.h"

Server::Server(QWidget *parent): QMainWindow(parent),ui(new Ui::Server){
    ui->setupUi(this);
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this,
            SLOT(newConnection()));
    QString socket_data;
    socket_data.sprintf("Listening: %s\n", server->listen(QHostAddress::Any, 8888) ? "true" : "false");
    ui->textEdit->insertPlainText(socket_data);
}
Server::~Server(){
    delete ui;
}
void Server::newConnection(){
    while (server->hasPendingConnections()){
        QTcpSocket *socket = server->nextPendingConnection();
        clients.push_back(socket);
        socket->setObjectName(QString::number(cnt));
        ui->textEdit->insertPlainText("Connected from " + QString::number(cnt++) + "\r\n");
        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
        QByteArray *buffer = new QByteArray();
        buffers.insert(socket, buffer);
    }
}
void Server::disconnected(){
    QTcpSocket *socket = static_cast<QTcpSocket *>(sender());
    QByteArray *buffer = buffers.value(socket);
    // 클라이언트 삭제
    ui->textEdit->insertPlainText("Client " + socket->objectName() + " disconnected.\n");
    // 목록에서 클라이언트 제거
    clients.erase(remove(clients.begin(), clients.end(), socket), clients.end());
    buffers.remove(socket);
    delete buffer;             // 버퍼 메모리 해제
    socket->deleteLater();     // 소켓 메모리 해제
}
void Server::readyRead(){
    QTcpSocket *socket = static_cast<QTcpSocket *>(sender());
    QByteArray *buffer = buffers.value(socket);
    while (socket->bytesAvailable() > 0){
        buffer->append(socket->readAll());
        ui->textEdit->insertPlainText(socket -> objectName() + ": " + 
                                      QString(buffer->data()) + "\r\n");
        QString message = QString("%1: %2").arg(socket->objectName()).arg(QString(buffer->data()));
        for(QTcpSocket* client : clients){
            client->write(message.toUtf8()); 
        }
        send_flag = socket->waitForBytesWritten();
        if (!send_flag)
            ui->textEdit->insertPlainText("Socket send fail\n");
        qint32 size = buffer->size();
        QByteArray data = buffer->mid(0, size);
        buffer->remove(0, size);
        emit dataReceived(data);
    }
}

int main(int argc, char **argv){
    QApplication app(argc, argv);
    Server *window = new Server();
    window->show();
    return app.exec();
}
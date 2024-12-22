#include "Client.h"
#include "ui_Client.h"

Client::Client(QWidget *parent) : QMainWindow(parent), ui(new Ui::Client){
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    fd_flag = connectToHost("127.0.0.1"); // localhost
    if (!fd_flag){
        ui->textEdit->insertPlainText("Socket connect fail\n");
        ui->label2->setText("Disconnected");
        ui->pushButton3->setEnabled(true);
    }
    else{
        ui->label2->setText("Connected");
        ui->pushButton3->setEnabled(false);
    }
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
        QString sendData = ui->lineEdit->text();
        QString fileName = ui->label->text();
        if(fileName != "File is Empty"){
            QFile file(fileName);
            //파일 열기 
            if (file.open(QIODevice::ReadOnly)) {
                QByteArray fData = file.readAll();
                QString fPath = fileName;
                QFileInfo fileInfo(fPath);
                QString fName = fileInfo.fileName();
                file.close();
                QByteArray result = "\n" +fName.toUtf8() + "\n" + fData;
                send_flag = writeData(result);
                if (!send_flag) {
                    ui->textEdit->insertPlainText("File send fail\n");
                }
            } 
        }
        if(!sendData.isEmpty()){
            send_flag = writeData(sendData.toStdString().c_str());
            ui->lineEdit->setText("");
            if(!send_flag){
                ui->textEdit->insertPlainText("Message send fail\n");
            }
        }
        ui->lineEdit->setEnabled(true);
        ui->label->setText("File is Empty");
        if (sendData.isEmpty() && fileName == "File is Empty")
            ui->textEdit->insertPlainText("Socket send fail\n");
    }
}

void Client::on_pushButton2_clicked(){
    QString fileName = QFileDialog::getOpenFileName(this, "파일 선택", "", "모든 파일 (*);;텍스트 파일 (*.txt)");
    if (!fileName.isEmpty()) {
        ui->label->setText(fileName);
        ui->lineEdit->setText("");
        ui->lineEdit->setEnabled(false);
    }else{
        ui->label->setText("File is Empty");
        ui->lineEdit->setEnabled(true);
    }
}

void Client::on_pushButton3_clicked(){
    fd_flag = connectToHost("127.0.0.1"); // localhost
    if (!fd_flag){
        ui->textEdit->insertPlainText("Socket connect fail\n");
        ui->label2->setText("Disconnected");
        ui->pushButton3->setEnabled(true);
    }
    else{
        ui->label2->setText("Connected");
        ui->pushButton3->setEnabled(false);
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
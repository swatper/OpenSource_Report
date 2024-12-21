/********************************************************************************
** Form generated from reading UI file 'Client.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->setEnabled(true);
        Client->resize(391, 324);
        centralwidget = new QWidget(Client);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(320, 220, 61, 23));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 0, 371, 211));
        textEdit->setMouseTracking(false);
        textEdit->setReadOnly(true);
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 220, 301, 23));
        lineEdit->setMouseTracking(false);
        lineEdit->setReadOnly(false);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 250, 301, 16));
        pushButton2 = new QPushButton(centralwidget);
        pushButton2->setObjectName(QString::fromUtf8("pushButton2"));
        pushButton2->setGeometry(QRect(320, 250, 61, 20));
        Client->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Client);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 391, 20));
        Client->setMenuBar(menubar);
        statusbar = new QStatusBar(Client);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Client->setStatusBar(statusbar);

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QMainWindow *Client)
    {
        Client->setWindowTitle(QCoreApplication::translate("Client", "Client", nullptr));
        pushButton->setText(QCoreApplication::translate("Client", "Send", nullptr));
        label->setText(QCoreApplication::translate("Client", "File is Empty", nullptr));
        pushButton2->setText(QCoreApplication::translate("Client", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H

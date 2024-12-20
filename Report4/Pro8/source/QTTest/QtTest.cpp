#include "QtTest.h"
#include <qpushbutton.h>
#include <qapplication.h>
#include <iostream>
using namespace std;
//생성자
ButtonWindow::ButtonWindow(QWidget *parent, Qt::WindowFlags flags) 
                : QMainWindow(parent, flags){
    this->setWindowTitle("This is the window Title");
    QPushButton *button = new QPushButton("Click Me!", this);
    button->setGeometry(50, 30, 70, 20);
    connect(button, SIGNAL(clicked()), this, SLOT(Clicked()));
}
//소멸자
ButtonWindow::~ButtonWindow(){}

void ButtonWindow::Clicked(void){
    cout << "clicked!\n";
}

int main(int argc, char **argv){
    QApplication app(argc,argv);
    ButtonWindow *window = new ButtonWindow();
    window->show();
    return app.exec();
}
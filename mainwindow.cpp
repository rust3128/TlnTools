#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QStringList user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentUser=user;
    infoUser2StatusBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::infoUser2StatusBar()
{
    labelUser = new QLabel(this);
    labelUser->setText("Пользователь: " + currentUser.at(1));
    ui->statusBar->addPermanentWidget(labelUser);
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usersdialog.h"

#include <QMessageBox>


MainWindow::MainWindow(QSqlRecord user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentUser.id=user.value("user_id").toInt();
    currentUser.fio=user.value("fio").toString();
    createUI();
    infoUser2StatusBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::infoUser2StatusBar()
{
    labelUser = new QLabel(this);
    labelUser->setText("Пользователь: " + currentUser.fio);
    ui->statusBar->addPermanentWidget(labelUser);

}

void MainWindow::createUI()
{

    if(currentUser.id!=1) {
        ui->actionUsers->setDisabled(true);
        ui->actionUsers->setStatusTip(ui->actionUsers->statusTip()+" Доступно только администратору.");
    }
}


void MainWindow::on_actionUsers_triggered()
{
    UsersDialog *usersDlg = new UsersDialog();
    usersDlg->exec();
}

#include "logindialog.h"
#include "ui_logindialog.h"
#include "LoggingCategories.h"



LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    createUI();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::createUI()
{
    dblite = QSqlDatabase::database("lite");
    users = new QSqlQueryModel();
    users->setQuery("select user_id, username, password from users", dblite);
    ui->comboBoxLogin->setModel(users);
    ui->comboBoxLogin->setModelColumn(1);
    ui->comboBoxLogin->setCurrentIndex(-1);
    currUserID=-1;
    ui->labelInfo->setText("");
}

void LoginDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch (ui->buttonBox->standardButton(button)) {
    case QDialogButtonBox::Ok:
        verifyLogin();
        break;
    case QDialogButtonBox::Cancel:
        this->reject();
        break;
    default:
        break;
    }
}

void LoginDialog::verifyLogin()
{
    if(userPass==ui->lineEditPassword->text().trimmed()) {
        qInfo(logInfo()) << QString("Пользователь: %1. Успешный вход в систему.").arg(ui->comboBoxLogin->currentText());
        this->accept();
    } else {
        ui->labelInfo->setText("Не верный пароль!");
        qWarning(logInfo()) << QString("Пользователь: %1. Не верный пароль!.").arg(ui->comboBoxLogin->currentText());
        ui->lineEditPassword->clear();
        return;
    }
}

void LoginDialog::on_comboBoxLogin_activated(int idx)
{
    userPass="";

    currUserID=users->data(users->index(idx,0)).toInt();
    userPass=users->data(users->index(idx,2)).toString();
}

void LoginDialog::on_lineEditPassword_textEdited()
{
    ui->labelInfo->clear();
}

QStringList LoginDialog::getUser()
{
    QStringList user;
    user << QString::number(currUserID) << ui->comboBoxLogin->currentText();
    return user;
}

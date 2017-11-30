#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSqlRecord>
#include <QSqlQueryModel>

struct userdata
{
    int id;
    QString fio;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QSqlRecord user, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionUsers_triggered();

    void on_actionInputNum_triggered();

private:
    Ui::MainWindow *ui;
    userdata currentUser;
    QLabel *labelUser;
    QLabel *labelDB;
    QStringList listTalons;
    void crModelSerials();
    QSqlQueryModel *modelSerials;
private:
    void infoUser2StatusBar();
    void createUI();

};

#endif // MAINWINDOW_H

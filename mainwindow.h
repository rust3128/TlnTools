#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSqlRecord>

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

private:
    Ui::MainWindow *ui;
    userdata currentUser;
    QLabel *labelUser;

    void infoUser2StatusBar();
    void createUI();

};

#endif // MAINWINDOW_H

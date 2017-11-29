#ifndef DATABASES_H
#define DATABASES_H

#define DATABASE_NAME       "C:/Develop/TlnTools/TlnTools.db"

#include <QtSql>
#include <QMessageBox>

static bool connectionOptions()
{
    // База данных приложения
    if(!QFile(DATABASE_NAME).exists()){
            qCritical(logCritical) << "Отсутсвует файл настроек приложения.";
            return false;
    }

    QSqlDatabase dblite = QSqlDatabase::addDatabase("QSQLITE","lite");
    dblite.setHostName("TlnHost");
    dblite.setDatabaseName(DATABASE_NAME);
    if(dblite.open()){
          qInfo(logInfo()) << "База данных приложения успешно открыта." << dblite.databaseName();

    } else {
        qCritical(logCritical()) << QString("Не удалось открыть базу данных приложения. Причина: %1")
                                    .arg(dblite.lastError().text());
        return false;
    }

    return true;
}

static bool connectToDatabases()
{
    QString connName = "Саноил";
    QSqlDatabase dblite = QSqlDatabase::database("lite");

    QSqlQuery q = QSqlQuery(dblite);

    q.prepare("SELECT * FROM connections WHERE conname = :connName");
    q.bindValue(":connName", connName);
    if(!q.exec()) {
        qCritical(logCritical()) << QString("Не удалось получить список подключений. Причина: %1")
                                    .arg(dblite.lastError().text());
        return false;
    }
    while (q.next()) {
        if(q.value(2).toString()=="QODBC3"){
            QSqlDatabase dbto = QSqlDatabase::addDatabase("QODBC3","talonsonline");
            QString dbName = QString("Driver={SQL SERVER};SERVER=%1;DATABASE=%2;Trusted_Connection=no;")
                    .arg(q.value(3).toString())
                    .arg(q.value(4).toString());
            dbto.setDatabaseName(dbName);
            dbto.setUserName(q.value(5).toString().trimmed());
            dbto.setPassword(q.value(6).toString().trimmed());
            if(!dbto.open()) {
                    qDebug() <<  "Не возможно подключиться к базе данных." << endl << "Причина:" << dbto.lastError().text();
                    QMessageBox::critical(0, qApp->tr("Не могу открыть базу данных"),
                                          QString("Не могу установить соединение с базой данных TalonsOnline\nПричина: %1").arg(dbto.lastError().text()),
                                          QMessageBox::Ok);
                    return false;
            }
        }
        if(q.value(2).toString()=="QIBASE") {
            QSqlDatabase dbfb = QSqlDatabase::addDatabase("QIBASE","central");
            dbfb.setHostName(q.value(3).toString());
            dbfb.setDatabaseName(q.value(4).toString());
            dbfb.setUserName(q.value(5).toString());
            dbfb.setPassword(q.value(6).toString());

            if(!dbfb.open()) {
                        qDebug() <<  "Не возможно подключиться к базе данных." << endl << "Причина:" << dbfb.lastError().text();
                        QMessageBox::critical(0, qApp->tr("Не могу открыть базу данных"),
                                              QString("Не могу установить соединение c центральной базой данных MPos\nПричина: %1\n Проверьте настройки подключения.").arg(dbfb.lastError().text()),
                                              QMessageBox::Ok);
                        return false;
                    }
        }

    }


    return true;
}

#endif // DATABASES_H

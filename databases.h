#ifndef DATABASES_H
#define DATABASES_H

#define DATABASE_NAME       "E:/Develop/TlnTools/TlnTools.db"

#include <QtSql>
#include <QMessageBox>

static bool createConnection()
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
        qCritical(logCritical()) << QString("Не удалось открыть базуданных приложения. Причина: %1")
                                    .arg(dblite.lastError().text());
        return false;
    }

    return true;
}

#endif // DATABASES_H

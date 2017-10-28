#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QScopedPointer>
#include <QTextStream>
#include <QDateTime>
#include <QLoggingCategory>
#include <QTextCodec>


#include "LoggingCategories.h"
#include "databases.h"
#include "logindialog.h"

// Умный указатель на файл логирования
QScopedPointer<QFile>   m_logFile;

// Объявляение обработчика
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Устанавливаем файл логирования,
    // внимательно сверьтесь с тем, какой используете путь для файла
    m_logFile.reset(new QFile("TlnTools.log"));
    // Открываем файл логирования
    m_logFile.data()->open(QFile::Append | QFile::Text);
    // Устанавливаем обработчик
    qInstallMessageHandler(messageHandler);

    // Устанавливаем файл локализации
    QTranslator *qt_translator = new QTranslator();
    if(qt_translator->load(":/translate/qtbase_ru.qm")) {
        a.installTranslator(qt_translator);
    }
    else {
        qWarning(logWarning()) << "Не удалось загрузить языковый файл.";
    }

    if(!createConnection()) {
        return 1;
    }

    LoginDialog *loginDlg = new LoginDialog();
    loginDlg->exec();
    if(loginDlg->result()==QDialog::Rejected)
        return 1;

    MainWindow *w = new MainWindow(loginDlg->getUser());
    qInfo(logInfo()) << "Запуск программы.";
    w->show();

    return a.exec();
}

// Реализация обработчика
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Открываем поток записи в файл
    QTextStream out(m_logFile.data());
    QTextStream console(stdout);


    // Записываем дату записи
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    // По типу определяем, к какому уровню относится сообщение
    switch (type)
    {
#ifdef QT_DEBUG
    case QtInfoMsg:     out << "INF "; console << "Info: " << msg << endl; break;
    case QtDebugMsg:    out << "DBG "; console << "Debug: " << msg << endl; break;
    case QtWarningMsg:  out << "WRN "; console << "Warning: " << msg << endl; break;
    case QtCriticalMsg: out << "CRT "; console << "Critical: " << msg << endl; break;
    case QtFatalMsg:    out << "FTL "; console << "Fatality: " << msg << endl; break;
#else
    case QtInfoMsg:     out << "INF "; break;
    case QtDebugMsg:    out << "DBG "; break;
    case QtWarningMsg:  out << "WRN "; break;
    case QtCriticalMsg: out << "CRT "; break;
    case QtFatalMsg:    out << "FTL "; break;
#endif

    }
    // Записываем в вывод категорию сообщения и само сообщение
    out << context.category << ": "
        << msg << endl;
    out.flush();    // Очищаем буферизированные данные
    console.flush();
}

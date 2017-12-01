#ifndef TALONSMODEL_H
#define TALONSMODEL_H

#include <QObject>

class TalonsModel : public QObject
{
    Q_OBJECT
public:
    explicit TalonsModel(QStringList tlnList, QObject *parent = nullptr);

signals:

public slots:
};

#endif // TALONSMODEL_H

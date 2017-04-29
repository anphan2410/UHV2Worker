#ifndef UHV2WORKER_H
#define UHV2WORKER_H

#include <QObject>

class UHV2Worker : public QObject
{
    Q_OBJECT
public:
    explicit UHV2Worker(QObject *parent = 0);

signals:

public slots:
};

#endif // UHV2WORKER_H
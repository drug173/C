#ifndef DATABASE_H
#define DATABASE_H
#include <QObject>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>



class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();
  void connectToDataBase();
  QSqlDatabase connectName();

private:

    QSqlDatabase    db;
    bool openDataBase();//открыть базу

    bool restoreDataBase();
    void closeDataBase();

};

#endif // DATABASE_H



#include "database.h"
#include <QMessageBox>


DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

QSqlDatabase DataBase::connectName()
{
    return db;
}

 void DataBase::connectToDataBase()
{

    if(!QFile("task").exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){

            return true;

    } else {

            QMessageBox::critical(nullptr, QObject::tr("Cannot open database. Program aborted."), QObject::tr("Database text: %1\nDriver text: %2").arg(db.lastError().databaseText(), db.lastError().driverText()), QMessageBox::Ok);
            return -1;

    }

}

bool DataBase::openDataBase()
{

    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("task");
    if(db.open()){
        return true;
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database. Program aborted."), QObject::tr("Database text: %1\nDriver text: %2").arg(db.lastError().databaseText(), db.lastError().driverText()), QMessageBox::Ok);
        return false;

    }
}

void DataBase::closeDataBase()
{
    db.close();
}



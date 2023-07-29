#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include "database.h"



  class QLineEdit;
  class InputDialog : public QDialog {
   Q_OBJECT
   private:
    QLineEdit* m_Name;
    QLineEdit* m_Image;
    QLineEdit* m_State;

public:
      InputDialog(QWidget* pwgt = nullptr);

    QString name() const;
    QString image () const;
    int state() const;
    ///строка, путь к файлу изображения
    QString strImg;
    QLabel* plblImg ;
signals:    ///сигнал передаёт id
     void getIdRow(int idRow);

private slots:
     ///изменение в БД
      void   editDataBase(QVector<QVariant> newValue);
      ///вставка в БД
      void   insertDataBase(QVector<QVariant> newValue);
      void   openFile();
};

#endif // INPUTDIALOG_H


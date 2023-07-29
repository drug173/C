#include "inputdialog.h"
#include <QtGui>
#include "widget.h"

InputDialog::InputDialog(QWidget* pwgt/*= 0*/)
     : QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    m_Name = new QLineEdit;
    m_Image  = new QLineEdit;
    m_State  = new QLineEdit;
     strImg="";
     this->setWindowTitle(QObject::tr("Введите данные"));

    QLabel* plblName    = new QLabel("&name");
    QLabel* plblImage     = new QLabel("&image");
    QLabel* plblState     = new QLabel("&state");
    plblImg     = new QLabel("");


    plblImg->setText(strImg);
    plblName->setBuddy(m_Name);
    plblImage->setBuddy(m_Image);
    plblState->setBuddy(m_State);


    QPushButton* pcmdCancel = new QPushButton("&Cancel");
    QPushButton* pcmdOpen     = new QPushButton("&Открыть");
    QPushButton* pcmdOk     = new QPushButton("&Ok");

    connect(pcmdOk, SIGNAL(clicked()), SLOT(accept()));
    connect(pcmdCancel, SIGNAL(clicked()), SLOT(reject()));
    connect(pcmdOpen, SIGNAL(clicked()), SLOT(openFile()));

    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->addWidget(plblName, 0, 0);
    ptopLayout->addWidget(plblImage, 2, 0);
    ptopLayout->addWidget(plblState, 1, 0);
    ptopLayout->addWidget(m_Name, 0, 1);
    ptopLayout->addWidget(m_State, 1, 1);
    ptopLayout->addWidget(plblImg, 2, 1);//....
    ptopLayout->addWidget(pcmdOpen, 2,2);
    ptopLayout->addWidget(pcmdOk, 3,0);
    ptopLayout->addWidget(pcmdCancel, 3, 1);
    setLayout(ptopLayout);

}


///слот загрузки файла изображения
  void   InputDialog::openFile()
  {

      strImg = QFileDialog::getOpenFileName(this, "Выберите файл", "", "Images (*.png)");
      plblImg->setText(strImg);
  }

///слот редактирования
void InputDialog::editDataBase(QVector<QVariant> newValue)
{

    QString strImg1 =newValue.at(1).toString();
    QFile file(strImg1); // создаем объект класса QFile
       QByteArray data; //  куда мы будем считывать данные
       QBuffer inBuffer( &data );
       if (file.open(QIODevice::ReadOnly)) // Проверяем, возможно ли открыть наш файл для чтения
       data = file.readAll(); //считываем данные  в объект data

    QSqlQuery query3;
    query3.prepare("UPDATE hierarhy SET name=?, image=?, state=? WHERE id =?;");
    QString strName =newValue.at(0).toString();
    query3.addBindValue(strName);
    query3.addBindValue(data);
    QString strState =newValue.at(2).toString();
    query3.addBindValue(strState);
    int idRow =newValue.at(3).toInt();
    query3.addBindValue(idRow);
    query3.exec();
    query3.next ();
    if (!query3.exec ()) {
           qDebug() << "хрень вышла";
       }
    if (!query3.isActive()) QMessageBox::warning(this, tr("Database Error"), query3.lastError().text());
}


///слот вставки в базу данных
void InputDialog::insertDataBase(QVector<QVariant> newValue)
{
     QString strImg1 =newValue.at(1).toString();
     QFile file(strImg1); // создаем объект класса QFile
        QByteArray dataImg; //  куда мы будем считывать данные
        QBuffer inBuffer( &dataImg );
        if (file.open(QIODevice::ReadOnly)) // Проверяем, возможно ли открыть наш файл для чтения
        //считываем данные  в объект data
      dataImg = file.readAll();
      QSqlQuery query3;
      query3.exec("INSERT INTO hierarhy (id_parent,name,image,state) VALUES (?, ?, ?, ?)");
      int strIdParent =newValue.at(3).toInt();
      query3.addBindValue(strIdParent);
      QString strName =newValue.at(0).toString();
      query3.addBindValue(strName);
      query3.addBindValue(dataImg);
      QString strState =newValue.at(2).toString();
      query3.addBindValue(strState);
      query3.exec();
       int idRowInsert=query3.lastInsertId().toInt();
       //отправляем id вставленной строки
       emit getIdRow(idRowInsert);
        query3.clear ();
}



QString InputDialog::name() const
{
    return m_Name->text();
}
///передача строки, путь к файлу
QString InputDialog::image() const
{
    return strImg;
}

int InputDialog::state() const
{
    return m_State->text().toInt();
}

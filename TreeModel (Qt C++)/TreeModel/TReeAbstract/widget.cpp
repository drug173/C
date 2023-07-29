#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    DataBase base1;
    base1.connectToDataBase();
    //QSqlTableModel *model = new QSqlTableModel; //модель таблицы
    //model->setTable("hierarhy");
    //model->select();
    //model->setEditStrategy(QSqlTableModel::OnFieldChange);
    //ui->tableView->setModel(model);
    QPixmap pixmap("../build/img2.png");
     pixmap1=pixmap;
     ui->label_2->setPixmap(pixmap1);

     TreeModel* treeModel = new TreeModel;
     ui->treeView->setModel(treeModel);



     QPalette* palette = new QPalette();
     palette->setColor(QPalette::Base,QColor(170, 190,195));
     ui->treeView->setPalette(*(palette));

     ui->treeView->setColumnHidden(2, true);
     ui->treeView->setColumnHidden(3, true);
     ui->treeView->setColumnHidden(4, true);
     auto header=ui->treeView->header();
     header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
     header->setSectionResizeMode(1, QHeaderView::ResizeToContents);
     header->setSectionResizeMode(2, QHeaderView::Fixed);
     header->setSectionResizeMode(3, QHeaderView::Fixed);
     header->setSectionResizeMode(4, QHeaderView::Fixed);
     header->setStretchLastSection(false);


     connect(ui->treeView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
             this, SLOT(slotCurrentPic(QModelIndex)));
    connect(ui->treeView->selectionModel(),SIGNAL(selectionChanged(const QItemSelection&,const QItemSelection&)),
          this, SLOT(updateActions(const QItemSelection&,const QItemSelection&)));

     connect(ui->delRow,SIGNAL(clicked()),this,SLOT(removeRow1()));
     connect(ui->modifi,SIGNAL(clicked()),this,SLOT(modifiRow()));
     connect(ui->addRow,SIGNAL(clicked()),this,SLOT(insertChild1()));
     connect(this,SIGNAL(valueChanged(QVector<QVariant>)),&iDialog,SLOT(editDataBase(QVector<QVariant>)));
     connect(this,SIGNAL(valueInsert(QVector<QVariant>)),&iDialog,SLOT(insertDataBase(QVector<QVariant>)));
     connect(&iDialog,SIGNAL(getIdRow(int)),this,SLOT(getRowId(int)));
     //делаем кнопки неактивными
     updateActions();
}

Widget::~Widget()
{
    delete ui;
}


///удаляет строку со всеми зависимыми строками
void Widget::removeRow1() {
    //Получаем модельный индекс выбранного элемента
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    //
    QAbstractItemModel *yurModel = ui->treeView->model();
    TreeModel* model= qobject_cast<TreeModel*>(yurModel);
    //получаем выбранный элемент
   TreeItem* item3= model->getItem (index);
   //номер строки
   int numRow=item3->rowNumber();
   //индекс родителя
   QModelIndex indexParent=model->parent (index);

  removeRowCascade(index,model);

  model->removeRow (numRow,indexParent);

}



///каскадное удаление элемента и всех дочерних узлов
void Widget::removeRowCascade(QModelIndex index,TreeModel *model)
{

    QList<QVariant> idList;//список id на удаление
    //получаем по индексу элемент
    TreeItem* item2= model->getItem (index);
    int idRow=item2->data(2).toInt ();  //получаем id строки

    if(!(model->hasChildren(index)))//если нет потомков, то удаляем узел
   {
         QSqlQuery query2;
                query2.prepare("DELETE FROM  hierarhy  WHERE id =?;");
                query2.addBindValue(idRow);
                query2.exec();
                query2.clear ();
        return;
    }
    //если есть потомки
    if(model->hasChildren(index))
     {    int idItem, idParenItem;//id родителя и элемента
           QMap< int,  int> mapId; /*словарь записей таблицы данных <id,id_parent> после включения элемента в модель  */

           QSqlQuery query;
           query.exec("SELECT * FROM hierarhy;");
           while (query.next())
           {//составляем список id всех элементов и родителей
               idItem = query.value(0).toInt();
               idParenItem=query.value(1).toInt();
               mapId.insert (idItem,idParenItem);// словарь родителей элементов
           }
           query.clear ();

            idList<<removeRowDB(idList, idRow,mapId);


            //удаляем всех из списка
            foreach (QVariant key , idList)
            {
                QSqlQuery query2;
                        query2.prepare("DELETE FROM  hierarhy  WHERE id =?;");
                        query2.addBindValue(key);
                        query2.exec();
                        query2.clear ();
                       // model->removeRow (numberRow,indexParent);
            }
       }
}


///функция ищет всех детей текущего узла, idParent номер родителя
 QList<QVariant>  Widget::removeRowDB(QList<QVariant> idList, QVariant idParent, QMap< int,  int> mapId )
{
    int value;
    foreach (int key, mapId.keys())//перебираем значения словаря записей таблицы данных
    {
         value=mapId.value(key);
         if(value==idParent)//если элемент потомок
         {
             idList<<removeRowDB(idList, key,mapId);
         }
    }
     idList<<idParent;//добавляем id в список на удаление
    return idList;
}




void Widget::modifiRow()
{
    InputDialog* pInputDialog = new InputDialog;
    if (pInputDialog->exec() == QDialog::Accepted)
        {
        //вводим данные
      QVariant name= pInputDialog->name();
      QVariant image=pInputDialog->image();
      QVariant state=pInputDialog->state();
     //Получаем модельный индекс выбранного элемента
     QModelIndex index = ui->treeView->selectionModel()->currentIndex();
     //
     QAbstractItemModel *yurModel = ui->treeView->model();
     TreeModel* model= qobject_cast<TreeModel*>(yurModel);
     //получаем выбранный элемент
      TreeItem* item2= model->getItem (index);
     int row1=item2->rowNumber();  //получаем номер строки элемента
       int idRow=item2->data(2).toInt ();  //получаем id строки
        int idRowParent=item2->data(3).toInt ();  //получаем id_parent строки
      QModelIndex parent=model->parent (index);  //получаем индекс родителя


      //item2->setData (0,name);
     // item2->setData (1,image);
      //item2->setData (4,state);

      QVector<QVariant> newValue;
      newValue<<name<<image<<state<<idRow;
      //применяем изменения в БД
      emit  valueChanged(newValue);
      //получаем изображение
    QSqlQuery query2;
       query2.prepare("SELECT * FROM  hierarhy  WHERE id =?;");
       query2.addBindValue(idRow);
       query2.exec();
       query2.next ();
      QByteArray image2 = query2.value(3).toByteArray ();
       query2.clear ();




      QList<QVariant> valueList;
      valueList<<name<<image2<<idRow<<idRowParent<<state;
      //заносим изменения в МОДЕЛЬ
         model->beginResetModel1();
      model->setData (index,valueList);
          model->endResetModel1();
     ui->treeView->selectionModel()->setCurrentIndex(model->index(row1, 0, parent),
     QItemSelectionModel::ClearAndSelect);

    newValue.clear ();
    valueList.clear ();


    }
     updateActions();

 delete pInputDialog;
}


//Вставляет новую строку
void Widget::insertChild1()
{
    InputDialog* pInputDialog = new InputDialog;
    if (pInputDialog->exec() == QDialog::Accepted)
        {
        //вводим данные
      QString name= pInputDialog->name();
      QString image=pInputDialog->image();
      int state=pInputDialog->state();
     //Получаем модельный индекс элемента
     QModelIndex index = ui->treeView->selectionModel()->currentIndex();
     QAbstractItemModel *yurModel = ui->treeView->model();
     TreeModel* model= qobject_cast<TreeModel*>(yurModel);

     //получаем выбранный элемент, он становится родителем вставляемого элемента
      TreeItem* itemParent= model->getItem (index);
      //получаем id выбранной строки, становится id_parent для вставляемого элемента
       int idParentRow=itemParent->data(2).toInt ();

       QVector<QVariant> newValue;
       newValue<<name<<image<<state<<idParentRow;
      //отправляем сигнал на запись данных в БД
      emit  valueInsert(newValue);
       //получаем id вставленного элемента
      int idRowI = rowID;
      QByteArray image2;
      //..........................////////////////////////..................
      newValue.clear ();
      //создаём новую строку в родителе
      model->beginResetModel1();
     // model->insertRow (0,index);

            //получаем изображение
          QSqlQuery query2;
             query2.prepare("SELECT * FROM  hierarhy  WHERE id =?;");
             query2.addBindValue(idRowI);
             query2.exec();
             query2.next ();
             image2 = query2.value(3).toByteArray ();
             query2.clear ();

              QPixmap pixmap;
             QSize size(20,20);
             //загружает изображение в Pixmap
             pixmap.loadFromData (image2);
             QIcon *icon=new  QIcon(pixmap) ;
             QPixmap pix= icon->pixmap (size);

       //переопределить, image2 чтоб выводилась иконка
       newValue<<name<<image2<<idRowI<<idParentRow<<state;

       //Добавляем новый УЗЕЛ в модель
        TreeItem* itemNew =new TreeItem(newValue,itemParent);
        //находим индекс вставляемого элемента
        int row1 =itemNew->rowNumber ();
        QModelIndex indexR;
        indexR=model->index (row1,0,index);
        //задаём роли для элемента
        QList<QVariant>  listname;
        listname<<name<<image2<<idRowI<<idParentRow<<state;
        QMap< int, QVariant> map4;
          map4.insert(8,listname);
          map4.insert(1,listname);
          map4.insert(0,listname);
          map4.insert(2,listname);
        model-> setItemData(indexR,map4);
        itemParent->appendChild(itemNew);//добавляем новый узел в потомки
        model->endResetModel1();
     //Выбираем вставленный узел
     ui->treeView->selectionModel()->setCurrentIndex(model->index(0, 0, index),
      QItemSelectionModel::ClearAndSelect);
        newValue.clear ();
    }
     //Меняем состояние кнопок
     updateActions();
  delete pInputDialog;
}

///предаёт значение id
void Widget::getRowId(int RowId)
{
    rowID=RowId;

}
//...................................................



void Widget::updateActions(const QItemSelection &selected,const QItemSelection &deselected) {
 updateActions();
}


void Widget::updateActions() {
 //Обновим состояние кнопок
 bool hasSelection = !ui->treeView->selectionModel()->selection().isEmpty();
 ui->delRow->setEnabled(hasSelection);

 bool hasCurrent = ui->treeView->selectionModel()->currentIndex().isValid();
 ui->modifi->setEnabled(hasCurrent);
 }


void Widget::slotCurrentPic(QModelIndex index)
{
    QPixmap outPixmap = QPixmap();

    QAbstractItemModel *yurModel = ui->treeView->model();
    TreeModel* model= qobject_cast<TreeModel*>(yurModel);



     TreeItem* item= model->getItem (index);

      QByteArray pix=item->data(1).toByteArray ();

    outPixmap.loadFromData(pix);
    // Устанавливаем изображение в picLabel
    ui->label->setPixmap(outPixmap.scaled(200,200));
}



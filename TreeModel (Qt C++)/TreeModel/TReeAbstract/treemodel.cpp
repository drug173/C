#include "treemodel.h"

TreeModel::TreeModel(QObject *parent) : QAbstractItemModel(parent)
{
    //создаём корневой узел с именами заголовков

    rootItem = new TreeItem({ tr("name"), tr("image"),tr("id"), tr("id_parent"), tr("state")});
    setDataModel(rootItem);

}

TreeModel::~TreeModel() {}




//..............///////////////.....setDataModel.........//////////////////////////
//устанавливает данные из таблицы базы данных в модель дерева
void TreeModel::setDataModel(TreeItem *parent)
{
    ///словарь записей таблицы данных
    QMap< int,  int> mapId; //хранит  id и id_parent
    ///список всех id
    QList<int> idList; //хранит все id элементов
    QSqlQuery query,query2,query3;
    ///id родителя и элемента
     int idItem, idParenItem;
    //............................................/////////////////
    //.............................///////////////////////
    //составляем список id всех элементов и родителей
    query.exec("SELECT * FROM hierarhy;");
    while (query.next())
    {
        idItem = query.value(0).toInt();
        idParenItem=query.value(1).toInt();
        idList<<idItem;   //список id всех элементов
        mapId.insert (idItem,idParenItem);// словарь родителей элементов
    }
    query.clear ();
    //............................................/////////////////
    //.............................///////////////////////
    //ищем корни(может быть несколько корней
    bool fl=false;
    int value;

    if(!mapId.isEmpty())//если словарь <id,Id_parent> не пуст
    {
        foreach (int key, mapId.keys())//перебираем значения словаря записей таблицы данных
      {
        value=mapId.value(key);//key это id записи
        fl=false;
        for(int j2=0;j2<idList.size();j2++)
          {
             if(value==idList[j2])//проверяем есть ли у элемента родитель
             {
                 fl=true;
                 break;//если родитель есть, переходим к другому
             }
           }
        //
        if(fl==false)//если родителя нет, то он корень дерева
        {
            //создаём узел
            //выбираем из базы запись с id==key
            query2.prepare("SELECT * FROM hierarhy WHERE id =?;");
            query2.addBindValue(key);
            query2.exec();
            query2.next();
            //создаём список с данными для узла
            QVector <QVariant> DataItemColumn; //Список данных столбцов в узле(строке)            
             DataItemColumn<< query2.value(2).toString();
             DataItemColumn<< query2.value(3).toByteArray ();
             DataItemColumn<< query2.value(0).toInt();
             DataItemColumn<< query2.value(1).toInt();
             DataItemColumn<< query2.value(4).toInt();
             //получаем индекс корня rootItem
             QModelIndex parentindex=this->index (0,0,QModelIndex());

             //создаём новый узел дерева
             TreeItem* item =new TreeItem(DataItemColumn,parent);
             parent->appendChild(item);//добавляем новый узел в потомки


            //вызываем рекурсивную функцию добавления потомков в текущий узел с индексом родителя
             addChild(mapId,key,item);
             mapId.remove (key);//удаляем из словаря id элемента
        }
      }
    }
}

//....... рекурсивная функция добавления потомков для узла с id равным key
 void TreeModel::addChild(QMap< int,int>& mapId, int key , TreeItem *parent)
 {

     if(!mapId.isEmpty())//если словарь <id,Id_parent> не пуст
     {
         int value2;
         QSqlQuery query3;
         QList<TreeItem*> rowItems;//спиок данных в строке по столбцам
     foreach (int key2, mapId.keys())//перебираем значения словаря записей таблицы данных
      {
         value2=mapId.value(key2);
         if(value2==key)//проверяем является ли узел key родителем текущему узлу
          {
             query3.prepare("SELECT * FROM hierarhy WHERE id =?;");
             query3.addBindValue(key2);
             query3.exec();
             query3.next();
             QVector <QVariant> DataItemColumn; //Список данных столбцов в узле(строке)             
              DataItemColumn<< query3.value(2).toString();
              DataItemColumn<< query3.value(3).toByteArray();
              DataItemColumn<< query3.value(0).toInt();
              DataItemColumn<< query3.value(1).toInt();
              DataItemColumn<< query3.value(4).toInt();
              //создаём новый узел дерева
              TreeItem* item =new TreeItem(DataItemColumn,parent);
              query3.clear ();
              parent->appendChild(item);//добавляем узел нового родителя в потомки корня



              //вызываем рекурсивную функцию добавления потомков в текущий узел
               addChild(mapId,key2,item);



         }
      }
     }
        //mapId.remove (key);//удаляем из словаря id элемента
}


 QVariant TreeModel::data (const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();
  if (role != Qt::DisplayRole  && role != Qt::EditRole && role != Qt::BackgroundRole && role !=Qt::DecorationRole) return QVariant();
    TreeItem *item = getItem(index);

 if (role == Qt::BackgroundRole && (index.column()==0)){
        int state= item->data(4).toInt ();
     if(state==0 )
     {
        return  QColor( Qt::red);
     }
     if(state==1 )
     {
        return  QColor(Qt::yellow);
     }
     if(state==2 )
     {
        return  QColor(Qt::green);
     }
     return  QColor( Qt::lightGray);
}
 if (role == Qt::DecorationRole && (index.column()==1) ){

     TreeItem* item= this->getItem (index);

      QByteArray pix=item->data(1).toByteArray ();
    QPixmap pix1;
    pix1.loadFromData(pix);
    QSize size(50,50);
    QIcon icon(pix1);
    icon.pixmap (size);

    return  icon;
}
 if (role == Qt::DisplayRole  || role == Qt::EditRole)
   if((index.column()==0) || (index.column()==2)|| (index.column()==3)||(index.column()==4) )
   {
   return item->data(index.column());
   }

return QVariant();
}





//количество столбцов у потомков элемента (всегда равно 5)
int TreeModel::columnCount(const QModelIndex &parent) const
{
    return 5;//количество узлов во всех узлах равно 5
}

//количество детей элемента
int TreeModel::rowCount(const QModelIndex &parent) const
{
 TreeItem *parentItem = getItem(parent);
 return parentItem->childCount();
}


// индекс модели по заданным строке, столбцу и родителю
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0) return QModelIndex();
    TreeItem *parentItem = getItem(parent);
    TreeItem *childItem = parentItem->child(row);
    if (childItem) return createIndex(row, column, childItem);
    else return QModelIndex();
}

//индекс родителя
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
 if (!index.isValid()) return QModelIndex();
 TreeItem *childItem = getItem(index);
 TreeItem *parentItem = childItem->parentItem();
 if (parentItem == rootItem) return QModelIndex();
 return createIndex(parentItem->rowNumber(), 0, parentItem);
}

//ссылка на элемент по индексу
TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
     TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
     if (item) return item;
    }
    return rootItem;
}




/*
//устанавливает заголовки в столбцах
QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
 if (orientation == Qt::Horizontal && role == Qt::DisplayRole) return rootItem->data(section);
 return QVariant();
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role) {

    if (role != Qt::EditRole || orientation != Qt::Horizontal) return false;
    bool result = rootItem->setData(section, value);
    if (result) {
     emit headerDataChanged(orientation, section, section);
    }
    return result;
}
*/



//добавляет данные в узел
bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role) {
//if (role != Qt::EditRole) return false;
 TreeItem *item = getItem(index);
 bool result = true;
 QList<QVariant> listValue;
 listValue=value.toList ();
 if(!(item->setData (0,listValue.at(0)))){result=false;}
 if(!(item->setData (1,listValue.at(1)))){result=false;}
 if(!(item->setData (2,listValue.at(2)))){result=false;}
 if(!(item->setData (3,listValue.at(3)))){result=false;}
 if(!(item->setData (4,listValue.at(4)))){result=false;}
 if (result) {
  emit dataChanged(index, index);
 }
 return result;
}





bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent) {
 TreeItem *parentItem = getItem(parent);
 bool success = true;
 beginRemoveRows(parent, position, position + rows - 1);
 success = parentItem->removeChild(position);
 endRemoveRows();
 return success;
}

void TreeModel::beginResetModel1()
{

    beginResetModel ();
}

void TreeModel::endResetModel1()
{

    endResetModel();
}




bool TreeModel::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles)
{
    bool b = true;

    for (QMap<int, QVariant>::ConstIterator it = roles.begin(); it != roles.end(); ++it)
        b = b && setData(index, it.value(), it.key());
    return b;
}

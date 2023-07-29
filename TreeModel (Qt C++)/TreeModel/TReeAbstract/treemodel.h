#ifndef MODELTREE_H
#define MODELTREE_H
#include <QAbstractItemModel>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include "database.h"
#include <QtWidgets>
#include "treeitem.h"
#include <QSize>

class TreeModel  : public  QAbstractItemModel
{

 Q_OBJECT
public:

    TreeModel (QObject *parent = nullptr);


        ~TreeModel() override;
        ///устанавливает данные из таблицы базы данных в модель дерева
        void setDataModel(TreeItem *parent=nullptr);
        //данные заголовка
       // QVariant headerData(int section, Qt::Orientation orientation,  int role = Qt::DisplayRole) const override;
        // bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

          ///по строке и столбцу возвращает индекс элемента.
        QModelIndex index(int row, int column=0, const QModelIndex &parent = QModelIndex()) const override;
        /// возвращает индекс родителя элемента;
        QModelIndex parent(const QModelIndex &index) const override;
        ///добавляет потомка в текущий узел
         void addChild(QMap< int,int>& mapId, int key , TreeItem *parent);

         //получить данные из модельного индекса index с ролью role
        QVariant data(const QModelIndex &index, int role) const override;

      //  Qt::ItemFlags flags(const QModelIndex &index) const override;

        bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles) override;

        ///количество детей у элемента
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        ///количество столбцов для дочерних элементов
       int columnCount(const QModelIndex &parent = QModelIndex()) const  override;
       ///установить в узел с индексом index значение value
        bool setData(const QModelIndex &index, const  QVariant &value, int role = Qt::EditRole) override;
       ///удаляет строки
       bool removeRows(int position, int rows=1, const QModelIndex &parent = QModelIndex()) override;

       ///получение  элемента по индексу
        TreeItem  *getItem(const QModelIndex &index) const;
        void beginResetModel1();
        void endResetModel1();
       private:

             /// корневой узел
             TreeItem *rootItem;


};

#endif // MODELTREE_H

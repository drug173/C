#ifndef TREEITEM_H
#define TREEITEM_H
#include <QList>
#include <QVector>
#include <QVariant>



//Узел представляет собой список столбцов (строку)
//узел содержит  список дочерних элементов, список данных текущего узла по столбцам
//и ссылку на родителя
///Содержит информацию об узле
class TreeItem
{
public:
    TreeItem(const QVector<QVariant> &data, TreeItem *parent=nullptr ) ;
    ///Количество дочерних элементов
    int childCount() const;
    ///Вернуть ссылку на дочерний элемент
    TreeItem *child(int row);
    ///Вернуть родительский элемент
    TreeItem *parentItem();
    ///Вернуть номер строки элемента в родительском узле
    int rowNumber() const;
    ///Добавить узел-потомок
    void appendChild(TreeItem *child);
    ///Вернуть данные указанного столбца
    QVariant data(int column) const;
    ///метод ставит значение value в столбец column элемента при редактированиии(изменении) элемента
    bool setData(int column, const QVariant &value);
    bool removeChild(int row);  //Удалить потомкa

private:

  ///Список дочерних элементов
 QList <TreeItem*> m_childItems;
 ///Список данных текущего узла
 QVector <QVariant> m_itemData;
 ///Ссылка на родительский узел
 TreeItem *m_parentItem;


};

#endif // TREEITEM_H

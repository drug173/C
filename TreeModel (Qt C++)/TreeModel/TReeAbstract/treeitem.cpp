#include "treeitem.h"

TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent)
{
    m_parentItem = parent;
    m_itemData = data;

}


//количество дочерних элементов
int TreeItem::childCount() const {
 return m_childItems.count();
} //получает количество потомков узла (Количество потомков узла = длине списка потомков)


//получение потомка по строке
TreeItem *TreeItem::child (int row) {
 return m_childItems.value(row);//По номеру строки выбрать нужного потомка из списка
}

//Вернуть ссылку на родителя
TreeItem *TreeItem::parentItem() {
 return m_parentItem;
}



//возвращает свой номер  в списке потомков своего родителя
int TreeItem::rowNumber() const {
 if (m_parentItem) return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));
 return 0;
}//Если есть родитель - найти свой номер в списке его потомков.Иначе вернуть 0

// добавляет данные (узел в список потомков) при первом построении модели и не используется при обычном использовании.
void TreeItem::appendChild(TreeItem *item) {
 m_childItems.append(item);
}

//Получить данные из нужного столбца
QVariant TreeItem::data (int column) const {
 return m_itemData.value(column);
}


// метод ставит значение value в столбец column элемента при редактированиии(изменении) элемента
bool TreeItem::setData(int column, const QVariant &value) {
 if (column < 0 || column >= m_itemData.size()) return false;
 m_itemData[column] = value;
 return true;
}



bool TreeItem:: removeChild( int row)
{
    //if(!row){return false;}

        delete this->m_childItems.takeAt(row);

    int i = 0;
    i++;
    return true;
}






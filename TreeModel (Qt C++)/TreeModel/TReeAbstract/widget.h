#ifndef WIDGET_H
#define WIDGET_H
#include "database.h"
#include <QWidget>
#include <QSqlTableModel>
#include "treemodel.h"
#include <QDialog>
#include "inputdialog.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
        ///id вставляемого элемента
    int rowID;

     QPixmap pixmap1;
     void updateActions(); //слот для обновления состояния кнопок
private slots: //слоты для действий, выполняемых по кнопкам


    void slotCurrentPic(QModelIndex index);

   void insertChild1();
    void modifiRow();
   void removeRow1();
    void getRowId(int RowId);
public slots: //для реализации сигнала selectionChanged у QTreeView::selectionModel
    void updateActions(const QItemSelection &,const QItemSelection &);
 signals:
     void valueChanged(QVector<QVariant> newValue);
     ///сигнал на запись в БД
     void valueInsert(QVector<QVariant> newValue);
private:
    InputDialog iDialog;
    Ui::Widget *ui;
    void removeRowCascade(QModelIndex index, TreeModel *model);
    QList<QVariant> removeRowDB(QList<QVariant> idList, QVariant idParent, QMap< int,  int> mapId );
};

#endif // WIDGET_H

#ifndef DOCTORDELEGATE_H
#define DOCTORDELEGATE_H

#include <QItemDelegate>
#include <QMap>


#include "DepartmentService.h"

class DoctorDelegate : public QItemDelegate
{
public:
    DoctorDelegate(QWidget *parent = NULL):
        QItemDelegate(parent)
    {
        vector<Department> departments=DepartmentService().getAllDepartments();
        int i=0;
        for(Department department:departments){
            departmentNames.append(department.getName().c_str());
            indexToIdMap.insert(i,department.getId());
            idToIndexMap.insert(department.getId(),i);
            i++;
        }
    }

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
private:
    QMap<int,int> idToIndexMap;
    QMap<int,int> indexToIdMap;
    QStringList departmentNames;
};

#endif // DOCTORDELEGATE_H

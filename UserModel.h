#ifndef USERMODEL_H
#define USERMODEL_H


#include <QAbstractTableModel>

#include "UserService.h"

class UserModel : public QAbstractTableModel
{
public:
    UserModel(vector<User> users,QObject *parent=nullptr);

    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    void addUser(const User& user);
    void deleteUser(int index);

    vector<User> getUsers();
    User getUserByIndex(int index);

    void reloadFromDataSource();

    void setUsersAndReload(const vector<User>& users);
private:
    vector<User> users;

    UserService service;
};

#endif // USERMODEL_H

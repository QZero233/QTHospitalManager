#include "UserModel.h"

#include "TimeUtils.h"

#include <QMessageBox>

UserModel::UserModel(vector<User> users,QObject *parent):
QAbstractTableModel(parent),
users(users)
{

}

int UserModel::rowCount(const QModelIndex &parent) const{
    return users.size();
}

int UserModel::columnCount(const QModelIndex &parent) const{
    //Username
    //Password
    //Group

    //Name
    //Tel
    //Gender
    //Age
    return 7;
}

QVariant UserModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();


    //Display role: give rendered data
    //Edit role: give raw data
    if(role!=Qt::DisplayRole && role!=Qt::EditRole)
        return QVariant();

    int row=index.row();
    int column=index.column();

    User user=users.at(row);

    switch(column){
    case 0:
        return user.getUsername().c_str();
    case 1:
        return "******";
    case 2:
        if(role==Qt::EditRole)
            return user.getGroup();
        return user.getGroup()==User::GROUP_ADMIN?"管理员":"患者";
    case 3:
        return user.getName().c_str();
    case 4:
        return user.getTelephone().c_str();
    case 5:
        if(role==Qt::EditRole)
            return user.getGender();
        return user.getGender()==User::GENDER_MALE?"男":"女";
    case 6:
        return user.getAge();
    default:
        return QVariant();
    }
}

bool UserModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(!index.isValid())
        return false;

    User user=users[index.row()];
    switch(index.column()){
    case 1:
        user.setPassword(value.toString().toStdString());
        break;
    case 2:
        user.setGroup(value.toInt());
        break;
    case 3:
        user.setName(value.toString().toStdString());
        break;
    case 4:
        user.setTelephone(value.toString().toStdString());
        break;
    case 5:
        user.setGender(value.toInt());
        break;
    case 6:
        user.setAge(value.toInt());
        break;
    }

    users[index.row()]=user;
    UserService().updateUser(user);

    return true;
}

QVariant UserModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation==Qt::Horizontal && role==Qt::DisplayRole){
        switch(section){
        case 0:
            return "用户名";
        case 1:
            return "密码";
        case 2:
            return "组别";
        case 3:
            return "真实姓名";
        case 4:
            return "电话号码";
        case 5:
            return "性别";
        case 6:
            return "年龄";
        }
    }

    return QVariant();
}

Qt::ItemFlags UserModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

void UserModel::addUser(const User& user){
    beginInsertRows(QModelIndex(),users.size(),users.size());

    service.addUser(user);
    users.push_back(user);

    endInsertRows();
}

void UserModel::deleteUser(int index){
    beginRemoveRows(QModelIndex(),index,index);

    User target=users[index];
    service.deleteUser(target.getUsername());

    vector<User> backup=users;
    users=vector<User>();
    for(int i=0;i<backup.size();i++){
        if(i!=index)
            users.push_back(backup[i]);
    }

    endRemoveRows();
}

vector<User> UserModel::getUsers(){
    return users;
}

User UserModel::getUserByIndex(int index){
    return users[index];
}

void UserModel::reloadFromDataSource(){
    for(int i=0;i<users.size();i++){
        users[i]=service.getUser(users[i].getName());
    }

    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(users.size() - 1, columnCount(QModelIndex()) - 1);

    emit dataChanged(topLeft, bottomRight);
    emit layoutChanged();
}

void UserModel::setUsersAndReload(const vector<User>& users){
    this->users=users;
    reloadFromDataSource();
}



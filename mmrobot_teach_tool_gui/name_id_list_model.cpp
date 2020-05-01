#include "name_id_list_model.h"
NameIDElement::NameIDElement(const QString &name, const int &id)
    :name_(name), id_(id){
        name_and_id_ = name_ +" "+  QString::number(id_);
}
NameIDElement::NameIDElement(const std::string &name, const int &id)
    :id_(id){
    name_ = QString::fromStdString(name);
    name_and_id_ = name_ + " "+ QString::number(id_);
}
NameIDListModel::NameIDListModel(QObject *parent):QAbstractListModel(parent){}
QHash<int, QByteArray> NameIDListModel::roleNames() const{
    return { { NameRole, "name" },
        { IdRole, "id" },
        {NameIdRole, "name_and_id"}};
}
int NameIDListModel::rowCount(const QModelIndex & parent) const {
    if (parent.isValid())
        return 0;
    return list_.size();
}
bool NameIDListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!hasIndex(index.row(), index.column(), index.parent()) || !value.isValid())
        return false;

    NameIDElement &item = list_[index.row()];
    if (role == NameRole){
        item.name_ = value.toString();
        item.name_and_id_ = item.name_ + " "+ QString::number(item.id_ );
    }
    else if (role == IdRole){
        item.id_ = value.toInt();
        item.name_and_id_ = item.name_ +" "+  QString::number(item.id_ );
    }
    else return false;

    emit dataChanged(index, index, { role, NameIdRole } );
    return true ;

}
QVariant NameIDListModel::data(const QModelIndex & index, int role) const  {
    if (!hasIndex(index.row(), index.column(), index.parent()))
        return {};

    const NameIDElement &item = list_.at(index.row());
    if (role == NameRole) return item.name_;
    if (role == IdRole) return item.id_;
    if (role == NameIdRole) return item.name_and_id_;
    return {};
}
void NameIDListModel::addListItem(const NameIDElement &element){
    list_.push_back(element);
}
void NameIDListModel::clear(){
    list_.clear();
}
void NameIDListModel::beginResetModel(){
    QAbstractListModel::beginResetModel();
}
void NameIDListModel::endResetModel(){
    QAbstractListModel::endResetModel();
}

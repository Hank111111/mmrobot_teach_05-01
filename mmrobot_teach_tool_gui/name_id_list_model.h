#ifndef LISTMODEL_H
#define LISTMODEL_H
#include <QAbstractListModel>
class NameIDElement{
public:
    QString name_;
    int id_;
    QString name_and_id_;
    NameIDElement(const QString &name, const int &id);
    NameIDElement(const std::string &name, const int &id);
};

class NameIDListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        IdRole,
        NameIdRole,
    };

    explicit NameIDListModel(QObject *parent = nullptr);
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override ;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override ;
    void addListItem(const NameIDElement &element);
    void clear();
    void beginResetModel();
    void endResetModel();

private:
    QList<NameIDElement> list_;

};
#endif // LISTMODEL_H

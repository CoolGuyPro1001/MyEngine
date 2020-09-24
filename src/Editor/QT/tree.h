#include <QModelIndex>
#include <QVariant>
#include <QVector>
#include <QAbstractItemModel>

class TreeItem
{
public:
    explicit TreeItem(const QVector<QVariant>& data, TreeItem* parent = nullptr);
    ~TreeItem();

    TreeItem* child(int number);

    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const
    ;
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);

    TreeItem* parent();

    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);

    int childNumber() const;
    bool setData(int column, const QVariant& value);

private:
    QVector<TreeItem*> childItems;
    QVector<QVariant> itemData;
    TreeItem *parentItem;
};


class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel(const QStringList& headers, const QString& data, QObject* parent = nullptr);
    ~TreeModel();

    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role = Qt::EditRole) override;

    bool insertColumns(int position, int columns, const QModelIndex& parent = QModelIndex()) override;
    bool removeColumns(int position, int columns, const QModelIndex& parent = QModelIndex()) override;

    bool insertRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;

private:
    //void setupModelData(const QStringList &lines, TreeItem *parent);
    TreeItem *getItem(const QModelIndex &index) const;

    TreeItem *rootItem;
};
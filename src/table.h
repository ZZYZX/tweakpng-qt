#ifndef TABLE_H
#define TABLE_H

#include <QString>
#include <QAbstractTableModel>
#include <QList>
#include <QStringList>

class TableItem
{

public:
    TableItem();
    QString name; // Chunk name: IHDR, IEND, etc...
    QString len;  // Total bytelength
    QString crc;  // CRC
    QString attr; // Chunk attributes
    QString data; // Contents
};
 
class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TableModel(QObject *parent = 0);
 
    QStringList header_data;
    QList<TableItem *> list;
 
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
 
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
 
    QVariant headerData(int section,Qt::Orientation orientation, int role=Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
// signals:
 
// public slots:
 
};

#endif

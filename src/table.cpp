#include "table.h"


ChunkTableItem::ChunkTableItem()
{
    this->name = "";
    this->len  = "";
    this->crc  = "";
    this->attr = "";
    this->data = "";
}


ChunkTableModel::ChunkTableModel(QObject *parent): QAbstractTableModel(parent)
{
    // Let's start by assigning names to our columns
    header_data << tr("Chunk");
    header_data << tr("Length");
    header_data << tr("CRC");
    header_data << tr("Attributes");
    header_data << tr("Contents");

    for(int i = 1; i < 4; i++) {
        ChunkTableItem* it = new ChunkTableItem;
        list.append(it);
    }
}
 
QVariant ChunkTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    // Alignment of text withing the cells
    if(role == Qt::TextAlignmentRole) {
        if(index.column() == 1)
            return QVariant(Qt::AlignRight | Qt::AlignVCenter);

        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    }
 
    if(index.row() >= list.size())
        return QVariant();

    if(role == Qt::DisplayRole || role == Qt::EditRole) {
        if (index.column() == 0 )
            return list.at(index.row())->name;
        if (index.column() == 1 )
            return list.at(index.row())->len;
        if (index.column() == 2 )
            return list.at(index.row())->crc;
        if (index.column() == 3 )
            return list.at(index.row())->attr;
        if (index.column() == 4 )
            return list.at(index.row())->data;
    }

    return QVariant();
}
 
bool ChunkTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        switch(index.column()) {
            case 0:
                list[row]->name = value.toString();
            break;

            case 1:
                list[row]->len  = value.toInt();
            break;

            case 2:
                list[row]->crc  = value.toString();
            break;

            case 3:
                list[row]->attr = value.toString();
            break;

            case 4:
                list[row]->data = value.toString();
            break;

            default:
                return false;
            break;
        }

        // emit(dataChanged(index, index));

        return true;
    }

    return false;
}

int ChunkTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return list.size();
}
 
int ChunkTableModel::columnCount(const QModelIndex &parent)    const
{
    Q_UNUSED(parent);

    return 5;
}

QVariant ChunkTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // Alignment of text within the headers
    if(role == Qt::TextAlignmentRole ) {
        // Row headers
        if(orientation == Qt::Horizontal) {
            return (section == 1) ? Qt::AlignRight : Qt::AlignLeft;
        }
        // Col headers
        if(orientation == Qt::Vertical) {
            return Qt::AlignCenter;
        }
    }

    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return header_data.at(section);
    } else {
        return QString("%1").arg( section + 1 );
    }
}

Qt::ItemFlags ChunkTableModel::flags(const QModelIndex &index) const
{
   if (!index.isValid())
        return Qt::ItemIsEnabled;
 
   return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}


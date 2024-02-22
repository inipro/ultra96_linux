#include "mydatamodel.h"
#include <QDebug>
#include <QSize>

MyDataModel::MyDataModel()
{
	for (int i=0; i<60; i++) m_data.push_back(0.0);
}

int MyDataModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return m_data.size();
}

int MyDataModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return 2;
}

QVariant MyDataModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid() || role != Qt::DisplayRole)
		return QVariant();

	if (index.column() == 0)
		return index.row() - 59;
	return m_data[index.row()];
}

QVariant MyDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	Q_UNUSED(orientation)

	if (role == Qt::SizeHintRole)
		return QSize(1, 1);
	return QVariant();

}

QHash<int, QByteArray> MyDataModel::roleNames() const
{
	static QHash<int, QByteArray> roleNames{{ValueRole, "value"}};
	return roleNames;
}

void MyDataModel::addData(const float value)
{
	beginResetModel();

	beginRemoveRows(QModelIndex(), 0, 0);
	m_data.pop_front();
	endRemoveRows();

	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	m_data.push_back(value);
	endInsertRows();

	endResetModel();
}


#pragma once
#include <QAbstractTableModel>
#include <QVector>

class MyDataModel : public QAbstractTableModel
{
	Q_OBJECT

	enum { ValueRole = Qt::DisplayRole };

public:
	MyDataModel();

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, 
			Qt::Orientation orientation, 
			int role = Qt::DisplayRole) const override;

	QHash<int, QByteArray> roleNames() const override;

	void addData(const float value);

private:
	QVector<float> m_data;
};

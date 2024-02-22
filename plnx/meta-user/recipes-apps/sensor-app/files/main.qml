import QtQuick 2.7
import QtQuick.Controls 1.4
import QtCharts 2.1

ApplicationWindow {
	id: root
	width: 640
	height: 480
	visible: true
	title: qsTr("Sensor App")

	ChartView {
		id: chartView
		anchors.fill: parent
		
		ValueAxis {
			id: axisX
			min: -59
			max: 0
			labelFormat: "%d sec"
		}

		ValueAxis {
			id: axisY
			min: 0
			max: 40
			labelFormat: "%d lux"
		}

		LineSeries {
			id: series
			axisX: axisX
			axisY: axisY
			name: "Ambient Light"
		}

		VXYModelMapper {
			id: myDataModelMapper
			model: myDataModel
			series: series
			firstRow: 0
			xColumn: 0
			yColumn: 1
		}
	}
}

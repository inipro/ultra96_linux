#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFile>
#include <QTimer>
#include "mydatamodel.h"

int main(int argc, char *argv[])
{

	QApplication app(argc, argv);

	MyDataModel myDataModel;

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("myDataModel", &myDataModel);
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	QTimer *timer = new QTimer();
	QObject::connect(timer, &QTimer::timeout, &myDataModel, [&myDataModel]() {
		QFile file("/sys/devices/platform/axi/80000000.axi_quad_spi/spi_master/spi2/spi2.0/adc");
		if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			int al = file.readAll().trimmed().toInt();
			al = al >> 4;
			myDataModel.addData(al);
		}
		
	});
	timer->start(1000);

	return app.exec();
}

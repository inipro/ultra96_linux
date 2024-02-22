#
# This is the sensor-app application recipe
#
#

SUMMARY = "sensor-app application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "qtdeclarative"

SRC_URI = "\
	file://CMakeLists.txt \
	file://main.cpp \
	file://mydatamodel.h \
	file://mydatamodel.cpp \
	file://main.qml \
	file://qml.qrc \
	"

S = "${WORKDIR}"

RDEPENDS:${PN} += " \
		sensor-fw \
		"

inherit cmake cmake_qt5

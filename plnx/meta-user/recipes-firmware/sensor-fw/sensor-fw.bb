#
# This file is the sensor-fw recipe.
#

SUMMARY = "Simple sensor-fw to use fpgamanager class"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit dfx_dtg_zynqmp_full

COMPATIBLE_MACHINE:zynqmp = ".*"

SRC_URI = "file://sensor_wrapper.xsa \
	   file://pl-custom.dtsi \
	   file://0001-Add-avnet-ultra96-ver2.patch \
           "
RDEPENDS:${PN} += "pmodals"

inherit bitfile_info

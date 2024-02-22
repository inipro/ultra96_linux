#
# This is the video-app application recipe
#
#

SUMMARY = "video-app application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS = "v4l-utils gstreamer1.0 gstreamer1.0-plugins-base"

RDEPENDS:${PN} += "pcam5c-fw gstreamer1.0-plugins-good gstreamer1.0-plugins-bad"

SRC_URI = "\
	file://CMakeLists.txt \
	file://main.c \
	"

S = "${WORKDIR}"


inherit pkgconfig cmake

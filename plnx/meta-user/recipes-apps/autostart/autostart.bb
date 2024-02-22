DESCRIPTION = "Init script to start at boot"
SUMMARY = "Init script to start at boot"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://autostart.sh \
	   file://autostart.service \
"

inherit update-rc.d systemd

RDEPENDS:${PN} += " \
	qt5everywheredemo \
	"
INSANE_SKIP:${PN} += "installed-vs-shipped"

INITSCRIPT_NAME = "autostart.sh"
INITSCRIPT_PARAMS = "start 99 S ."

SYSTEMD_PACKAGES = "${PN}"
SYSTEMD_SERVICE:${PN} = "autostart.service"
SYSTEMD_AUTO_ENABLE:${PN}="enable"

do_install () {
	if ${@bb.utils.contains('DISTRO_FEATURES', 'sysvinit', 'true', 'false', d)}; then
		install -d ${D}${sysconfdir}/init.d/
		install -m 0755 ${WORKDIR}/autostart.sh ${D}${sysconfdir}/init.d/
	fi

	install -d ${D}${bindir}
	install -m 0755 ${WORKDIR}/autostart.sh ${D}${bindir}
	install -d ${D}${systemd_system_unitdir} 
	install -m 0644 ${WORKDIR}/autostart.service ${D}${systemd_system_unitdir}
}

FILES:${PN} += "\
	${@bb.utils.contains('DISTRO_FEATURES','sysvinit','${sysconfdir}/init.d/autostart.sh', '', d)} \
"

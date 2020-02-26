SUMMARY = "libreader for GigaBlue Model ${MACHINE}"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"

RDEPENDS_${PN} = "libsdl"

COMPATIBLE_MACHINE = "^(gbtrio4k)$"

SRCDATE = "20200226"

PV = "${SRCDATE}"
PR = "r0"

SRC_URI = "http://define-sw.dyndns.tv/openatv/openpli/${MACHINE}-libreader-${SRCDATE}.tar.gz"

S = "${WORKDIR}"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/libreader ${D}/${bindir}
}

do_package_qa() {
}

FILES_${PN}  = "${bindir}/libreader"

SRC_URI[md5sum] = "541939248abf12d7055143fd3e380e51"
SRC_URI[sha256sum] = "f7f2f2d5d01e8e7eb3c7d8f5e27ee9810e8b71faea04a2555bf2ee5717649f80"

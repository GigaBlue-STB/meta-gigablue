SUMMARY = "libreader for GigaBlue Model ${MACHINE}"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"

RDEPENDS_${PN} = "libsdl"

COMPATIBLE_MACHINE = "^(gbtrio4k)$"

SRCDATE = "20200612"

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

SRC_URI[md5sum] = "6efcb0f4fcf73d4a62c27578e9679fc9"
SRC_URI[sha256sum] = "a15ee4bb4c073c001fbefac09af01ac42518b5acae47af6a770a13f942a42ef8"

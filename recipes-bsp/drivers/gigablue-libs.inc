DESCRIPTION = "shared lib for ${MACHINE}"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"

PACKAGE_ARCH = "${MACHINE_ARCH}"

RDEPENDS_${PN} = "curl"

PV = "${SRCDATE}"
PR = "r1"

inherit lib_package

INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
SOLIBS = ".so"
FILES_SOLIBSDEV = ""

SRC_URI = "http://define-sw.dyndns.tv/openatv/openpli/${MACHINE}-hilib-${SRCDATE}.tar.gz"

S = "${WORKDIR}/hilib"


# The driver is a set of binary libraries to install
# there's nothing to configure or compile
do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
	install -d ${D}${libdir}
	install -m 0755 ${S}/*.so ${D}${libdir}/
}

do_package_qa() {
}

FILES_${PN} += "${libdir}/*"

INSANE_SKIP_${PN} = "already-stripped dev-so"

DESCRIPTION = "Gigablue xbmc support"
SECTION = "base"
LICENSE = "CLOSED"

PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI = "http://source.mynonpublic.com/gigablue/v3ddriver/xbmc-support_gb7252_${GLPR}.tar.gz"

S = "${WORKDIR}/xbmc-support"

do_install(){
    install -d ${D}${includedir}
    install -d ${D}${libdir}
    install -m 0644 ${S}/gles_init.h ${D}${includedir}
    install -m 0644 ${S}/gles_init.a ${D}${libdir}/gles_init.a
    ln -sf gles_init.a ${D}${libdir}/libgles_init.a
}

PACKAGES = "${PN}"
FILES_${PN} = "${includedir} ${libdir}"

INSANE_SKIP_${PN} = "staticdev"

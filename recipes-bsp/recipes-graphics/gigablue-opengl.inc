DESCRIPTION = "libgles for ${MACHINE}"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"

PR = "${SRCDATE}"

PROVIDES = "virtual/libgles1 virtual/libgles2 virtual/egl"
RPROVIDES_${PN} = "virtual/libgles1 virtual/libgles2 virtual/egl libEGL.so libGLESv2.so libmali.so"

SRC_URI = "http://define-sw.dyndns.tv/openatv/openpli/${MACHINE}-opengl-${SRCDATE}.tar.gz"

S = "${WORKDIR}/usr"

# The driver is a set of binary libraries to install
# there's nothing to configure or compile
do_configure[noexec] = "1"

# Generate a mali rules script
do_compile_append () {
	cat > 50-mali.rules << EOF
KERNEL=="mali0", MODE="0660", GROUP="video"
EOF
}

do_install() {
    install -d ${D}${libdir}
    install -d ${D}${sysconfdir}/udev/rules.d
    install -m 0755 ${S}/lib/libMali.so ${D}${libdir}
    ln -sf libMali.so ${D}${libdir}/libmali.so
    ln -sf libMali.so ${D}${libdir}/libGLESv2.so.2.0
    ln -sf libGLESv2.so.2.0 ${D}${libdir}/libGLESv2.so.2
    ln -sf libGLESv2.so.2 ${D}${libdir}/libGLESv2.so
    ln -sf libMali.so ${D}${libdir}/libGLESv1_CM.so.1.1
    ln -sf libGLESv1_CM.so.1.1 ${D}${libdir}/libGLESv1_CM.so.1
    ln -sf libGLESv1_CM.so.1 ${D}${libdir}/libGLESv1_CM.so
    ln -sf libMali.so ${D}${libdir}/libEGL.so.1.4
    ln -sf libEGL.so.1.4 ${D}${libdir}/libEGL.so.1
    ln -sf libEGL.so.1 ${D}${libdir}/libEGL.so
    install -m 0644 ${S}/50-mali.rules ${D}${sysconfdir}/udev/rules.d/50-mali.rules
    install -d ${D}${includedir}
    install -m 0644 ${S}/include/hi_dbe.h ${D}${includedir}/
    for d in EGL GLES GLES2 KHR; do
        install -d ${D}${includedir}/$d
        for f in ${S}/include/$d/*.h; do
           install -m 0644 $f ${D}${includedir}/$d/
        done
    done
}

do_package_qa() {
}

FILES_${PN} = "${libdir}/* /etc/udev/rules.d/50-mali.rules"
FILES_${PN}-dev = "${includedir}/*"

INSANE_SKIP_${PN} += "already-stripped dev-so ldflags"

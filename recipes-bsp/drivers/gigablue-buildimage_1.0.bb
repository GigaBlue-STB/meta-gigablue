SUMMARY = "Create the usb ugrade file"
LICENSE = "CLOSED"

SRC_URI = "file://buildimage.zip"

S = "${WORKDIR}"

do_install () {
        install -d ${D}/${sbindir}
        install -m 775 ${S}/mkupdate ${D}/${sbindir}
}

INSANE_SKIP_${PN} += "ldflags"

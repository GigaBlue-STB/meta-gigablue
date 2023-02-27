DESCRIPTION = "E2 Chromium Plugin"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "CLOSED"
# require conf/license/license-close.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

PV = "1.0"
PR = "20180628_r0"
SRC_URI = "http://source.mynonpublic.com/gigablue/chromium/e2plugin-chromium-gigablue_${PR}.tar.gz"
SRC_URI_append =+ " \
           file://port-to-python3-gigablue.patch"
           
COMPATIBLE_MACHINE = "^(gbquad4k|gbue4k)$"

DEPENDS = "chromium-browser"
RDEPENDS_${PN} = "chromium-browser"

do_install_append() {
    install -d ${D}/usr/lib/enigma2/python/Plugins/Extensions/Chromium
    cp -aRf ${WORKDIR}/e2plugin/* ${D}/usr/lib/enigma2/python/Plugins/Extensions/Chromium/
}

do_package_qa() {
}

PROVIDES += "enigma2-plugin-extensions-chromium"
RPROVIDES_${PN} += "enigma2-plugin-extensions-chromium"

FILES_${PN} = "/"

SRC_URI[md5sum] = "6b1db0620fd187252d1195a4389da930"
SRC_URI[sha256sum] = "9723574753390358d567bcfeb364485f26d279417436c927f0534d27c24f9779"


SUMMARY = "2nd bootloader support"
SECTION = "base"
PRIORITY = "required"
MAINTAINER = "Gigablue"
LICENSE = "proprietary"
PACKAGE_ARCH := "${MACHINE}"

require conf/license/license-gplv2.inc

PR = "r1"
ALLOW_EMPTY_${PN} = "1"

inherit deploy
do_deploy() {
    if [ -e boot.bin  ]; then
    install -m 0644 boot.bin  ${DEPLOYDIR}/gb7252_boot.bin
    fi
    if [ -e rescue.bin  ]; then
    install -m 0644 rescue.bin  ${DEPLOYDIR}/gb7252_rescue.bin
    fi
}

SRC_URI = "http://impex-sat.de/gigablue/initrd/initrd_gb7252_${SRCDATE}.zip"

S = "${WORKDIR}"

addtask deploy before do_build after do_install

DESCRIPTION = "Linux kernel for ${MACHINE}"
SECTION = "kernel"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

COMPATIBLE_MACHINE = "^(gbtrio4k)$"

KERNEL_RELEASE = "4.4.35"
SRCDATE = "20181224"

inherit kernel machine_kernel_pr

MACHINE_KERNEL_PR_append = ".7"

SRC_URI[md5sum] = "ad7eab17a5071a0d5f9ff44eb44e027d"
SRC_URI[sha256sum] = "0654d5aa21c51eaea46f7203014afe60052ec0990a92b9e289e1ca8a2793907c"


# By default, kernel.bbclass modifies package names to allow multiple kernels
# to be installed in parallel. We revert this change and rprovide the versioned
# package names instead, to allow only one kernel to be installed.
PKG_${KERNEL_PACKAGE_NAME}-base = "kernel-base"
PKG_${KERNEL_PACKAGE_NAME}-image = "kernel-image"
RPROVIDES_${KERNEL_PACKAGE_NAME}-base = "kernel-${KERNEL_VERSION}"
RPROVIDES_${KERNEL_PACKAGE_NAME}-image = "kernel-image-${KERNEL_VERSION}"

SRC_URI += "http://source.mynonpublic.com/gigablue/mv200/gigablue-linux-${PV}-${SRCDATE}.tar.gz \
    file://defconfig \
    file://0001-remote.patch \
    file://HauppaugeWinTV-dualHD.patch \
    file://dib7000-linux_4.4.179.patch \
    file://dvb-usb-linux_4.4.179.patch \
    file://initramfs-subdirboot.cpio.gz;unpack=0 \
    file://findkerneldevice.py \
    file://0002-log2-give-up-on-gcc-constant-optimizations.patch \
    file://0003-dont-mark-register-as-const.patch \
    file://wifi-linux_4.4.183.patch \
    file://fix-dvbcore-buffer-read.patch \
    file://make-yyloc-declaration-extern.patch \
"

S = "${WORKDIR}/linux-${PV}"
B = "${WORKDIR}/build"

export OS = "Linux"
KERNEL_OBJECT_SUFFIX = "ko"
KERNEL_IMAGEDEST = "tmp"
KERNEL_IMAGETYPE = "uImage"
KERNEL_OUTPUT = "arch/${ARCH}/boot/${KERNEL_IMAGETYPE}"

KERNEL_EXTRA_ARGS = "EXTRA_CFLAGS=-Wno-attribute-alias"

FILES_${KERNEL_PACKAGE_NAME}-image = "/${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} /${KERNEL_IMAGEDEST}/findkerneldevice.py"

kernel_do_configure_prepend() {
	install -d ${B}/usr
	install -m 0644 ${WORKDIR}/initramfs-subdirboot.cpio.gz ${B}/
}
kernel_do_install_append() {
	install -d ${D}/${KERNEL_IMAGEDEST}
	install -m 0755 ${KERNEL_OUTPUT} ${D}/${KERNEL_IMAGEDEST}
	install -m 0755 ${WORKDIR}/findkerneldevice.py ${D}/${KERNEL_IMAGEDEST}
}

pkg_postinst_kernel-image () {
    if [ "x$D" == "x" ]; then
        if [ -f /${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} ] ; then
            python /${KERNEL_IMAGEDEST}/findkerneldevice.py
            dd if=/${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE} of=/dev/kernel
        fi
    fi
    true
}

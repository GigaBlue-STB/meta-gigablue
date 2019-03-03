require conf/machine/include/gigablue-arm.inc

MACHINE_KERNEL_PR = "r7"

MACHINE_EXTRA_RRECOMMENDS = " \
    gst-plugin-dvbmediasink \
    ntfs-3g \
"

PREFERRED_VERSION_linux-gigablue = "4.1.20"
PREFERRED_PROVIDER_virtual/kernel = "linux-gigablue"
PREFERRED_PROVIDER_virtual/egl = "gb-v3ddriver-gb7252"
PREFERRED_PROVIDER_virtual/libgles2 = "gb-v3ddriver-gb7252"

PACKAGECONFIG_GL_pn-qtbase = " gles2 eglfs linuxfb"

IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"

IMAGE_CMD_tar_prepend = "\
    mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}; \
    cp ${DEPLOY_DIR_IMAGE}/${MACHINE}_boot.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/boot.bin; \
    cp ${DEPLOY_DIR_IMAGE}/${MACHINE}_gpt.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/gpt.bin; \
    cp ${DEPLOY_DIR_IMAGE}/${MACHINE}_rescue.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/rescue.bin; \
    cp ${DEPLOY_DIR_IMAGE}/${MACHINE}_bolt_${SRCDATE_BOLT}.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/bolt_${SRCDATE_BOLT}.bin; \
    cp ${DEPLOY_DIR_IMAGE}/zImage ${IMGDEPLOYDIR}/${IMAGEDIR}/kernel.bin; \
    echo ${DISTRO_NAME}-${DISTRO_VERSION}.${BUILD_VERSION} > ${IMGDEPLOYDIR}/${IMAGEDIR}/imageversion; \
    cd ${IMAGE_ROOTFS}; \
    tar -cvf ${IMGDEPLOYDIR}/rootfs.tar -C ${IMAGE_ROOTFS} .; \
    mv ${IMGDEPLOYDIR}/rootfs.tar ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar; \
    bzip2 ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar; \
    cd ${IMGDEPLOYDIR}; \
    zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/*; \
    rm -Rf gigablue; \
"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS = " \
    gigablue-platform-util-gb7252 \
    gigablue-ddbootup \
    gigablue-swapcreate \
"

MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS = " \
    gb-v3ddriver-gb7252 \
    gb-qteglfs-platform \
    "

EXTRA_IMAGEDEPENDS = "\
    gigablue-initrd-cfe-${MACHINE} \
    "

IMAGE_INSTALL_append += "\
    bluetoothsetup-gb7252 \
    "

OPTIONAL_BSP_ENIGMA2_PACKAGES = "\
    enigma2-plugin-extensions-hbbtv-gb \
    enigma2-plugin-extensions-chromium \
    "

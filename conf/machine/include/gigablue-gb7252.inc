require conf/machine/include/gigablue-arm.inc

MACHINE_KERNEL_PR = "r0"

MACHINE_EXTRA_RRECOMMENDS = " \
    gst-plugin-dvbmediasink \
    ntfs-3g \
"

PREFERRED_VERSION_linux-gigablue = "4.1.20"
PREFERRED_PROVIDER_virtual/kernel = "linux-gigablue"

IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"

IMAGE_CMD_tar_prepend = "\
    mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}; \
    cp ${DEPLOY_DIR_IMAGE}/gb7252_boot.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/boot.bin; \
    cp ${DEPLOY_DIR_IMAGE}/gb7252_gpt.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/gpt.bin; \
    cp ${DEPLOY_DIR_IMAGE}/gb7252_rescue.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/rescue.bin; \
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

EXTRA_IMAGEDEPENDS = "\
    gigablue-initrd-cfe-gb7252 \
"

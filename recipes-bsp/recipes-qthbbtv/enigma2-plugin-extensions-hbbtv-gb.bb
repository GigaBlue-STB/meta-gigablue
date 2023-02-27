SUMMARY = "HbbTV for QT browser"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "CLOSED"
PACKAGE_ARCH := "${MACHINE_ARCH}"

SRCDATE = "20181019_r1"

PR = "r1"

inherit gitpkgv

SRC_URI = "http://source.mynonpublic.com/gigablue/hbbtv/gb-hbbtv-qt-${SRCDATE}.zip"

SRC_URI[md5sum] = "fb71d97af77211e46e5dbfcf0ae2e61d"
SRC_URI[sha256sum] = "8ce7d977174d5c317211e3a42c911c3cc06a20a3a585fb695183b074d5e90071"

SRC_URI += " \
    file://dumpait \
    "

RDEPENDS_${PN}  = "qtwebkit virtual/libgles2"
RDEPENDS_${PN} += "gb-v3ddriver-gb7252"

S = "${WORKDIR}"

PLUGINPATH = "${libdir}/enigma2/python/Plugins/Extensions/HbbTV"

FILES_${PN} = "${bindir} ${libdir}/mozilla/plugins/libhbbtvbrowserplugin.so ${PLUGINPATH}/*.py ${PLUGINPATH}/dumpait"
FILES_${PN}-src = "${PLUGINPATH}/*.py"

do_install(){
    install -d ${D}${PLUGINPATH}
    install -m 0755 ${S}/plugin/*.py ${D}${PLUGINPATH}
    install -m 0755 ${S}/dumpait ${D}${PLUGINPATH}
    install -d ${D}${bindir}
    install -m 0755 ${S}/gb_qthbbtv ${D}${bindir}
    install -m 0755 ${S}/run_hbbtv.sh ${D}${bindir}
    install -d ${D}${libdir}/mozilla/plugins
    install -m 0755 ${S}/libhbbtvbrowserplugin.so ${D}${libdir}/mozilla/plugins
}

# Just a quick hack to "compile" the python parts.
do_install_append() {
    python3 -O -m compileall ${D}
}

pkg_postinst_ontarget_${PN}(){
#!/bin/sh
ln -sf /usr/share/fonts /usr/lib/fonts

# remove old PLUGINPATH
# vbcfg.py requires PLUGINROOT = "/usr/lib/enigma2/python/Plugins/Extensions/HbbTV"
if [ -d ${libdir}/enigma2/python/Plugins/Extensions/Hbbtv ]; then
  rm -rf ${libdir}/enigma2/python/Plugins/Extensions/Hbbtv
fi

exit 0
}

INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

INSANE_SKIP_${PN} += "already-stripped file-rdeps ldflags"

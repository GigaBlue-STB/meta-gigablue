#!/bin/sh

runlevel=runlevel | cut -d' ' -f2

if [ "$runlevel" != "0" ] ; then
	exit 0
fi

mount -t sysfs sys /sys
mount -t proc proc /proc

/usr/bin/hihalt

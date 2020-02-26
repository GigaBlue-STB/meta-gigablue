#!/usr/bin/python

import os

try:
	STARTUP = open('/boot/STARTUP', 'r').readline().split(' ')
	STARTUP = STARTUP[1].split('.')
	kerneldevice = STARTUP[1]
	if kerneldevice == "kernel":
		kerneldevice = 'mmcblk0p12'
	#print kerneldevice
	os.symlink("/dev/" + kerneldevice, '/dev/kernel')
except:
	pass

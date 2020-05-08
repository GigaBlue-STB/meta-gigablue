import os

try:
	cmdline = open('/proc/cmdline', 'r').readline()
	kernel_device = cmdline.rsplit('kernel=', 1)[1].split(' ', 1)[0]
	if os.path.exists(kernel_device):
		#print kernel_device
		os.symlink(kernel_device, '/dev/kernel')
except:
	pass

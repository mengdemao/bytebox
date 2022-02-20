# 构建archlinux
ARCHLINUX_ROOTFS_SITE=http://mirrors.163.com
ARCHLINUX_ROOTFS_SIZE=32768
ARCHLINUX_ROOTFS_FILE=ArchLinuxARM-armv7-latest.tar.gz
ARCHLINUX_ROOTFS_EXT4=ArchLinux.ext4

build_rootfs_archlinux()
{
	# 下载系统文件
	if [ ! -f ${ARCHLINUX_ROOTFS_FILE} ];
	then
		axel ${ARCHLINUX_ROOTFS_SITE}/archlinuxarm/os/${ARCHLINUX_ROOTFS_FILE}
	fi

	# 创建镜像文件
	if [ ! -f ${ARCHLINUX_ROOTFS_EXT4} ];
	then
		fakeroot dd if=/dev/zero of=${ARCHLINUX_ROOTFS_EXT4} bs=1M count=${ARCHLINUX_ROOTFS_SIZE}
		fakeroot mkfs.ext4 ${ARCHLINUX_ROOTFS_EXT4}
	fi

	# 挂载rootfs
	if [ ! -d Archlinux ];
	then
		mkdir Archlinux
		fakeroot bsdtar -xpf ${ARCHLINUX_ROOTFS_FILE} -C Archlinux
	fi
	rm -rf ArchLinux
}

# 构建debian
ROOTFS_SITE=http://mirrors.163.com
ROOTFS_SIZE=32768
ROOTFS_FILE=ArchLinuxARM-armv7-latest.tar.gz
ROOTFS_EXT4=ArchLinux.ext4

build_rootfs_debian()
{
	# 下载系统文件
	if [ ! -f ${ROOTFS_FILE} ];
	then
		axel ${ROOTFS_SITE}/archlinuxarm/os/${ROOTFS_FILE}
	fi

	# 创建镜像文件
	if [ ! -f ${ROOTFS_EXT4} ];
	then
		fakeroot dd if=/dev/zero of=${ROOTFS_EXT4} bs=1M count=${ROOTFS_SIZE}
		fakeroot mkfs.ext4 ${ROOTFS_EXT4}
	fi

	# 挂载rootfs
	if [ ! -d Archlinux ];
	then
		mkdir Archlinux
		fakeroot bsdtar -xpf ${ROOTFS_FILE} -C Archlinux
	fi
	rm -rf ArchLinux
}

# 构建ubuntu
UBUNTU_ROOTFS_SITE=http://cdimage.ubuntu.com/
UBUNTU_ROOTFS_SIZE=8192
UBUNTU_ROOTFS_FILE=ubuntu-base-16.04.6-base-armhf.tar.gz
UBUNTU_ROOTFS_EXT4=ubuntu.ext4

build_rootfs_ubuntu()
{
	# 下载系统文件
	if [ ! -f ${UBUNTU_ROOTFS_FILE} ];
	then
		axel ${UBUNTU_ROOTFS_SITE}/ubuntu-base/releases/16.04/release/${UBUNTU_ROOTFS_FILE}
	fi

	# 创建镜像文件
	if [ ! -f ${UBUNTU_ROOTFS_EXT4} ];
	then
		fakeroot dd if=/dev/zero of=${UBUNTU_ROOTFS_EXT4} bs=1M count=${UBUNTU_ROOTFS_SIZE}
		fakeroot mkfs.ext4 ${UBUNTU_ROOTFS_EXT4}
	fi

	# 挂载rootfs
	if [ ! -d ubuntu ];
	then
		mkdir ubuntu
		fakeroot bsdtar -xpf ${UBUNTU_ROOTFS_FILE} -C ubuntu
	fi
	cp -a /usr/bin/qemu-arm-static ubuntu

	# rm -rf ubuntu
}

# 构建buildroot
build_rootfs_buildroot()
{
	pushd ${rootfs}/buildroot/ >> /dev/null
	make arm_vexpress_defconfig
	make
	make sdk
	popd >> /dev/null
}

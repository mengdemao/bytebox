#!/bin/bash

set -u
set -e

source script/setenv.sh

source script/virt.sh

source script/build_kernel.sh

source script/build_rootfs.sh

case $1 in
	opengrok)
		docker run -d -v $(pwd)/../kernel:/opengrok/src -p 8080:8080 opengrok/docker:latest
		;;
	kernel)
		build_kernel
		;;

	debian)
		build_debian
		;;

	debian_config)
		build_config_debian
		;;

	alientek)
		build_alientek
		;;

	debian_alientek)
		build_config_alientek
		;;

	debian_rootfs)
		build_rootfs_debian
		;;

	archlinux_rootfs)
		build_rootfs_archlinux
		;;

	debian_rootfs)
		build_rootfs_debian
		;;

	ubuntu_rootfs)
		build_rootfs_ubuntu
		;;

	buildroot_rootfs)
		build_rootfs_buildroot
		;;

	module)
		build_module
		;;

	# 运行
	debug)
		debug
		;;

	run)
		run
		;;

	# 全部执行
	all)
		build_debian
		build_module
		build_rootfs_buildroot
		;;
esac

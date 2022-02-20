#!/bin/bash

set +u

export PROJECT_ROOT=$(git rev-parse --show-toplevel)
export JOBS=$(nproc)

export kernel=${PROJECT_ROOT}/kernel
export rootfs=${PROJECT_ROOT}/rootfs
export module=${PROJECT_ROOT}/kmodule

export INSTALL_PATH=${rootfs}/boot/
export INSTALL_MOD_PATH=${rootfs}/
export INSTALL_HDR_PATH=${rootfs}/usr/

if [ ! $ARCH ]; then
	ARCH=arm
	export ARCH
	echo "set default arch"
fi

if [ ! $CROSS_COMPILE ]; then
	if [ $ARCH = arm ]; then
		echo "Arch is arm32"
		CROSS_COMPILE=arm-none-linux-gnueabihf-
	elif [ $ARCH = arm64 ]; then
		echo "Arch is arm64"
		CROSS_COMPILE=aarch64-none-linux-gnu-
	else
		echo "CROSS_COMPILE is not set"
	fi
	export CROSS_COMPILE
fi

# 设置默认的kernel位置
if [ ! ${BR_KERNEL} ]; then
	BR_KERNEL=$kernel
	export BR_KERNEL
fi

# 设置默认的kernel版本号
if [ ! ${BR_KERNEL_VERSION} ]; then
	BR_KERNEL_VERSION=master
	export BR_KERNEL_VERSION
fi

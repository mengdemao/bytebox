build_module()
{
	echo "build kernel"

	pushd ${module} >> /dev/null
	make kversion
	make
	popd >> /dev/null
}

build_kernel()
{
	echo "build kernel"
	pushd ${kernel} >> /dev/null
	make -j${JOBS}
	popd >> /dev/null
}

build_debian()
{
	echo "build kernel"
	pushd ${kernel} >> /dev/null
	make distclean
	make debian_defconfig
	make all -j${JOBS}
	popd >> /dev/null
}

build_config_debian()
{
	echo "build kernel"
	pushd ${kernel} >> /dev/null
	make distclean
	make debian_defconfig
	make menuconfig
	make all -j${JOBS}
	popd >> /dev/null
}

build_alientek()
{
	echo "build kernel"
	pushd ${kernel} >> /dev/null
	make distclean
	make alientek_defconfig
	make menuconfig
	make -j${JOBS}
	popd >> /dev/null
}

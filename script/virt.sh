run()
{
	echo "prepare run"
	qemu-system-arm -m 1024 -M virt\
					-nographic -smp 4 -kernel ${kernel}/arch/arm/boot/zImage \
					-append "crashkernel=128M root=/dev/vda rootfstype=ext4 rw"\
					-drive if=none,file=${rootfs}/buildroot/output/images/rootfs.ext4,id=hd0 \
					-device virtio-blk-device,drive=hd0 \
					-netdev user,id=mynet\
					-device virtio-net-device,netdev=mynet\
					--fsdev local,id=kmod_dev,path=./kmodule,security_model=none\
					-device virtio-9p-device,fsdev=kmod_dev,mount_tag=kmod_mount
}

debug()
{
	echo "prepare debug"
	qemu-system-arm -m 1024 -M virt\
					-nographic -smp 4 -kernel ${kernel}/arch/arm/boot/zImage \
					-append "crashkernel=128M root=/dev/vda rootfstype=ext4 rw"\
					-drive if=none,file=${rootfs}/buildroot/output/images/rootfs.ext4,id=hd0 \
					-device virtio-blk-device,drive=hd0 \
					-netdev user,id=mynet\
					-device virtio-net-device,netdev=mynet\
					--fsdev local,id=kmod_dev,path=./kmodule,security_model=none\
					-device virtio-9p-device,fsdev=kmod_dev,mount_tag=kmod_mount\
					-S -s
}

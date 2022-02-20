#!/bin/bash

# 这里可以修改设置
# USER=user
# HOST=pass

# 创建用户
useradd -G sudo -m -s /bin/bash $USER
passwd $USER
# 输入密码

# 设置主机名和以太网
echo $HOST > /etc/hostname
echo "127.0.0.1    localhost.localdomain localhost" > /etc/hosts
echo "127.0.0.1    $HOST" >> /etc/hosts
echo "auto eth0" > /etc/network/interfaces.d/eth0
echo "iface eth0 inet dhcp" >> /etc/network/interfaces.d/eth0
echo "nameserver 127.0.1.1" > /etc/resolv.conf

# 使能串口
ln -s /lib/systemd/system/serial-getty\@.service /etc/systemd/system/getty.target.wants/serial-getty@ttyS0.service

# 安装包
apt-get update
apt-get upgrade
apt-get install ifupdown net-tools network-manager
apt-get install udev sudo ssh

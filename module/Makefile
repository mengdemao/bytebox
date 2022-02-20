#
# kernel module 编译脚本
#

# 如果kernel环境没有设置,那么则使用主机系统的kernel文件
kernel ?= /lib/modules/$(shell uname -r)/build

REVISION_GIT = $(shell git show -s --pretty=format:%h)
REVISION_TAG = $(shell git tag -l | tail -1)

COMPILE_USER = $(shell whoami)
COMPILE_HOST = $(shell hostname)

COMPILE_DATE = $(shell date +"%y-%m-%d")
COMPILE_TIME = $(shell date +"%H:%M:%S")

.PHONY: kversion clean all

all: modules kversion

modules:kversion
	make -C ${kernel} M=$(shell pwd) modules

kversion:
	$(shell if [ -f kversion.h ]; then rm kversion.h; fi)
	$(shell cp include/kversion.h.in include/kversion.h)
	$(shell sed -i "s/%REVISION_GIT%/$(REVISION_GIT)/g" include/kversion.h)
	$(shell sed -i "s/%REVISION_TAG%/$(REVISION_TAG)/g" include/kversion.h)
	$(shell sed -i "s/%COMPILE_USER%/$(COMPILE_USER)/g" include/kversion.h)
	$(shell sed -i "s/%COMPILE_HOST%/$(COMPILE_HOST)/g" include/kversion.h)
	$(shell sed -i "s/%COMPILE_DATE%/$(COMPILE_DATE)/g" include/kversion.h)
	$(shell sed -i "s/%COMPILE_TIME%/$(COMPILE_TIME)/g" include/kversion.h)

clean:
	@ make -C ${kernel} M=$(shell pwd) clean
	@ rm -rf include/kversion.h

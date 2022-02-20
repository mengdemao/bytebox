FROM ubuntu:20.10

RUN apt update -y &&					\
	apt upgrade -y &&					\
	apt install -y						\
	gcc									\
	gcc-arm-linux-gnueabi				\
	gcc-arm-linux-gnueabihf				\
	gcc-arm-none-eabi					\
	qemu								\
	clang								\
	llvm								\
	grep								\
	sed									\
	gawk								\
	u-boot-tools						\
	autoconf							\
	automake							\
	bison								\
	bzip2								\
	flex								\
	git									\
	gperf								\
	make								\
	python								\
	texinfo								\
	unrar								\
	unzip								\
	wget								\
	sudo								\
	cmake								\
	scons								\
	doxygen								\
	tar									\
	sudo								\
	python3-pip							\
	help2man							\
	lzip								\
	axel								\
	rsync

USER root
RUN useradd -m -s /bin/bash bytebox &&\
	passwd -d bytebox &&\
	echo "bytebox      ALL = NOPASSWD: ALL" >> /etc/sudoers &&\
	mkdir -p /compiler && chown -R bytebox:bytebox /compiler &&\
	mkdir -p /bytebox  && chown -R bytebox:bytebox /bytebox

VOLUME /playground

COPY ./entrypoint.sh ./entrypoint.sh
USER root
RUN ["chmod", "+x", "./entrypoint.sh"]
USER bytebox

ENTRYPOINT ["./entrypoint.sh"]

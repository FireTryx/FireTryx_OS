FROM randomdude/gcc-cross-i686-elf

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install nasm xorriso nano curl figlet grub-pc-bin grub-common neofetch -y

VOLUME /root/env
WORKDIR /root/env
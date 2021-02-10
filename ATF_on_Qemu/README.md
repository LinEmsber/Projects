# Run ARM Trusted Firmware (ATF) on QEMU

## Environment
- $ uname -a
- > Linux user 4.4.0-189-generic #219-Ubuntu SMP Tue Aug 11 12:26:50 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux

## Prerequisites
### Tool
- Python3.7
  - $ sudo add-apt-repository ppa:deadsnakes/ppa
  - $ sudo apt update
  - $ sudo apt install python3.7
- ninja
  - $ wget https://github.com/ninja-build/ninja/releases/download/v1.8.2/ninja-linux.zip
  - $ sudo unzip ninja-linux.zip -d /usr/local/bin/
  - $ sudo update-alternatives --install /usr/bin/ninja ninja /usr/local/bin/ninja 1 --force
- glibc2.0
  - $ sudo apt-get install libglib2.0-dev
- meson
  - $ sudo apt-get install python3 python3-pip python3-setuptools python3-wheel ninja-build
  - $ pip3 install --user meson
- libpixman
  - $ sudo apt-get install libpixman-1-dev
- AARCH64 toolchain
  - $ wget https://developer.arm.com/-/media/Files/downloads/gnu-a/10.2-2020.11/binrel/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu.tar.xz

## open-source project
- QEMU
  - $ git clone git://git.qemu.org/qemu.git
  - $ cd ./qemu
  - $ ./configure --target-list=aarch64-softmmu --python="/usr/bin/python3.7"
  - $ make -j 4
- ROOTFS
  - $ git clone git://git.buildroot.net/buildroot
  - $ cd buildroot
  - $ export ARCH=arm64
  - $ export CROSS_COMPILE="/home/jl/ATF_on_QEMU/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-"
  - $ make qemu_aarch64_virt_defconfig
  - $ ./utils/config -e BR2_TARGET_ROOTFS_CPIO
  - $ ./utils/config -e BR2_TARGET_ROOTFS_CPIO_GZIP
  - $ make olddefconfig
  - $ make
- Linux
  - $ git cloen https://github.com/torvalds/linux.git
- Arm trusted firmware
  - $ git clone https://github.com/ARM-software/arm-trusted-firmware.git

## Reference
- Python3.7
  - Reference: https://phoenixnap.com/kb/how-to-install-python-3-ubuntu
- ninja
  - Reference: https://www.claudiokuenzler.com/blog/756/install-newer-ninja-build-tools-ubuntu-14.04-trusty
- meson
  - Reference: https://mesonbuild.com/Quick-guide.html
- libpixman
  - Reference: https://superuser.com/questions/618695/pkg-config-path-cairo-pc-cannot-find-pixman
- AARCH64 toolchain
  - Reference: https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads

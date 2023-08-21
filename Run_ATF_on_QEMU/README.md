# ARM trusted firmware (ATF) on QEMU

## Environment
- $ uname -a
- > Linux user 4.4.0-189-generic #219-Ubuntu SMP Tue Aug 11 12:26:50 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux

## Rrerequisites
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
  - $ make install
  - $ make -j 4
    - Fix compilation error: Modify line from block/nvme.c: 3150, give the variable, result, a initialization value
```c
    uint32_t result = 0;
```
  - $ ls ./build/aarch64-softmmu/qemu-system-aarch64
  - > ./build/aarch64-softmmu/qemu-system-aarch64
- ROOTFS
  - $ git clone git://git.buildroot.net/buildroot
  - $ cd buildroot
  - $ export ARCH=aarch64
  - $ export CROSS_COMPILE="$<gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu>/bin/aarch64-none-linux-gnu-"
  - $ make qemu_aarch64_virt_defconfig
  - $ ./utils/config -e BR2_TARGET_ROOTFS_CPIO
  - $ ./utils/config -e BR2_TARGET_ROOTFS_CPIO_GZIP
  - $ make olddefconfig
  - $ make
  - $ ls ./output/images/rootfs.cpio.gz
  - > ./output/images/rootfs.cpio.gz
- Linux
  - $ git clone https://github.com/torvalds/linux.git
  - $ ARCH=arm64 CROSS_COMPILE="$<gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu>/bin/aarch64-none-linux-gnu-" make defconfig
  - $ ARCH=arm64 CROSS_COMPILE="$<gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu>/bin/aarch64-none-linux-gnu-" make -j4
  - $ ls ./arch/arm64/boot/Image
  - > ./arch/arm64/boot/Image
- Arm trusted firmware
  - $ git clone https://github.com/ARM-software/arm-trusted-firmware.git
  - $ make CROSS_COMPILE="$<gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu>/bin/aarch64-none-linux-gnu-" PLAT=qemu DEBUG=1
  - $ ls ./build/qemu/debug
  - > bl1  bl1.bin  bl2  bl2.bin  bl31  bl31.bin  lib  libc  libfdt  libwrapper  romlib
- UEFI
  - wget http://snapshots.linaro.org/components/kernel/leg-virt-tianocore-edk2-upstream/latest/QEMU-KERNEL-AARCH64/RELEASE_GCC5/QEMU_EFI.fd
  - mv ./QEMU_EFI.fd arm-trusted-firmware/build/qemu/debug/bl3.bin

## Run ATF on QEMU (cont.)
- $ cd qemu//build/aarch64-softmmu/
- $ ln -ds ../../../arm-trusted-firmware/build/qemu/release/bl1.bin ./bl1.bin
- $ ln -ds ../../../arm-trusted-firmware/build/qemu/release/bl2.bin ./bl2.bin
- $ ln -ds ../../../arm-trusted-firmware/build/qemu/release/bl31.bin ./bl31.bin
- $ ln -ds ../../../arm-trusted-firmware/build/qemu/release/QEMU_EFI.fd ./bl33.bin
- $ ln -ds ../../../linux/arch/arm64/boot/Image ./Image
- $ ln -ds ../../../buildroot/output/images/rootfs.cpio.gz ./rootfs.cpio.gz
- $ ./qemu-system-aarch64 -machine virt -cpu cortex-a57 -nographic -smp 2 -m 2048 -initrd rootfs.cpio.gz -kernel Image -append "console=ttyAMA0 earlycon root=" -d unimp -semihosting-config enable=on,target=native

## Run Linux on QEMU with GDB
### In the 1st terminal
- $ cd qemu//build/aarch64-softmmu/
- $ ./qemu-system-aarch64 -s -S -machine virt -cpu cortex-a57 -nographic -smp 2 -m 2048 -initrd rootfs.cpio.gz -kernel Image -append "console=ttyAMA0 earlycon root=" -d unimp -semihosting-config enable=on,target=native
### In the 2nd terminal
- $ cd qemu//build/aarch64-softmmu/
- $ <gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu>/bin/aarch64-none-linux-gnu-gdb ./Image

## Reference
- Python3.7
  - https://phoenixnap.com/kb/how-to-install-python-3-ubuntu
- ninja
  - https://www.claudiokuenzler.com/blog/756/install-newer-ninja-build-tools-ubuntu-14.04-trusty
- meson
  - https://mesonbuild.com/Quick-guide.html
- libpixman
  - https://superuser.com/questions/618695/pkg-config-path-cairo-pc-cannot-find-pixman
- AARCH64 toolchain
  - https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads
- QEMU virt Armv8-A
  - https://github.com/ARM-software/arm-trusted-firmware/blob/master/docs/plat/qemu.rst

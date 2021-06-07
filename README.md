# SHORE
SHORE: RISC-V Memory Safety in C

This is the repository for the accelerating pointer-based memory safety enforcement on RISC-V.
Please refer to the DAC 2021 paper (link: ...) for detail of the implementation

Quick start:

The project is using the RISC-V LLVM compiler to instrument memory safety operations into programs.
The first step is to build the llvm compiler with clang front-end for C

```
sudo apt-get -y install \
  binutils build-essential libtool texinfo \
  gzip zip unzip patchutils curl git \
  make cmake ninja-build automake bison flex gperf \
  grep sed gawk python bc \
  zlib1g-dev libexpat1-dev libmpc-dev \
  libglib2.0-dev libfdt-dev libpixman-1-dev 


git clone --recursive https://github.com/Lycheus/SHORE.git

cd SHORE
mkdir _install
export PATH=`pwd`/_install/bin:$PATH
hash -r

# gcc, binutils, newlib
git clone --recursive https://github.com/riscv/riscv-gnu-toolchain
pushd riscv-gnu-toolchain
./configure --prefix=`pwd`/../_install --enable-multilib
make -j`nproc`


```

# SHORE: RISC-V Memory Safety for C/C++

This is the repository for the accelerating pointer-based memory safety enforcement on RISC-V.
Please refer to the DAC 2021 paper (link: ...) for detail of the implementation.

## Quickstart:

The project is using the RISC-V LLVM compiler to instrument memory safety operations into programs.
The tools include: 
  1) **GNU linux toolchain** for libraries; 
  2) **LLVM compiler (clang)** with SHORE instrumentation;
  3) **RISC-V ISA simulator (SPIKE)** with SHORE ISA extention;
  4) **Proxy kernel (PK)** with shadow space allocation

The following script is supported and verified on Ubuntu 20.04 LTS.

First, we shall keep the tool server updated.

```
sudo apt-get update
sudo apt-get -y dist-upgrade

sudo apt-get -y install \
  binutils build-essential libtool texinfo \
  gzip zip unzip patchutils curl git \
  make cmake ninja-build automake bison flex gperf \
  grep sed gawk python bc \
  zlib1g-dev libexpat1-dev libmpc-dev \
  libglib2.0-dev libfdt-dev libpixman-1-dev 
```

Clone the SHORE github
```
git clone --recursive https://github.com/Lycheus/SHORE.git
```

Next is to build the tools (it is a very lengthy process, prepare your coffee and cookie =))
```
cd SHORE
mkdir _install
export PATH=`pwd`/_install/bin:$PATH
export RISCV=`pwd`/_install/
hash -r

# gcc, binutils, newlib
pushd riscv-gnu-toolchain
./configure --prefix=`pwd`/../_install --with-cmodel=medany --enable-multilib
make linux -j`nproc`
popd

#LLVM
pushd shore-llvm
mkdir _build
cd _build
cmake -G Ninja -DCMAKE_BUILD_TYPE="Release" \
  -DBUILD_SHARED_LIBS=True -DLLVM_USE_SPLIT_DWARF=True \
  -DCMAKE_INSTALL_PREFIX="../../_install" \
  -DLLVM_OPTIMIZED_TABLEGEN=True -DLLVM_BUILD_TESTS=False \
  -DDEFAULT_SYSROOT="../../_install/sysroot" \
  -DLLVM_DEFAULT_TARGET_TRIPLE="riscv64-unknown-gnu-linux" \
  -DLLVM_TARGETS_TO_BUILD="" -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD="RISCV" \
  -DCLANG_DEFAULT_LINKER="$RISCV/bin/riscv64-unknown-linux-gnu-gcc" \
  ../llvm
cmake --build . --target install

#build SBCETS runtime
cd ../runtime
make
popd

# build spike (RISC-V ISA simulator)
pushd shore-isa-sim
mkdir build
cd build
../configure --prefix=$RISCV --with-fesvr=$RISCV --enable-histogram
make -j$(nproc)
make install
popd

#build pk (proxy kernel)
pushd shore-pk
mkdir build
cd build
../configure --prefix=$RISCV --host=riscv64-unknown-linux-gnu
make
make install
popd
```

Finally, we can test some program

```
# Sanity test your new RISC-V LLVM
cat >hello.c <<END
#include <stdio.h>

int main(){
  printf("Hello RISCV!\n");
  return 0;
}
END

clang -fsoftboundcets -c hello.c
#riscv64-unknown-linux-gnu-gcc hello.o -o hello -L $RISCV/../shore-llvm/runtime -lsoftboundcets_rt -lrt -lm -static -march=rv64imac -mabi=lp64 
riscv64-unknown-linux-gnu-gcc hello.o -o hello -L ~/riscv/riscv-llvm/runtime -lsoftboundcets_rt -lm -static -march=rv64gc -mabi=lp64
spike pk hello
```

## Tips & Tricks
### For shore-pk:
You might need to change the makefile install directory to _install/bin instead gnu

Be careful the default installation directory of pk is "unknown-linux-gnu" instead "_install", what make it worse is that the default pk used by spike is targeting "unknown-elf" directory instead "_install".
You can use absolute path for pk to solve this problem. 
```
e.g. "spike pk binaries" -> "spike ~/<shore>/_install/pk binaries"
```


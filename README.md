# Welcome to dpdk-samples!


# System Config

There are some steps to prepare system for building dpdk:

- In the ubuntu:
	> sudo apt install libpcap-dev
	>
	> sudo apt install libelf-dev
	>
	> sudo apt install libnuma-dev
	>
	> sudo apt install python3-pip
	>
	> sudo python3 -m pip install meson
	>
	> sudo python3 -m pip install ninja
	>
	> sudo python3 -m pip install pyelftools

# Build Dpdk

In this part, we survay how can download and build dpdk.

- Download last lts version:
  
	> wget https://fast.dpdk.org/rel/dpdk-23.11.tar.xz
	>
	> tar xf dpdk-23.11.tar.xz 

- Build and Install:
  
	> cd dpdk-23.11
	>
	> meson -Dexamples=all build
	>
	> cd build
	>
	> ninja -C build

- Compiler and Linker Flags:
	- This command sets the PKG_CONFIG_PATH environment variable to include the directory /usr/local/lib64/pkgconfig/. This is necessary because pkg-config uses this variable to find .pc files, which contain the necessary information for compiling and linking against a library.

		> export PKG_CONFIG_PATH=/usr/local/lib64/pkgconfig/
	
	- This command uses pkg-config to output the compiler flags that are necessary for compiling a program that uses the DPDK library. If you're using gcc to compile your program, you might use a command like gcc $(pkg-config --cflags libdpdk) -o myprogram myprogram.c.

		> pkg-config --cflags libdpdk

	- This command uses pkg-config to output the linker flags that are necessary for linking a program that uses the DPDK library. If you're using gcc to link your program, you might use a command like gcc -o myprogram myprogram.c $(pkg-config --libs libdpdk).

		> pkg-config --libs libdpdk

	- It specifically requests the linker flags for linking the DPDK library statically. 

		> pkg-config --static --libs libdpdk

		- First, compile your source files into object files:
			> gcc $(pkg-config --cflags libdpdk) -c myprogram.c -o myprogram.o

		- Next, link your object files into an executable:
			> gcc -o myprogram myprogram.o $(pkg-config --static --libs libdpdk)


# Config Network

In this part, we config NIC for dpdk:

- First of all, we install a NIC driver that is compatible with dpdk:
	
	> sudo add-apt-repository universe
	>
	> sudo apt update
	>
	> sudo apt install dpdk-kmods-dkms
	>
	> sudo modprobe igb_uio
	>
	> lsmod | grep igb_uio

- After that, we load another compatible driver:

	> sudo modprobe uio_pci_generic
	>
	> lsmod | grep uio_pci_generic

- For load vfio-pci driver we should run below steps:

	>  echo 1 > /sys/module/vfio/parameters/enable_unsafe_noiommu_mode 2
	>
	> sudo modprobe vfio-pci
	>

- Now, it's time to assign driver to NIC:

	> ip a
	>
	> sudo ip link set ens33 down
	>
	> dpdk-devbind.py -s
	>
	> sudo dpdk-devbind.py -u 0000:02:01.0
	>
	> sudo dpdk-devbind.py -b igb_uio 0000:02:01.0
	>

- If we want to return back NIC setting, we should apply below steps:

	> sudo dpdk-devbind.py -u 0000:02:01.0
	>
	> sudo dpdk-devbind.py -b e1000 0000:02:01.0


- In the last step, we set hugepage:

	> sudo bash -c 'echo 512 > /sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages'
	>
	> dpdk-hugepages.py -s


# Launch IDE

- Open vscode as sudo:
  
	> sudo code --no-sandbox --user-data-dir="~/.vscode-root"

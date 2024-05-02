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
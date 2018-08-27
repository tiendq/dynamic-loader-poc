Dynamic Loader POC
==================

A C++ POC for dynamically loading app modules (plugins), cross-platform.

## Features
* Build with CMake, support Windows/Linux/macOS
* Dynamically load modules
* Support Windows/Linux/macOS (loading modules)

## Prerequisites
* [CMake](http://www.cmake.org/), check your CMake version in terminal by `cmake -version`

## Build
Configure the project build with the following command to create the build directory with the configuration.

```
mkdir build; cd build  # Create a build directory.
cmake ..               # Configure the project.
cmake --build .        # Build all default targets.
```

If you don't want `cd` :), you can also use below command to create `build` folder from project folder:

```
cmake -H. -Bbuild
# H indicates source directory
# B indicates build directory
```

## Test Linux

### Create Docker Container
Create a container based on [ArchLinux](https://www.archlinux.org/) by running `docker run --name dynamic-loader-poc -w /var/dynamic-loader-poc -v ``pwd``:/var/dynamic-loader-poc -it base/archlinux bash` from `dynamic-loader-poc` on host machine.

Start container with `docker start dynamic-loader-poc` and use the command `docker exec -it dynamic-loader-poc bash` to get a bash shell in the container.

### Install Tools
```
pacman -Sy
pacman -S gcc
pacman -S make
pacman -S cmake
```

Build from `/var/dynamic-loader-poc`.

Tien Do (tiendq).

Dynamic Loader POC
==================

POC for dynamically loading app modules.

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

Tien Do (tiendq).
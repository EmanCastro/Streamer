#! /bin/bash

case "$1" in
    "-h" | "--help")
        echo "Usage: ./script.sh [OPTIONS]"
        echo "Options:"
        echo "  -h, --help       Display this help message"
        # Add more options if needed
        exit 0
        ;;
    "-n" | "--new")
        echo "New build selected"
        rm -rf build
        mkdir build
        cd build
        cmake ..
        make
        ;;
    "-g" | "--gdb")
        echo "Building with debugging symbols"
        cmake -DCMAKE_BUILD_TYPE=Debug build
        make
        ;;
    "-c" | "--cross")
        echo "Cross build selected"
        ;;
    *)  # Default case
        cd build
        make
        exit 1
        ;;
esac
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
    "-c" | "--cross")
        echo "Cross build selected"
        # Handle option B
        ;;
    *)  # Default case
        echo "Invalid option. Use -h or --help for usage information."
        exit 1
        ;;
esac
#! /usr/bin/bash

# directories
export PJROOT="/home/moka/wp/tree"
export PREFIX="$PJROOT/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

# aliases
alias gcc="$TARGET-gcc"

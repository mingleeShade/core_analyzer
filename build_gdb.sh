#!/usr/bin/env bash

# ==============================================================================================
# FILENAME	:	build_gdb.sh
# AUTHOR	:	Celthi
# CREATION	:	2021-12-14
# Script to build the custom gdb with core analyzer.
# This script will the do the following steps
# 1. Create working directory
# 2. download the gdb 9.2 from gnu.org
# 3. copy the core analyzer code to the gdb
# 4. build the gdb
# ==============================================================================================

set -e
gdb_version="12.1"
if [ "$#" -ne 1 ]
then
    echo "build gdb 12.1"
else
    gdb_version=$1
fi

PROJECT_FOLDER=$(pwd)
echo "Current project folder is $PROJECT_FOLDER"
echo "installing gdb $gdb_version..."
build_folder=$PROJECT_FOLDER/build
mkdir -p $build_folder
cd $build_folder
gdb_to_install="gdb-$gdb_version"
tar_gdb="${gdb_to_install}.tar.gz"
if [ ! -f $tar_gdb ]
then
    wget http://ftp.gnu.org/gnu/gdb/$tar_gdb
fi
if [ ! -d $gdb_to_install ]
then
    tar -xvf $tar_gdb
fi
cp -rLvp $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb $build_folder/gdb-$gdb_version/

cd $gdb_to_install

if [ $gdb_version == "9.2" ]; then
    sed -i '20d' ./gdb/nat/amd64-linux-siginfo.c
    sed -i '21i #include <signal.h>' ./gdb/nat/amd64-linux-siginfo.c
fi

mkdir -p build
cd build

echo "building..."
PWD=$(pwd)
# if you prefer the gdb with debug symbol use commented line to build
# $PWD/../configure -disable-binutils --with-python --disable-ld --disable-gold --disable-gas --disable-sim --disable-gprof CXXFLAGS='-g' CFLAGS='-g' --prefix=/usr

$PWD/../configure --with-python --prefix=/usr
bear -- make -j8
sudo make install # do not remove the build folder && rm -rf $build_folder
echo "if you want to remove the build folder, please run \"rm -rf $build_folder\""

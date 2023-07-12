#!/bin/bash


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
build_folder=$PROJECT_FOLDER/build

if [ ! -d $build_folder ]
then
    # 不存在文件夹的话，也无需做同步
    echo "No need to sync file."
    exit 0
fi

cp -uv $build_folder/gdb-$gdb_version/gdb/Makefile.in $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/decode.c $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/decode.h $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/gdb_dep.c $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/heap.c $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/heap.h $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/heap_jemalloc.c $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/heap_jemalloc.h $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/heap_ptmalloc.h $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/heap_ptmalloc_2_27.c $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/heap_ptmalloc_2_31.c $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/heap_ptmalloc_2_35.c $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/heap_ptmalloc_common.c $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/heap_tcmalloc.c $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/heap_tcmalloc.h $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/heapcmd.c $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/i386-decode.c $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/ref.h $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/regcache.c $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/regcache.h $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/search.c $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/search.h $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/segment.c $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/segment.h $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/x_dep.h $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/x_type.h $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/value.c $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/value.h $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/
cp -uv $build_folder/gdb-$gdb_version/gdb/python/py-heap.c $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/python
cp -uv $build_folder/gdb-$gdb_version/gdb/python/py-ref.c $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/python
cp -uv $build_folder/gdb-$gdb_version/gdb/python/python-internal.h $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/python
cp -uv $build_folder/gdb-$gdb_version/gdb/python/python.c $PROJECT_FOLDER/gdbplus/gdb-$gdb_version/gdb/python

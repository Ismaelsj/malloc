#!/bin/sh
export DYLD_LIBRARY_PATH=/Users/IsMac/Desktop/malloc
export DYLD_INSERT_LIBRARIES=/Users/IsMac/Desktop/malloc/libft_malloc.so
export DYLD_FORCE_FLAT_NAMESPACE=1
$@
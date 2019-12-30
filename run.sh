#!/bin/sh
export DYLD_LIBRARY_PATH=/Users/isidibe-/Documents/malloc
export DYLD_INSERT_LIBRARIES=/Users/isidibe-/Documents/malloc/libft_malloc.so
export DYLD_FORCE_FLAT_NAMESPACE=1
$@
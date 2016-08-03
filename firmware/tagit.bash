#!/bin/bash

PROJECT=./test
# PROJECT=./dev

echo "Project: $PROJECT"

# remove old cscope db
rm -f .cscope.*  cscope.*
# remove old tags
rm -f tags

# create list of files for cscope
find $PROJECT  -name '*.[ch]' > cscope_A.files
find ./drivers -name '*.[ch]' >> cscope_A.files
find ./common  -name '*.[ch]' >> cscope_A.files
find ./CMSIS   -name '*.[ch]' >> cscope_A.files
find /usr/arm-none-eabi/include -name '*.[h]' >> cscope_A.files
./.filter.awk cscope_A.files    > .cscope.files
#mv cscope_A.files cscope.files
rm -f cscope_A.files

echo "Create tags file"
# Run ctags on directory of interest
# add local and all vars to ckinds list
# try ctags --list-kinds=c for different vars tracked.
#  ctags --list-kinds=c 
# c  classes
# d  macro definitions
# e  enumerators (values inside an enumeration)
# f  function definitions
# g  enumeration names
# l  local variables [off]
# m  class, struct, and union members
# n  namespaces
# p  function prototypes [off]
# s  structure names
# t  typedefs
# u  union names
# v  variable definitions
# x  external and forward variable declarations [off]


#ctags --verbose --c-kinds=+cdefglmnpstuvx --tag-relative=no --language-force=C -L cscope.files
ctags --c-kinds=+cdefglmnpstuvx --tag-relative=no --language-force=C -L .cscope.files

echo "Create cscope db"
# run cscope
cscope -R  -b -q -i .cscope.files >& .cscope.log




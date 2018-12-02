#!/bin/bash
set -euo pipefail
IFS=$'\n\t'

max_num=32
prefix="GEN"

printf "// auto-generated from autogen.sh, DO NOT EDIT!\n"
printf "// intended to be used by #define_EVIL (https://github.com/wmww/define_EVIL)\n"
printf "// dealing with close to or more then $max_num things may not work\n\n"

printf "#define GEN_MAX_NUM $max_num\n\n"

printf "// INC_ and DEC_\n"
printf "// usage: cat INC_ or DEC_ to any small number to get n+1 or n-1\n"
for (( i=0; i<$max_num; i++ ))
do
	printf "#define INC_$i $[i + 1]\n"
done
printf "\n"
for (( i=0; i<$max_num; i++ ))
do
	printf "#define DEC_$[i + 1] $i\n"
done
printf "\n"

printf "// enables the usage of EQ on numbers\n"
for (( i=0; i<$max_num; i++ ))
do
	printf "#define ENABLE_EQ_${i}_${i}\n"
done
printf "\n"

printf "// REMOVE_COMMAS\n"
for (( i=0; i<$max_num; i++ ))
do
	printf "#define _${prefix}_REMOVE_COMMAS_$i(a, ...) a _${prefix}_REMOVE_COMMAS_$[i + 1](__VA_ARGS__)\n"
done
printf "#define _${prefix}_REMOVE_COMMAS_$max_num(a, ...) a\n\n"

printf "// COUNT\n"
printf "#define _${prefix}_COUNT_NUMBERS "
for (( i=$max_num; i>=2; i-- ))
do
	printf "$i, "
done
printf "1\n"
printf "#define _${prefix}_COUNT("
for (( i=0; i<$max_num; i++ ))
do
	printf "_$i, "
done
printf "n, ...) n\n\n"

printf "// REPEAT\n"
printf "#define _${prefix}_REPEAT_0(macro, order)\n"
printf "#define _${prefix}_REPEAT_1(macro, order) macro(0)\n"
for (( i=2; i<=$max_num; i++ ))
do
	printf "#define _${prefix}_REPEAT_$i(macro, order) order(_${prefix}_REPEAT_$[i - 1](macro, order), macro($[i - 1]))\n"
done
printf "\n"

printf "// MAP\n"
printf "#define _${prefix}_MAP_0(macro, order, index, dir, empty)\n"
printf "#define _${prefix}_MAP_1(macro, order, index, dir, item) macro(item, index)\n"
for (( i=2; i<=$max_num; i++ ))
do
	printf "#define _${prefix}_MAP_$i(macro, order, index, dir, item, ...) order(macro(item, index), _${prefix}_MAP_$[i - 1](macro, order, EXPAND_CAT(dir, index), dir, __VA_ARGS__))\n"
done
printf "\n"

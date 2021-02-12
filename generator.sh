#!/bin/bash
set -euo pipefail
IFS=$'\n\t'

max_num=32
prefix="EVIL_GEN"

printf "// auto-generated from generator.sh, DO NOT EDIT!\n"
printf "// intended to be used by #define_EVIL (https://github.com/wmww/define_EVIL)\n"
printf "// dealing with close to or more then $max_num things may not work\n\n"

printf "#if not(defined(EVIL)) || defined(_${prefix}_H)\n"
printf "#error this file should only be included by define_EVIL.h\n"
printf "#endif\n"
printf "#define _${prefix}_H\n\n"

printf "#define EVIL_GEN_MAX_NUM $max_num\n\n"

printf "// EVIL_INC_ and EVIL_DEC_\n"
printf "// usage: cat EVIL_INC_ or EVIL_DEC_ to any small number to get n+1 or n-1\n"
for (( i=0; i<$max_num; i++ ))
do
	printf "#define EVIL_INC_$i $[i + 1]\n"
done
printf "\n"
for (( i=0; i<$max_num; i++ ))
do
	printf "#define EVIL_DEC_$[i + 1] $i\n"
done
printf "\n"

printf "// enables the usage of EVIL_EQ on numbers\n"
for (( i=0; i<$max_num; i++ ))
do
	printf "#define EVIL_ENABLE_EQ_${i}_${i}\n"
done
printf "\n"

printf "// EVIL_REMOVE_COMMAS\n"
for (( i=0; i<$max_num; i++ ))
do
	printf "#define _${prefix}_REMOVE_COMMAS_$i(a, ...) a _${prefix}_REMOVE_COMMAS_$[i + 1](__VA_ARGS__)\n"
done
printf "#define _${prefix}_REMOVE_COMMAS_$max_num(a, ...) a\n\n"

printf "// EVIL_COUNT\n"
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

printf "// EVIL_REPEAT\n"
printf "#define _${prefix}_REPEAT_0(macro, order)\n"
printf "#define _${prefix}_REPEAT_1(macro, order) macro(0)\n"
for (( i=2; i<=$max_num; i++ ))
do
	printf "#define _${prefix}_REPEAT_$i(macro, order) order(_${prefix}_REPEAT_$[i - 1](macro, order), macro($[i - 1]))\n"
done
printf "\n"

printf "// EVIL_MAP\n"
printf "#define _${prefix}_MAP_0(macro, order, index, dir, empty)\n"
printf "#define _${prefix}_MAP_1(macro, order, index, dir, item) macro(item, index)\n"
for (( i=2; i<=$max_num; i++ ))
do
	printf "#define _${prefix}_MAP_$i(macro, order, index, dir, item, ...) order(macro(item, index), _${prefix}_MAP_$[i - 1](macro, order, EVIL_EXPAND_CAT(dir, index), dir, __VA_ARGS__))\n"
done
printf "\n"

#!/bin/bash

printf "// auto-generated from autogen.sh, DO NOT EDIT!\n\n"

printf "// INC_ and DEC_\n"
printf "// usage: cat INC_ or DEC_ to any small number to get n+1 or n-1\n"
max_inc=24
for (( i=0; i<$max_inc; i++ ))
do
	printf "#define INC_$i $[i + 1]\n"
done
for (( i=0; i<$max_inc; i++ ))
do
	printf "#define DEC_$[i + 1] $i\n"
done
printf "\n"

printf "// REMOVE_COMMAS\n"
max_commas=24
for (( i=0; i<$max_commas; i++ ))
do
	printf "#define _AG_REMOVE_COMMAS_$i(a, ...) a _AG_REMOVE_COMMAS_$[i + 1](__VA_ARGS__)\n"
done
printf "#define _AG_REMOVE_COMMAS_$max_commas(a, ...) a\n\n"

printf "// COUNT\n"
max_count=24
printf "#define _AG_COUNT_NUMBERS "
for (( i=$max_count; i>=2; i-- ))
do
	printf "$i, "
done
printf "1\n"
printf "#define _AG_COUNT("
for (( i=0; i<$max_count; i++ ))
do
	printf "_$i, "
done
printf "n, ...) n\n\n"

printf "// REPEAT\n"
max_repeat=24
printf "#define _AG_REPEAT_0(macro, joiner, order)\n"
printf "#define _AG_REPEAT_1(macro, joiner, order) macro(0)\n"
for (( i=2; i<=$max_repeat; i++ ))
do
	printf "#define _AG_REPEAT_$i(macro, joiner, order) order(_AG_REPEAT_$[i - 1](macro, joiner, order), joiner, macro($[i - 1]))\n"
done
printf "\n"

printf "// MAP\n"
max_map=24
printf "#define _AG_MAP_0(macro, joiner, order, index, dir, empty)\n"
printf "#define _AG_MAP_1(macro, joiner, order, index, dir, item) macro(item, index)\n"
for (( i=2; i<=$max_map; i++ ))
do
	printf "#define _AG_MAP_$i(macro, joiner, order, index, dir, item, ...) order(macro(item, index), joiner, _AG_MAP_$[i - 1](macro, joiner, order, EXPAND_CAT(dir, index), dir, __VA_ARGS__))\n"
done
printf "\n"

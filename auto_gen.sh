printf "// auto-generated from auto_gen.sh, DO NOT EDIT!\n\n"

printf "// REMOVE_COMMAS\n"
max_commas=24
for i in $(seq 0 $[max_commas - 1])
do
	printf "#define _AG_REMOVE_COMMAS_$i(a, ...) a _AG_REMOVE_COMMAS_$[i + 1](__VA_ARGS__)\n"
done
printf "#define _AG_REMOVE_COMMAS_$max_commas(a, ...) a\n\n"


printf "// COUNT_THINGS\n"
max_count=24
printf "#define _AG_COUNT_THINGS_NUMBERS "
for i in $(seq $max_count -1 2)
do
	printf "$i, "
done
printf "1\n"
printf "#define _AG_COUNT_THINGS("
for i in $(seq 0 $[max_count - 1])
do
	printf "_$i, "
done
printf "n, ...) n\n"
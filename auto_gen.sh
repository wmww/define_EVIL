big=24

echo "// auto-generated from auto_gen.sh, DO NOT EDIT!"
echo

echo "// REMOVE_COMMAS"
for i in $(seq 0 $[big - 1])
do
	echo "#define AG_REMOVE_COMMAS_$i(a, ...) a AG_REMOVE_COMMAS_$[i + 1](__VA_ARGS__)"
done
echo "#define AG_REMOVE_COMMAS_$big(a, ...) a"
echo
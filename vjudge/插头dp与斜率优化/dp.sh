for i in {1..100000}
do
./gen
./C
./std
cat C.out
cat std.out
if diff C.out std.out;then
echo $i AC
else
echo $i WA
exit 0
fi
done

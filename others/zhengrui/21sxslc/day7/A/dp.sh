for i in {1..1000};
do
	rm gen.in
	echo $i >> gen.in
	./gen.exe
	echo Case \#$i
	./std.exe
	./A.exe
	cat A.out
	if diff A.out std.out;then
		echo AC
	else
		echo WA
		exit 0
	fi
done

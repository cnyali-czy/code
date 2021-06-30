for i in {1..10000};
do
	echo Case \#$i
	echo $i>seed.in
	./gen.exe
	./bf.exe
	./A.exe
	cat A.in | md5sum
	if diff bf.out A.out;
		then echo AC
	else
		echo WA
		exit 0
	fi
done

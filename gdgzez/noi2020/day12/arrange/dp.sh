for i in {1..10000};
do
	echo Case \#$i
	./gen.exe
	./bf.exe
	./arrange.exe
	cat bf.out | md5sum
	if diff arrange.out bf.out;then
		echo AC
	else
		echo WA
		exit 0
	fi
done

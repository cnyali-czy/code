for i in {1..100000};
do
	echo Case \#$i
	./gen.exe
	./bf.exe
	./award.exe
	cat bf.out | md5sum
	if diff bf.out award.out;then
		echo AC
	else
		echo WA
		exit 0
	fi
done

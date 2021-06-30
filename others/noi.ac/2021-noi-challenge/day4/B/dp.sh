for i in {10000..100000};
do
	echo Case \#$i
	echo $i>seed.in
	./gen.exe
	./bf.exe
	./B.exe
	cat B.in 
	if diff bf.out B.out;
		then echo AC
	else
		echo WA
		exit 0
	fi
done

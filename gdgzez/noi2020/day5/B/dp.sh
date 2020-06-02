for i in {1..1000000};
do
	echo Case \#$i
	./gen
	./bf
	./B
	cat B.out | md5sum
	if diff B.out bf.out;then
		echo AC
	else
		echo WA
		exit 0
	fi
done

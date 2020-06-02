for i in {1..1000000};
do
	echo Case \#$i
	./gen
	./bf
	./C
	cat C.out | md5sum
	if diff C.out bf.out;then
		echo AC
	else
		echo WA
		exit 0
	fi
done

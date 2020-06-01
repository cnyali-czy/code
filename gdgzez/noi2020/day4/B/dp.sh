for i in {1..1000};
do
	echo Case $i
	./gen
	./bf
	./B
	cat B.out
	if diff B.out bf.out;then
		echo AC
	else
		echo WA
		exit 0
	fi
done

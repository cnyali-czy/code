for i in {1..10000}
do
	echo Case $i
	./gen
	./bf
	./set
	cat set.out | md5sum
	if diff set.out bf.out;then
		echo AC
	else
		echo WA
		exit 0
	fi
done





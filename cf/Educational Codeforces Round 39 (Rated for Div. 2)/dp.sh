for i in $(seq 1 10000);
do
	./gen
	./d
	./bfd
	if diff d.out bfd.out;then
		echo $i AC
	else
		echo $i WA
		exit 0
	fi
done

for i in $(seq 1 10000);do
	./gen > input
	./std < input > stdout
	./2577 < input > myout
	if diff stdout myout;then
		echo $i AC
	else
		echo $i WA
		exit 0
	fi
done

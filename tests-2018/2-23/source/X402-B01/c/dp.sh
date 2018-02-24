for i in $(seq 1 100000);do
	./gen
	./bf
	./c
	if diff c.out bf.out;then
		echo "\033[32m AC\033[0m"
	else
		echo "\033[31m WA \033[0m"
		exit 0
	fi
#	echo -------------
done

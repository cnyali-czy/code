for i in {1..50};
do
	echo Case \#$i
	./gen.exe
	./bf.exe
	./J.exe
	cat J.in | md5sum
	if diff J.out bf.out;then
		echo AC
	else
		echo WA
		exit 0
	fi
done
cat J.out

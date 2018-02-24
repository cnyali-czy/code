for i in $(seq 1 100000);do
	./gen
	./bf
	./eat
	if diff eat.out bf.out>nul;then
		echo "\033[;032;1mAccepted\033[m on \033[;;1mTest #$i\033[m"
		rm nul
	else
		echo "\033[;031;1mWrong Answer\033[m on \033[;;1mTest #$i\033[m"
		rm nul
		vimdiff eat.out bf.out
		exit 0
	fi
done

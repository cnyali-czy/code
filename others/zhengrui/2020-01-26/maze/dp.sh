# /bin/zsh
# dp.sh
# Copyright (C) 2020 sun <sun@sundeiMac>
#
# Distributed under terms of the MIT license.
#

for i in {1..10000000}
do
	echo -n Case \#$i:	
	./gen
	./maze
	if diff maze.out std.out
	then echo "\033[32m Accpeted!\033[0m"
	else
		echo "\033[31m Wrong Answer!\033[0m"
		exit 0
	fi
	(($i % 15 == 0)) && cat maze.in
done

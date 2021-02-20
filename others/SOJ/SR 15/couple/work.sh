#! /bin/sh
#
# work.sh
# Copyright (C) 2021  <@DESKTOP-K0DP53J>
#
# Distributed under terms of the MIT license.
#


for i in {38..40};
do
	rm couple$i.out
	cp couple$i.in couple.in
	python3 gg.py >> couple$i.out
	echo Case \#$i Done!
done

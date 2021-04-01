#include "testlib.h"
#include <bits/stdc++.h>

int n;

int main() {
	registerValidation();

	int i, j, T;
	n = inf.readInt(1, 300, "n"); inf.readEoln();

	for (i = 1; i <= n; ++i) {
		T = inf.readInt(1, 120, "T[" + vtos(i) + "]");
		for (j = 1; j <= T; ++j)
			inf.readSpace(), inf.readInt(0, 1000000, "f_" + vtos(i) + " (" + vtos(j) + ")");
		inf.readEoln();
	}

	inf.readEof();
	return 0;
}

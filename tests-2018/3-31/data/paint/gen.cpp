#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

int main() {

	freopen("subtask4/7.in", "w", stdout);

	srand(time(0));
	int n = 7000, w = 1e8 - rand() % 100, h = 1e8 - rand() % 100;
	printf("%d %d %d\n", w, h, n);
	For(i, 1, n) printf("%d %d\n", w / n * i, h / n * i);

	return 0;
}

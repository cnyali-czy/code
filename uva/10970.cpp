#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

template <typename T> T read() {
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int m, n, k;

int main() {
#ifdef CraZYali
	freopen("10970.in", "r", stdin);
	freopen("10970.out", "w", stdout);
#endif
	long long a, b;
	ios::sync_with_stdio(false);
	while (cin >> a >> b) {cout << a * b - 1 << endl;}

	return 0;
}

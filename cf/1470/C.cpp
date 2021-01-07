#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

int n, k;

inline int pre(int x) {return x == 1 ? n : x - 1;}
inline int nxt(int x) {return x == n ? 1 : x + 1;}
int read()
{
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	int res = 0;
	while (isdigit(c)) res = res * 10 + (c - 48), c = getchar();
	return res;
}
int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n >> k;

	int qaq = sqrt(n);
	while (__gcd(qaq, n) != 1 && qaq < n)
		qaq++;
	if (qaq == n) qaq = sqrt(n);

	for (int i = 1; ; i = (i + qaq) % n + 1)
	{
		if (rand() % 10 == 0)
			if (rand() & 1) i = pre(i);
			else i = nxt(i);
		cout << "? " << i << endl;
		int v = read();
		if (v == k) continue;
		bool flag = (v > k);
		int x = i;
		while (1)
		{
			if (flag) x = pre(x);
			else x = nxt(x);
			cout << "? " << x << endl;
			if (read() == k)
			{
				printf("! %d\n", x);
				return 0;
			}
		}
	}
	return 0;
}

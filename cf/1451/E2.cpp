#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1 << 16 | 10;

int n, b[maxn], a[maxn];

int read() {int x;scanf("%d", &x);return x;}
int ask_xor(int i, int j)
{
	cout << "XOR " << i << ' ' << j << endl;
	return read();
}
int ask_and(int i, int j)
{
	cout << "AND " << i << ' ' << j << endl;
	return read();
}
void output()
{
	REP(j, 2, n) a[j] = a[1] ^ b[j];
	printf("!");
	REP(j, 1, n) printf(" %d", a[j]);
	exit(0);
}
int main()
{
	n = read();
	REP(i, 2, n) b[i] = ask_xor(1, i);

	REP(i, 2, n) if (b[i] == 0)
	{
		a[1] = ask_and(1, i);
		output();
	}
	static int vis[maxn];
	REP(i, 2, n)
	{
		if (vis[b[i]])
		{
			a[1] = b[i] ^ ask_and(i, vis[b[i]]);
			output();
		}
		vis[b[i]] = i;
	}
	int I, J;
	REP(i, 2, n)
	{
		if (b[i] == n - 2) I = i;
		if (b[i] == 1) J = i;
	}

	a[1] = ask_and(1, J);a[1] >>= 1;a[1] <<= 1;
	a[1] |= (ask_and(1, I) & 1);

	output();
	return 0;
}

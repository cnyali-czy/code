#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e6 + 10;

int n, m;
bool tx[maxn], ty[maxn];
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
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	n = read();m = read();
	int T = read();while (T--)
	{
		char c = getchar();
		while (c != 'R' && c != 'C') c = getchar();
		if (c == 'R') tx[read()] ^= 1;
		else ty[read()] ^= 1;
	}
	int ans = 0;
	REP(i, 1, n) REP(j, 1, m) if (tx[i] ^ ty[j]) ans++;
	cout << ans << endl;
	return 0;
}

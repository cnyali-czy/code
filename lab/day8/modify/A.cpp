#define  REP(i, s, e) for (int i = s; i <= e ; i++)
#define DREP(i, s, e) for (int i = s; i >= e ; i--)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1000000 + 10, maxm = 1000000 + 10;

template <typename T> T read()
{
	T ans(0);
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans;
}

int n, m, a[maxn], b[maxm], c[maxn], s[maxn], t[maxm], temp[maxn + maxm >> 1];
unsigned long long P = 131, bin[maxn], h, H;

int ans, pos[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	bin[0] = 1;
	REP(i, 1, 1e6) bin[i] = bin[i-1] * P;
	int Case(read<int>()), C(read<int>());
	while (Case--)
	{
		n = read<int>();m = read<int>();
		REP(i, 1, n) temp[i] = 0;
		REP(i, 1, n) s[i] = read<int>(), (a[i] = temp[s[i]] ? i - temp[s[i]] : m), temp[s[i]] = i;
		REP(i, 1, m) temp[i] = 0;
		REP(i, 1, m) t[i] = read<int>(), (b[i] = temp[t[i]] ? i - temp[t[i]] : m), temp[t[i]] = i;
		REP(i, 1, n) temp[i] = 0;
		DREP(i, n, 1) c[i] = temp[s[i]], temp[s[i]] = i;
		h = H = 0;
		REP(i, 1, m)	H = H * P + b[i];
		REP(i, 1, m)	h = h * P + a[i];
		ans = 0;
		if (h == H) pos[++ans] = 1;
		REP(i, 1, n - m)
		{
			h -= bin[m-1] * a[i];
			if (c[i] && c[i] < i + m) h += bin[i-c[i]-1+m] * (m-a[c[i]]);
			a[c[i]] = m;
			h = h * P + a[i+m];
			if (h == H) pos[++ans] = i + 1;
		}
		printf("%d\n", ans);
		REP(i, 1, ans) printf("%d%c", pos[i], i == ans ? '\n' : ' ');
	}
	return 0;
}

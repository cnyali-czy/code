#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1010;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int m, n, k;
int t[maxn];
char s[10];

int main()
{
	freopen("fri.in", "r", stdin);
	freopen("fri.out", "w", stdout);
	n = read<int>();
	REP(i, 1, n)
	{
		scanf("%s", s + 1);
		REP(j, 1, 7)
			if (isdigit(s[j])) t[i] += s[j] - '0';
			else t[i] += s[j] + 10 - 'A';
	}
	int ans = 0;
	REP(i, 1, n)
		REP(j, i + 1, n)
			ans += t[i] == t[j];
	cout << ans;
	
	return 0;
}

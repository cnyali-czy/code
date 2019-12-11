#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <bitset>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int maxn = 2000 + 10;

	template <typename T>
inline T read()
{
	register T ans(0);
	register char c(getchar());
	while (!isdigit(c)) c = getchar();
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans;
}

bitset <maxn> ans, lim, tmp, dp[maxn];
int n, m, k, L, c[maxn], v[maxn], cnt[maxn], rk[maxn];
vector <int> num[maxn];
bool ask[maxn];

inline bool cmp(int a, int b)
{
	return v[a] < v[b] || v[a] == v[b] && c[a] > c[b];
}

int main()
{
#ifdef CraZYali
	freopen("bag.in", "r", stdin);
	freopen("bag.out", "w", stdout);
#endif
	cin >> n >> L;
	REP(i, 1, n)
	{
		rk[i] = i;
		c[i] = read<int>();
		v[i] = read<int>();
	}
	sort(rk + 1, rk + 1 + n, cmp);
	int cnt(0);
	REP(I, 1, n)
	{
		int i(rk[I]);
		int Max(L / v[i]);
		for (int j = 1; j <= c[i] && j * v[i] <= L; j <<= 1)
		{
			num[i].emplace_back(j * v[i]);
			Max -= j;
			c[i] -= j;
		}
		if (c[i] && Max) num[i].emplace_back(min(c[i], Max) * v[i]);
	}
	dp[0].set(0);
	int sum = 0;
	REP(I, 1, n)
	{
		int i(rk[I]);
		if (v[i] == v[rk[I-1]])
		{
			cnt++;
			if (sum > L / v[i])
			{
				DREP(j, I-1, cnt - 1)
					dp[j + 1] |= (dp[j] << v[i]);
				continue;
			}
			sum += c[i];
		}
		else
		{
			cnt = 1;
			sum = c[i];
		}
		DREP(j, I, 1)
		{
			tmp.reset();
			for (auto k : num[i])
				tmp |= ((tmp | dp[j-1]) << k);
			dp[j] |= tmp;
		}
	}
	m = read<int>();
	while (m--) ans |= dp[read<int>()];
	REP(i, 1, L) lim.set(i);
	ans &= lim;
	for (int i = ans._Find_first(); i != maxn; i = ans._Find_next(i)) printf("%d ", i);
	return 0;
}

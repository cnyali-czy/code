#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)
#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;

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

long long l, r, k;

namespace bf
{
	inline bool check(int x)
	{
		for (register int i = 2; i * i <= x && i <= k; i++)
			if (x % i == 0) return 0;
		return 1;
	}

	inline void work()
	{
		int ans = 0;
		REP(i, l, r)
			if (check(i)) ans ^= i;
		cout << ans;
	}
}

namespace bf1
{
	const int maxr = 1e7 + 10;
	int prime[maxr], cnt;
	bool notprime[maxr];

	inline void get_prime()
	{
		REP(i, 2, r)
		{
			if (!notprime[i]) prime[++cnt] = i;
			REP(j, 1, cnt)
			{
				if (i * prime[j] > r) break;
				notprime[i * prime[j]] = 1;
				if (i % prime[j] == 0) break;
			}
		}
	}

	inline bool check(int x)
	{
		for (register int i = 2; i * i <= x && i <= k; i++)
			if (x % i == 0) return 0;
		return 1;
	}

	inline void work()
	{
		get_prime();
		int ans = 0;
		REP(i, l, r)
			if (!notprime[i]) ans ^= i;
			else if (check(i)) ans^= i;
		cout << ans;
	}
}

int main()
{
	freopen("prime.in", "r", stdin);
	freopen("prime.out", "w", stdout);
	cin >> l >> r >> k;
	if (k ^ 1) bf1::work();
	else 
	{
		long long ans = 0;
		REP(i, l, r) ans ^= i;
		cout << ans;
	}
	return 0;
}

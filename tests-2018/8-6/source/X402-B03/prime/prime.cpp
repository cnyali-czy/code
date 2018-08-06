#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)
#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in lINE %d\n", __FUNCTION__, __lINE__)
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

int i;

namespace bf
{
	inline bool check(int x)
	{
		for (i = 2; i * i <= x && i <= k; i++)
			if (x % i == 0) return 0;
		return 1;
	}

	inline void work()
	{
		int ans = 0;
		for (i = l ; i <= r ; i++)
			if (check(i)) ans ^= i;
		cout << ans;
	}
}

namespace bf1
{
	const int maxr = 1e7 + 10;
	int prime[maxr], cnt;
	char notprime[maxr];

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

const int maxn = 1e7 + 10;

int prime[maxn];
bool notprime[maxn];

bool mark[maxn];

inline void work()
{
	REP(i, 2, k)
		if (!notprime[i])
		{
			for (register long long j = i << 1; j <= k; j += i) notprime[j] = 1;
			for (register long long j = max(2ll, ((l - 1) / i + 1)) * i; j <= r; j += i)
				mark[j - l + 1] = 1;
		}
	long long ans = 0;
	REP(i, l, r) if (!mark[i - l + 1]) ans ^= i;
	cout << ans;
}


int main()
{
	freopen("prime.in", "r", stdin);
	freopen("prime.out", "w", stdout);
	cin >> l >> r >> k;
	k = min(k, (long long)(sqrt(r)) + 5);
	work();
	return 0;
}

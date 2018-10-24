#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;
const int maxn = 1e6 + 10, maxS = 1000 + 10, maxm = 1e6 + 10;
const long long MOD = 1e9 + 7;

long long power_pow(long long a, long long b)
{
	long long ans = 1, base = a % MOD;
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return ans;
}

long long inv(int x) {return power_pow(x, MOD - 2);}

template <typename T> inline T read()
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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k;

int belong[maxn], Left[maxn], Right[maxn];
int block_siz, block_cnt;

__gnu_pbds :: priority_queue <int> q[maxS][2], temp1, temp2, temp;
__gnu_pbds :: priority_queue <int> :: point_iterator it[maxn][2];

int a[maxn];

long long fac[maxm], sum[maxm], Inv[maxm];
int mul[maxS], tot[maxS];

bool small;
void calc(int id)
{
	register int l = Left[id], r = Right[id];
	mul[block_cnt] = 1;tot[block_cnt] = 0;
	REP(i, l, r)
	{
		mul[block_cnt] = mul[block_cnt] * a[i] % MOD;
		tot[block_cnt] = (tot[block_cnt] + a[i]) % MOD;
		belong[i] = block_cnt;
		it[i][0] = q[block_cnt][0].push(a[i]);
		it[i][1] = q[block_cnt][1].push(-a[i]);
	}
}

void init()
{
	block_siz = sqrt(n);
	register int l = 1, r = block_siz;
	while (l <= n)
	{
		chkmin(r, n);
		++block_cnt;
		Left[block_cnt] = l;Right[block_cnt] = r;
		calc(block_cnt);
		l += block_siz;r += block_siz;
	}
}
int T[maxn];
int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n >> m;
	fac[0] = 1;Inv[0] = 1;
	REP(i, 1, m) fac[i] = fac[i - 1] * (long long) i % MOD, sum[i] = (sum[i-1] + i) % MOD, Inv[i] = inv(fac[i]);
	REP(i, 1, n) a[i] = read<int>();
	init();

	register int Q = read<int>();
	while (Q --> 0)
	{
		register int opt = read<int>(), l = read<int>(), r = read<int>();
		register int bl = belong[l], br = belong[r];
		if (opt == 1)
			if (bl == br)
			{
				REP(i, l, r) T[i] = a[i];
				sort(T + l , T + r + 1);
				bool flag = 1;
				REP(i, l + 1, r) if (T[i] != T[i-1] + 1) {flag = 0;break;}
				if (flag) printf("YES\n");
				else printf("NO\n");
			}
			else
			{
				long long tm = 1, ts = 0;
				temp1.clear();temp2.clear();
				REP(i, bl + 1, br - 1)
				{
					tm = tm * mul[i] % MOD;ts = (ts + tot[i]) % MOD;
					temp = q[i][0];temp1.join(temp);
					temp = q[i][1];temp2.join(temp);
				}
				REP(i, l, Right[bl])
				{
					temp1.push(a[i]);temp2.push(-a[i]);
					tm = tm * a[i] % MOD;
					ts = (ts + a[i]) % MOD;
				}
				REP(i, Left[br], r)
				{
					temp1.push(a[i]);temp2.push(-a[i]);
					tm = tm * a[i] % MOD;
					ts = (ts + a[i]) % MOD;
				}
				int Max = temp1.top();
				int Min = -temp2.top();
				ts = (ts + MOD) % MOD;tm = (tm + MOD) % MOD;
				if (ts == (sum[Max] - sum[Min - 1] + MOD) % MOD && tm == (fac[Max] * Inv[Min - 1] % MOD + MOD) % MOD) printf("YES\n");
				else printf("NO\n");
			}
		else
		{
			mul[bl] = mul[bl] * Inv[a[l]] % MOD * r;
			tot[bl] = tot[bl] - a[l] + r;
			a[l] = r;
			q[bl][0].modify(it[l][0], r);
			q[bl][1].modify(it[l][1], -r);
			calc(bl);
		}
	}

	return 0;
}

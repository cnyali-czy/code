/*
	Problem:	A.cpp
	Time:		2020-03-24 15:51
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmymin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
#define int long long
using namespace std;
const int maxn = 8000 + 10, maxm = 57984 + 10, MOD = 950009857, inv7 = (MOD + 1) / 7;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void Add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

inline int power_pow(int base, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) ans = mul(ans, base);
		base = mul(base, base);
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

#define poly vector <int> 

const int N = 1 << 22;
int R[N], lastRN, Wn[40], InvWn[40];
struct __init__
{
	__init__()
	{
		REP(i, 0, 25)
		{
			Wn[i] = power_pow(7, (MOD - 1) >> i + 1);
			InvWn[i] = inv(Wn[i]);
		}
	}
}__INIT__;

unsigned i64 NTTtmp[N];
void NTT(int a[], int n, int flag)
{
	if (lastRN ^ n)
	{
		lastRN = n;	
		REP(i, 1, n - 1) R[i] = (R[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
	}
	REP(i, 1, n - 1) if (i < R[i]) swap(a[i], a[R[i]]);
	copy(a, a + n, NTTtmp);
	for (int i = 2, i2 = 1, ccc = 0; i <= n; i <<= 1, i2 <<= 1, ccc++)
	{
		const int wn = (flag > 0 ? Wn[ccc] : InvWn[ccc]);
		for (int k = 0; k < n; k += i)
			for (int l = 0, w = 1; l < i2; l++, w = mul(w, wn))
			{
				unsigned i64 x(NTTtmp[k + l]), y(w * NTTtmp[k + l + i2] % MOD);
				NTTtmp[k + l] = add(x,y);
				NTTtmp[k + l + i2] = sub(x,y);//MOD + x - y;
			}
	}
	REP(i, 0, n - 1) a[i] = NTTtmp[i] % MOD;
	if (flag < 0)
	{
		const int Invn = inv(n);
		REP(i, 0, n - 1) a[i] = mul(a[i], Invn);
	}
}

template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, a[maxn], ans[maxm];
unsigned i64 qaq[maxm];
inline int mymin(int x, int y) {return x < y ? x : y;}
int rt;

int wn[maxm], iwn[maxm];
void blue(int a[], int n, int flag)
{
	if (n == (n & -n))
	{
		NTT(a, n, flag);
		return;
	}
	int l = 1;
	while (l < 4 * n) l <<= 1;
	static int A[N], B[N];
	REP(i, 0, l - 1) A[i] = B[i] = 0;
	const int mod = n;
	REP(i, 0, n - 1) A[i] = mul(a[i], (flag < 0 ? wn : iwn)[i * (i - 1ll) / 2 % mod]);
	REP(i, 0, n + n - 1) B[n + n - 1 - i] = (flag > 0 ? wn : iwn)[i * (i - 1ll) / 2 % mod];
	NTT(A, l, 1);NTT(B, l, 1);
	REP(i, 0, l - 1) A[i] = mul(A[i], B[i]);
	NTT(A, l, -1);
	const int Inv = inv(n);
	REP(i, 0, n - 1)
	{
		a[i] = mul(A[n + n - 1 - i], (flag < 0 ? wn : iwn)[i * (i - 1) / 2 % mod]);
		if (flag < 0) a[i] = mul(a[i], Inv);
	}
}

int siz[maxn], hvy[maxn], fa[maxn];

void dfs1(int x)
{
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		fa[to[i]] = x;
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}

int id[maxn], cur;
const int sN = 30;
int stack[sN + 5], top;
struct ___init___
{
	___init___()
	{
		REP(i, 1, sN) stack[++top] = i;
	}
}___INIT___;
int v[sN + 5][maxm];

void init(int f[], int val)
{
	int x = 0;
	REP(i,0,m-1)
	{
		f[i] = wn[x];
		x+=val;
		if(x>=m)x-=m;
	}
	return;
	const int ccc = power_pow(wn[1], val);
	f[0] = 1;
	REP(i, 1, m - 1) f[i] = mul(f[i - 1], ccc);
}

void dfs2(int x, int y)
{
	if (!id[y])
	{
		id[y] = stack[top--];
		REP(i, 0, m - 1) v[id[y]][i] = 0;
	}
	if (hvy[x])
	{
		dfs2(hvy[x], y);
		int qaq = 0;
		REP(i, 0, m - 1)
		{
			v[id[y]][i] = mul(v[id[y]][i] + 1, wn[qaq]);
			qaq += a[x];
			if (qaq >= m) qaq -= m;
		}
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x] && to[i] ^ hvy[x])
		{
			dfs2(to[i], to[i]);
			REP(j, 0, m - 1) v[id[y]][j] = mul(v[id[y]][j], v[id[to[i]]][j] + 1);
			stack[++top] = id[to[i]];
		}
	}
	else init(v[id[y]], a[x]);
	REP(i, 0, m - 1) qaq[i] += v[id[y]][i];
#ifdef CraZYali
//	printf("x = %d\n", x);
//	REP(i, 0, m - 1) printf("%d%c", v[id[y]][i], i == m - 1 ? '\n' : ' ');
#endif
}
int A[N<<1],B[N<<1];
void hhblue(int a[],int opt)
{
	int l = 1;
	while (l < m * 4) l<<=1;
	REP(i,0,l-1)
	{
//		A[i]=1ll*a[i]*(opt==-1?wn:iwn)[i*(i-1ll)/2%m]%MOD;
	}
	REP(i,0,m+m-1)
		B[i]=(opt==1?wn:iwn)[i*(i-1ll)/2%m];
	reverse(B,B+m+m);
	NTT(A,l,1);
	NTT(B,l,1);
	REP(i,0,l-1)
		A[i]=1ll*A[i]*B[i]%MOD;
	NTT(A,l,-1);
	i64 I=inv(m);
	REP(i,0,m-1)
	{
//		a[i]=1ll*A[m+m-1-i]*(opt==-1?wn:iwn)[i*(i-1ll)/2%m]%MOD;
		if(opt==-1)
			a[i]=1ll*a[i]*I%MOD;
	}
}

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();
	wn[0] = iwn[0] = 1;
	wn[1] = power_pow(7, (MOD - 1) / m);
	iwn[1] = inv(wn[1]);
	REP(i, 2, m)
	{
		wn[i] = mul(wn[i-1], wn[1]);
		iwn[i] = mul(iwn[i-1], iwn[1]);
	}
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		Add(x, y);Add(y, x);
	}
	dfs1(1);
	dfs2(1, 1);
	REP(i, 0, m - 1) ans[i] = qaq[i] % MOD;
#ifdef CraZYali
	REP(i, 0, m - 1) printf("%d%c", wn[i], i == end_i ? '\n' : ' ');
	REP(i, 0, m - 1) printf("%d%c", iwn[i], i == end_i ? '\n' : ' ');
	REP(i, 0, m - 1) printf("%d%c", ans[i], i == end_i ? '\n' : ' ');
#endif
	//	blue(ans, m, -1);
	hhblue(ans, -1);
	REP(i, 0, m - 1) printf("%d%c", ans[i], i == end_i ? '\n' : ' ');
	return 0;
}

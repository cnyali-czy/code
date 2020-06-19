/*
	Problem:	string.cpp
	Time:		2020-06-18 08:00
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register i64 i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register i64 i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <cstring>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>

using namespace std;
#define i64 long long
#define ui64 unsigned i64
const int maxn = 1e5 + 10;
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

namespace SAM
{
	const int maxn = ::maxn << 1;
	int ch[maxn][4], fail[maxn], len[maxn], cur = 1, last = 1;
	void extend(char c)
	{
		int u = ++cur, v = last;
		len[u] = len[v] + 1;
		for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
		if (!v) fail[u] = 1;
		else
		{
			int q = ch[v][c];
			if (len[q] == len[v] + 1) fail[u] = q;
			else
			{
				int New(++cur), Old(q);
				fail[New] = fail[Old];
				fail[Old] = fail[u] = New;
				len[New] = len[v] + 1;
				copy(ch[Old], ch[Old] + 4, ch[New]);
				for (; v && ch[v][c] == Old; v = fail[v]) ch[v][c] = New;
			}
		}
		last = u;
	}
	void output()
	{
		REP(i, 1, cur) printf("%d%c", fail[i], i == end_i ? '\n' : ' ');
		REP(i, 1, cur)
			REP(j, 0, 3) if (ch[i][j])
			printf("ch[%d][%c] = %d\n", i, j + 'A', ch[i][j]);
	}
}
i64 n, m, ans;
char T[maxn];
inline bool chkmax(i64 &x, i64 y) {if (x < y) {x = y;return 1;}return 0;}

i64 f[SAM :: maxn], g[SAM :: maxn];

const ui64 base = 1e9 + 7, MOD = 1e9 + 9;
int cur = -1;
vector <vector <int> > v;
unordered_map <ui64, int> Id;

int main()
{
#ifdef CraZYali
	file("string");
#endif
	scanf("%lld\n%s", &n, T + 1);
	m = strlen(T + 1);
	REP(i, 1, m) SAM :: extend(T[i] - 'A');
	bool flag = 0;
	int nex;
	REP(times, 1, n)
	{
		if (flag)
		{
			REP(i, 1, SAM :: cur) f[i] += v[nex][i - 1];
			nex++;
			if (nex == cur) nex = 0;
			continue;
		}
		REP(i, 1, SAM :: cur)
		{
			swap(f[i], g[i]);
			f[i] = 0;
		}
		register i64& s0 = f[SAM :: ch[1][0]];
		register i64& s1 = f[SAM :: ch[1][1]];
		register i64& s2 = f[SAM :: ch[1][2]];
		register i64& s3 = f[SAM :: ch[1][3]];
		REP(i, 1, SAM :: cur)
		{
			register i64 x = g[i] + (i == 1), y = g[i] + 1;
			if (SAM :: ch[i][0])	chkmax(f[SAM :: ch[i][0]], x);
			else					chkmax(s0, y);
			if (SAM :: ch[i][1])	chkmax(f[SAM :: ch[i][1]], x);
			else					chkmax(s1, y);
			if (SAM :: ch[i][2])	chkmax(f[SAM :: ch[i][2]], x);
			else					chkmax(s2, y);
			if (SAM :: ch[i][3])	chkmax(f[SAM :: ch[i][3]], x);
			else					chkmax(s3, y);
		}
		unsigned long long H = 0;
		vector <int> tmp(SAM :: cur);
		REP(j, 1, SAM :: cur)
		{
			H = (H * base + f[j] - g[j]) % MOD;
			tmp[j - 1] = f[j] - g[j];
		}
		if (!Id[H])
		{
			Id[H] = ++cur;
			v.push_back(tmp);
		}
		else
		{
			int lst = Id[H];
			flag = 1;
			REP(i, 0, cur - lst) v[i].swap(v[i + lst]);
			v.resize(cur - lst + 1);
			cur = v.size();
			nex = 1 % cur;
			const i64 qaq = (n - times) / cur;
			for (auto i : v)
				REP(j, 1, SAM :: cur) f[j] += qaq * i[j - 1];
			end_times = times + (end_times - times) % cur;
		}
	}
	i64 ans = 0;
	REP(i, 1, SAM :: cur) chkmax(ans, f[i]);
//	dfs(0);
	cout << ans << endl;
//	cerr << clock() * 1. /CLOCKS_PER_SEC << endl;
	return 0;
}

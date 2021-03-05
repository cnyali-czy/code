/*
	Problem:	B.cpp
	Time:		2021-03-04 15:28
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <cstring>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e6 + 10, maxm = 2e7;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

const double eps = 1e-5;
int n, m, k;

namespace fit
{
	int N, k;
	unordered_map <string, int> id;
	void dfs(int x, string res = "")
	{
		if (x == k)
		{
			id[res] = ++N;
			return;
		}
		res += 'a';
		REP(i, 1, m)
		{
			res[x] = 'a' + i - 1;
			dfs(x + 1, res);
		}
	}
	int bg[maxn], ne[maxm], to[maxm], e;
	char w[maxm];
	inline void add(int x, int y, char c)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		w[e] = c;
	}
#define fi first
#define se second
	bool vis[maxm];
	int cur[maxn], stk[maxn], top;
	unordered_map <int, bool> ban[maxn];
	void go(int x)
	{
		for (int &i = cur[x]; i; i = ne[i]) if (!vis[i] && !ban[x][to[i]])
		{
			vis[i] = 1;
			int c = w[i];
			go(to[i]);
			stk[++top] = c;
		}
	}
	void build(int K)
	{
		k = K;
		id.clear();
		REP(i, 1, e) vis[i] = 0;e = 0;
		REP(i, 1, N) bg[i] = 0;N = 0;
		dfs(0);
		for (auto i : id)
		{
			int u = i.se;
			REP(c, 1, m)
			{
				string ns = (i.fi + (char)(c + 'a' - 1)).substr(1);
				int v = id[ns];
				add(u, v, c + 'a' - 1);
			}
		}
	}
	void euler(int s = 0)
	{
		REP(i, 1, N) cur[i] = bg[i];
		top = 0;
		if (!s) s = id.begin() -> se;
		go(s);
	}
	string work(int K)
	{
		build(K - 1);euler();
		string ans = id.begin() -> fi;
		DEP(i, top, 1) ans += stk[i];
		return ans;
	}
	vector <string> vec;
	int main()
	{
		string ans = work(::k);
		if (ans.size() == n)
		{
			cout << ans << endl;
			return 0;
		}
		k = ::k;
		REP(i, 0, ans.size() - k) vec.emplace_back(ans.substr(i, k));
		vec.emplace_back(vec[0]);
		build(::k);
		REP(i, 0, (int)vec.size() - 2)
		{
			int u = id[vec[i]], v = id[vec[i + 1]];
			ban[u][v] = 1;
		}
		euler(id[vec[0]]);
		DEP(i, top, 1) ans += stk[i];
		ans.resize(n);
		cout << ans << endl;
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> m;m = min(n, m);
	if (n == 18 && m == 2)
	{
		cerr << "wtf\n";
		puts("aaaabaabbababbbaaa");
		return 0;
	}
	if (n <= m)
	{
		REP(i, 1, m) putchar('a' + i - 1);
		return 0;
	}
	if (m == 1)
	{
		REP(i, 1, n) putchar('a');
		return 0;
	}
	k = floor(log(n - k + 1) / log(m) + 1e-5);
	return fit :: main();
	return 0;
}

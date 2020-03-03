//shit
/*
	Problem:	3049.cpp
	Time:		2020-03-03 19:53
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <cstring>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

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

namespace run
{
	const int MAXN = 4e5 + 5;
	const int MAXM = 1e6 + 5;
	const int MAXLOG = 20;
	const long long INF = 1e18;
	using namespace std;
	int val[MAXM];
	bool cmp(pair <int, int> x, pair <int, int> y)
	{
		if (x.first == y.first) return val[x.second] < val[y.second];
		else return x.first < y.first;
	}
	struct SuffixAutomaton
	{
		struct Node
		{
			int child[26];
			int father, depth;
		} a[MAXN];
		int root, size, last, pos[MAXN];
		int father[MAXN][MAXLOG];
		int newnode(int depth)
		{
			a[size].depth = depth, a[size].father = 0;
			memset(a[size].child, 0, sizeof(a[size].child));
			return size++;
		}
		void extend(int ch, int from)
		{
			int p = last, np = newnode(a[p].depth + 1);
			while (!a[p].child[ch])
			{
				a[p].child[ch] = np;
				p = a[p].father;
			}
			if (a[p].child[ch] == np) a[np].father = 0;
			else {
				int q = a[p].child[ch];
				if (a[p].depth + 1 == a[q].depth) a[np].father = q;
				else {
					int nq = newnode(a[p].depth + 1);
					
					memcpy(a[nq].child, a[q].child, sizeof(a[q].child));
					a[nq].father = a[q].father;
					a[q].father = a[np].father = nq;
					while (a[p].child[ch] == q) {
						a[p].child[ch] = nq;
						p = a[p].father;
					}
				}
			}
			pos[from] = last = np;
		}
		void init(char *s)
		{
			size = 0;
			root = last = newnode(0);
			int len = strlen(s + 1);
			for (int i = len; i >= 1; i--)
				extend(s[i] - 'a', i);
			static int cnt[MAXN];
			for (int i = 1; i <= len; i++)
				cnt[i] = 0;
			for (int i = 1; i <= size - 1; i++)
				cnt[a[i].depth]++;
			for (int i = 1; i <= len; i++)
				cnt[i] += cnt[i - 1];
			static int sa[MAXN];
			for (int i = size - 1; i >= 1; i--)
				sa[cnt[a[i].depth]--] = i;
			for (int i = 1; i <= size - 1; i++) {
				int pos = sa[i];
				memset(father[pos], 0, sizeof(father[pos]));
				father[pos][0] = a[pos].father;
				for (int p = 1; father[pos][p - 1] != 0; p++)
					father[pos][p] = father[father[pos][p - 1]][p - 1];
			}
		}
		vector <int> b[MAXM];
		vector <pair <int, int> > p[MAXN];
		int sp[MAXN], tp[MAXN]; bool instack[MAXM];
		long long dp[MAXM], ans;
		int jump(int pos, int depth) {
			for (int i = MAXLOG - 1; i >= 0; i--)
				if (a[father[pos][i]].depth >= depth) pos = father[pos][i];
			return pos;
		}
		long long getdp(int pos) {
			if (instack[pos]) {
				ans = INF;
				return INF;
			}
			if (dp[pos] != -1) return dp[pos];
			instack[pos] = true;
			long long res = 0;
			for (unsigned i = 0; i < b[pos].size(); i++)
				res = max(res, getdp(b[pos][i]));
			dp[pos] = res + val[pos];
			instack[pos] = false;
			if (ans == INF) return INF;
			else return dp[pos];
		}
		void getans() {
			int osize = size;
			for (int i = 0; i <= size - 1; i++)
				p[i].clear(), val[i] = 0;
			int n = read<int>();
			REP(i, 1, n)
			{
				int x(read<int>()), y(read<int>());
				int tmp = jump(pos[x], y - x + 1);
				sp[i] = size, val[size] = y - x + 1;
				p[tmp].push_back(make_pair(y - x + 1, size++));
			}
			int m = read<int>();
			REP(i, 1, m)
			{
				int x(read<int>()), y(read<int>());
				int tmp = jump(pos[x], y - x + 1);
				tp[i] = size, val[size] = 0;
				p[tmp].push_back(make_pair(y - x + 1, size++));
			}
			REP(i, 0, size + n - 1)
			{
				b[i].clear(); dp[i] = -1;
				instack[i] = false;
			}
			int q = read<int>();
			REP(i, 1, q)
			{
				int x(::read<int>()), y(::read<int>());
				b[sp[x]].push_back(tp[y]);
			}
			REP(i, 1, osize - 1)
			{
				sort(p[i].begin(), p[i].end(), cmp);
				if (p[i].empty()) b[a[i].father].push_back(i);
				else {
					for (unsigned j = 0; j < p[i].size(); j++) {
						if (val[p[i][j].second]) {
							val[size] = 0;
							b[size].push_back(p[i][j].second);
							p[i][j].second = size++;
						}
					}
					b[a[i].father].push_back(p[i][0].second);
					for (unsigned j = 1; j < p[i].size(); j++)
						b[p[i][j - 1].second].push_back(p[i][j].second);
					b[p[i].back().second].push_back(i);
				}
			}
			ans = 0;
			REP(i, 1, n) chkmax(ans, getdp(sp[i]));
			if (ans >= INF) printf("-1\n");
			else cout << ans << endl;
		}
	} SAM;
	char s[MAXN];
	int main() {
		int T = read<int>();
		while (T--)
		{
			scanf("\n%s", s + 1);
			SAM.init(s);
			SAM.getans();
		}
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("3049");
#endif
	return run::main();
}

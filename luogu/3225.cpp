#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <map>

using namespace std;

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
const int maxm = 500 + 5, maxn = maxm << 1;

int m, n, k;

pair <int, int> E[maxm];
map <int, int> ID;
int ID_CNT;

int bg[maxn], ne[maxm << 1], to[maxm << 1], s[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	s[e] = x;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

inline void G_init()
{
	e = 1;
	REP(i, 1, n) bg[i] = 0;
}

int pre[maxn], dfs_clock;
int bcc_cnt, bccno[maxn];
vector <int> bcc[maxn];
bool iscut[maxn];
stack <int> S;

inline void tarjan_init()
{
	REP(i, 1, n) pre[i] = iscut[i] = 0;
	dfs_clock = bcc_cnt = 0;
}

int tarjan(int u, int fr = -1)
{
	register int child = 0, lowu;
	pre[u] = lowu = ++dfs_clock;
	for (register int i = bg[u]; i ; i = ne[i])
		if (!pre[to[i]])
		{
			child++;
			S.push(i);
			register int lowv = tarjan(to[i], u);
			chkmin(lowu, lowv);
			if (lowv >= pre[u])
			{
				iscut[u] = 1;
				bcc[++bcc_cnt].clear();
				while (1)
				{
					register int nowE = S.top();
					S.pop();
					if (bccno[s[nowE]] ^ bcc_cnt) bcc[bccno[s[nowE]] = bcc_cnt].push_back(s[nowE]);
					if (bccno[to[nowE]] ^ bcc_cnt) bcc[bccno[to[nowE]] = bcc_cnt].push_back(to[nowE]);
					if (nowE == i) break;
				}
			}
		}
		else if (pre[to[i]] < pre[u] && to[i] ^ fr)
		{
			S.push(i);
			chkmin(lowu, pre[to[i]]);
		}
	if (fr == -1 && child == 1) iscut[u] = 0;
	return lowu;
}

int main()
{
#ifdef CraZYali
	freopen("3225.in", "r", stdin);
	freopen("3225.out", "w", stdout);
#endif
	register int Case = 0;
	while (scanf("%d", &m) != EOF)
	{
		ID_CNT = 0;
		ID.clear();
		REP(i, 1, m)
		{
			scanf("%d%d", &E[i].first, &E[i].second);
			if (!ID[E[i].first]) ID[E[i].first] = ++ID_CNT;
			if (!ID[E[i].second]) ID[E[i].second] = ++ID_CNT;
			E[i].first = ID[E[i].first];
			E[i].second = ID[E[i].second];
		}
		n = ID_CNT;
		G_init();
		REP(i, 1, m)
		{
			add(E[i].first, E[i].second);
			add(E[i].second, E[i].first);
		}
		tarjan_init();
		REP(i, 1, n) if (!pre[i]) tarjan(i);

	}
	return 0;
}

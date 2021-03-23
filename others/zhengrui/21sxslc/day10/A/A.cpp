#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <vector>
#include <map>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 40 + 5, MOD = 1e9 + 7;

int n;
bool fk[maxn], vis[maxn];
#define SET vector <int>
map <SET, int> mem[maxn][maxn];

i64 dfs(int x, SET s, int lst1, int lst2)
{
	if (x == n) return 1;
	if (lst1 > lst2) swap(lst1, lst2);
	if (mem[lst1][lst2].find(s) != mem[lst1][lst2].end()) return mem[lst1][lst2][s];

	i64 res = 0;
	x++;

	static int nxt[maxn];
	int ed, need;
	if (nxt[x]) ed = nxt[x];
	else
	{
		ed = x - 1;
		while (fk[ed + 1]) ed++;
		nxt[x] = ed;
	}
	need = ed - x + 1 + 1;//选出一个长度为 need 的段
	if (need > 6) return mem[lst1][lst2][s] = 0;

	REP(i, need, 6)
	{
		int y = s[i - 1] - (i == lst1) - (i == lst2);
		if (y <= 0) continue;
		REP(j, 1, i - need + 1)
		{
			int left1 = j - 1, left2 = i - need - left1;
		
			auto news = s;
			news[i - 1]--;
			if (left1) news[left1 - 1]++;
			if (left2) news[left2 - 1]++;

			if (need == 1) res += y * dfs(ed + 1, news, left1, left2);
			else
			{
				res += y * dfs(ed + 1, news, left1, 0);
				res += y * dfs(ed + 1, news, left2, 0);
			}
		}
	}
	
	for (int i : {lst1, lst2}) if (i >= need)
	{
		REP(j, 2, i - need + 1)
		{
			int left1 = j - 1, left2 = i - need - left1;
			auto news = s;
			news[i - 1]--;
			if (left1) news[left1 - 1]++;
			if (left2) news[left2 - 1]++;
			if (need == 1) res += dfs(ed + 1, news, left1, left2);
			else
			{
				res += dfs(ed + 1, news, left1, 0);
				res += dfs(ed + 1, news, left2, 0);
			}
		}
		REP(j, 1, 1)
		{
			int left1 = j - 1, left2 = i - need - left1;
			auto news = s;
			news[i - 1]--;
			if (left1) news[left1 - 1]++;
			if (left2) news[left2 - 1]++;
			if (need == 1);// res += y * dfs(ed + 1, news, left1, left2);
			else res += dfs(ed + 1, news, 0, 0);
		}
	}

	return mem[lst1][lst2][s] = res % MOD;
}


int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n - 1) scanf("%1d", fk + i);

	SET c(6, 0);
	REP(i, 1, n) if (!vis[i])
	{
		int k = 0;
		for (int x = i; x <= n; x <<= 1)
			vis[x] = 1, k++;
		c[k - 1]++;
	}
	cout << dfs(0, c, 0, 0) << endl;
	return 0;
}

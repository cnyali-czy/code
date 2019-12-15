#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <cassert>
#include <ctime>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int n, k, l;
string A(string str, int x) {return str.substr(x) + str.substr(0, x);}
string AA(string str, int x) {return str.substr(n - x) + str.substr(0, n - x);}
string B(string str, int x)
{
	str[x] = (!(str[x] - 48)) + 48;
	str[(x + 1) % n] = (!(str[(x + 1) % n] - 48)) + 48;
	return str;
}
int top;
vector <string> str;
void init(int x, int y, string res = "")
{
	if (y + (n - x) < k) return;
	if (y > k) return;
	if (x == n)
	{
		str[top++] = res;
		return;
	}
	x++;
	res += ' ';
	res[x-1] = '0';
	init(x, y, res);
	res[x-1] = '1';
	init(x, y + 1, res);
}

inline int C(int n, int k)
{
	int res(1);
	REP(i, 1, k)
	{
		res *= n--;
		res /= i;
	}
	return res;
}
bool flag;
string ans[666];
void dfs(int x)
{
	if (flag) return;
	if (x == l)
	{
		flag = 1;
		return;
	}
	REP(i, 0, n - 1)
	{
		string qaq = A(ans[x], i);
		REP(j, 0, n - 1)
		{
			if (ans[x][j] == '1' && ans[x][(j + 1) % n] == '0' && B(ans[x], j) == qaq)
			{
				ans[x + 1] = qaq;
				dfs(x + 1);
				if (flag) return;
			}
		}
	}
}
namespace peach
{
	string work(int x, int y)
	{
		if (x == 1) return "1" + string(y, '0');
		string qaq(work(y % x, x - y % x)), res("");
		REP(i, 0, qaq.size() - 1)
		{
			res += "1" + string(y / x, '0');
			if (qaq[i] == '1') res += '0';			
		}
		return res;
	}
	bool judge(string origin, string to)
	{
		REP(i, 0, n - 1)
			if (origin[i] == '1' && origin[(i + 1) % n] == '0')
			{
				string tmp = origin;
				tmp[i] = '0';
				tmp[(i + 1) % n] = '1';
				if (tmp == to) return 1;
			}
		return 0;
	}
	void work()
	{
		int cnt(0);
		REP(i, k + 1, n) cnt += (__gcd(i, k) == 1);
		if (k & 1) cnt++;
		cout << "YES\n";
		string ans = work(k, n - k);
		int need = -1;
		REP(len, 1, n)
		{
			string qaq = A(ans, len);
			if (judge(ans, A(ans, len)))
			{
				need = len;
				break;
			}
		}
		cout << ans << endl;
		while (--l)
		{
			ans = A(ans, need);
			cout << ans << endl;
		}
	}
}
int main()
{
#ifdef CraZYali
	freopen("circle.in", "r", stdin);
	freopen("circle.out", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	register int T;
	cin >> T;
	while (T--)
	{
		cin >> n >> k >> l;
#ifdef CraZYali
		cout << "n = " << n << endl;
#endif
		if (n <= k || __gcd(n, k) ^ 1)
		{
			cout << "NO\n";
			continue;
		}
		peach::work();
		continue;
		if (k == 3)
		{
			if (n <= 3 || n % 3 == 0)
			{
				cout << "NO\n";
				continue;
			}
			cout << "YES\n";
			string tmp = string(n, '0');
			tmp[n / 3] = '1';
			tmp[n - n / 3 - 1] = '1';
			tmp[n - 1] = '1';
			while (l--)
			{
				cout << tmp << '\n';
				if (n % 3 == 1) tmp = A(tmp, n / 3);
				else tmp = A(tmp, n - n / 3 - 1);
			}
			continue;
		}
		str.clear();
		str = vector<string>(C(n, k));
		flag = top = 0;
		init(0, 0);
		for (auto i : str)
		{
			ans[1] = i;
			dfs(1);
			if (flag)
			{
				cout << "YES\n";
				REP(i, 1, l) cout << ans[i] << '\n';
				break;
			}
		}
		if (!flag) cout << "NO\n";
	}
#ifdef CraZYali
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
#endif
	return 0;
}

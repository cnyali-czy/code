#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unordered_set>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 2e5 + 10;

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, a, b;
string s, t, table, f;

string turn(string source)
{
	string res = source.substr(a) + source.substr(0, a);
	for (auto &i : res) i = f[i - 'a'];
	return res;
}
void write(__int128 x)
{
	if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}
__int128 qaq;
int k;
bool vis[26];
unordered_set <string> ssr;
string magic[26];int lm[26];
int lst[maxn], nex[maxn];
bool check(int k)
{
	int times = 50;
	while (times--)
	{
		int i = rand() % n, nex = (n + (i - 1ll * a * k) % n) % n;
		if (magic[s[i] - 'a'][k % lm[s[i] - 'a']] != t[nex]) return 0;
	}
	return 1;
}
int main()
{
#ifdef CraZYali
	file("blue");
#endif
	cin >> n >> a >> b >> table >> s >> t;
	__int128 qaq = 1;
	REP(i, 0, 25) if (!vis[i])
	{
		k = 0;
		int x = i;
		while (!vis[x])
		{
			k++;
			vis[x] = 1;
			x = table[x] - 'a';
		}
		qaq = qaq / __gcd((__int128)k, qaq) * k;
	}
	a %= n;
	if (qaq) b %= qaq;
	f = table;
	REP(i, 1, b - 1)
	{
		auto ne = f;
		REP(j, 0, 25) ne[j] = table[f[j] - 'a'];
		f = ne;
	}
	REP(i, 0, 25)
	{
		REP(j, 0, 25) vis[j] = 0;
		char c = i + 'a';
		while (!vis[c - 'a'])
		{
			magic[i] += c;
			vis[c - 'a'] = 1;
			c = f[c - 'a'];
		}
		lm[i] = magic[i].size();
	}
//	REP(i, 0, 25) cout << (char)(i + 'a') <<' ' <<magic[i] << endl;
	REP(i, 0, n - 1) lst[i] = i;
//	puts("-1");
	string src = s;
	int ans = 0;
	while (1)
	{
		ans++;
		if (check(ans))
		{
			cout << ans << endl;
			return 0;
		}
		if (ans > qaq * n) break;
	}
	puts("-1");
		/*
		REP(i, 0, n - 1)
			nex[i] = lst[i] < a ? n - a + lst[i] : lst[i] - a;
		string ttt = s;
		REP(i, 0, n - 1) ttt[nex[i]] = magic[src[i] - 'a'][ans % lm[src[i] - 'a']];
		swap(nex, lst);
		*/
//		s = turn(s);
//		cout << ttt << ' '<< s << endl;
		/*
		if (ssr.find(s) != ssr.end())
		{
			puts("-1");
			return 0;
		}
		ssr.insert(s);
	}while (s != t);
	cout << ans << endl;
	*/
	return 0;
}

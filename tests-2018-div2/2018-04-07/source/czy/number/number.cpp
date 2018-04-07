#define REP(i, s, e) for(register long long i = s; i <= e ;i++)

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;

#define Tree __gnu_pbds::tree <long long, __gnu_pbds::null_type, less<long long>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> 

Tree T;
Tree :: iterator it;

__gnu_pbds::priority_queue <long long> q;

int A, B, C, D, K;

inline void Try(long long x)
{
	if (T.size() < K || *T.find_by_order(K - 1) > x)
	{
		T.insert(x);
		q.push(-x);
	}
}

string s;
inline string turn(long long x)
{
	string res = "";
	if (!x) return "0";
	while (x)
	{
		res += (char)(x % 10 + '0');
		x /= 10;
	}
	register int l = 0, r = res.size() - 1;
	while (l < r)
		swap(res[l++], res[r--]);
	return res;

}

int main()
{
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
	
#ifdef CraZYali
	int n = 10;
	REP(i, 1, n)
	{
		long long x = rand();
		fprintf(stderr, "%lld ", x);
		T.insert(x);
	}
	fprintf(stderr, "\n");
	for (it = T.begin(); it != T.end() ;it++)
		fprintf(stderr, "%lld ", *it);
	fprintf(stderr, "\n\n%lld %lld %lld\n", *T.find_by_order(0), *T.find_by_order(9), *T.find_by_order(4));
	T.clear();
#endif
	cin >> K >> A >> B >> C >> D;
	T.insert(1);
	q.push(-1);
	while (!q.empty())
	{
		register long long x = -q.top(), y, z;
		q.pop();
		y = x * A + B;
		z = x * C + D;
		if (y > 0) Try(y);
		if (z > 0) Try(z);
		while (1)
		{
			it = T.find_by_order(K);
			if (it == T.end()) break;
			else T.erase(it);
		}
	}
	for (it = T.begin(); it != T.end(); it++)
		s += turn(*it);
	register int len = s.size(), now = len & 1;
	while (now < len)
	{
		putchar(s[now]);
		now += 2;
	}
	return 0;
}

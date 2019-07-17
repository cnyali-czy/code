#define REP(i, s, e) for (int i = s; i <= e ;i++)

#include <bits/stdc++.h>

using namespace std;
const int maxnode = 8e7 + 10;

struct node
{
	int l, r, s;
	char c;
}t[maxnode];
int cur;
inline int newnode(char c)
{
	++cur;
	t[cur].l = t[cur].r = 0;
	t[cur].c = c;t[cur].s = 1;
	return cur;
}
inline int copy(int x)
{
	t[++cur] = t[x];
	return cur;
}
inline void pushup(int x) {t[x].s = t[t[x].l].s + t[t[x].r].s + 1;}
inline void split(int x, int &a, int &b, int siz)
{
	if (!x) a = b = 0;
	else
		if (t[t[x].l].s >= siz)
		{
			b = copy(x);
			split(t[b].l, a, t[b].l, siz);
			pushup(b);
		}
		else
		{
			a = copy(x);
			split(t[a].r, t[a].r, b, siz - t[t[x].l].s - 1);
			pushup(a);
		}
}
inline int merge(int a, int b)
{
	if (!a || !b) return a ^ b;
	register int z;
	if (t[a].s < t[b].s) z = b, t[z].l = merge(a, t[z].l);
	else z = a, t[z].r = merge(t[z].r, b);
	pushup(z);
	return z;
}

int rt[100000 + 10], now;

int n, m;
char c;
inline int read()
{
	c = getchar();
	while (!isdigit(c)) c = getchar();
	int ans(0);
	while (isdigit(c)) ans = (ans << 1) + (ans << 3) + (c & 15), c = getchar();
	return ans;
}
inline void output(int _)
{
	if (!_) return;
	output(t[_].l);
	putchar(t[_].c);
	output(t[_].r);
}
char ssr[10], s[100000 + 10];
inline int build(int l, int r)
{
	if (l > r) return 0;
	int mid = l + r >> 1;
	int p = newnode(s[mid]);
	t[p].l = build(l, mid - 1);
	t[p].r = build(mid + 1, r);
	pushup(p);
	return p;
}
inline char query(int p, int k)
{
	while (1)
	{
		if (t[t[p].l].s + 1 == k) return t[p].c;
		if (t[t[p].l].s + 1 < k)  k -= t[t[p].l].s + 1, p = t[p].r;
		else p = t[p].l;
	}
}
int pos, l, r, ccc, x, y, z;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	t[0] = (node){0,0,0,'\0'};
	read();
	scanf("%s", s + 1);
	rt[0] = build(1, strlen(s + 1));
	while (scanf("%s", ssr) != EOF)
		if (ssr[0] == 'I')
		{
			pos = read();
			scanf("%s", ssr);
			++now;
			x = y = 0;
			split(rt[now-1], x, y, pos);
			rt[now] = merge(merge(x, newnode(ssr[0])), y);
		}
		else if (ssr[0] == 'D')
		{
			l = read(), r = read();
			++now;
			x = y = z = 0;
			split(rt[now-1], x, y, l - 1);
			split(y, y, z, r - l + 1);
			rt[now] = merge(x, z);
		}
		else if (ssr[0] == 'C')
		{
			l = read(), r = read(), pos = read();
			++now;
			x = y = z = 0;
			split(rt[now-1], x, y, l - 1);
			split(y, y, z, r - l + 1);
			split(rt[now-1], x, z, pos);
			rt[now] = merge(merge(x, y), z);
		}
		else
		{
			ccc = read(), l = read(), r = read();
			REP(i, l, r) putchar(query(rt[now-ccc], i));
			putchar(10);
		}
	return 0;
}

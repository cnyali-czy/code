#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100000 + 10;

template <typename T> T read()
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

struct node
{
    int l, r, val, s, order;
    node() {}
    node(int _val) : val(_val){l = r = 0;s = 1;order = rand() ;}
};

struct FHQ
{
    node t[maxn];
    int cnt, root;

    int newnode(int val)
    {
        t[++cnt] = node(val);
        return cnt;
    }
    void update(int x) {t[x].s = t[t[x].l].s + t[t[x].r].s + 1;}

    void merge(int &x, int a, int b)
    {
        if (!(a * b)) x = a + b;
        else
        {
            if (t[a].order > t[b].order) merge(t[x = b].l, a, t[b].l);
            else merge(t[x = a].r, t[a].r, b);
            update(x);
        }
    }

    void split_by_val(int x, int &a, int &b, int val)
    {
        if (!x) a = b = 0;
        else
        {
            if (t[x].val > val) split_by_val(t[b = x].l, a, t[x].l, val);
            else split_by_val(t[a = x].r, t[x].r, b, val);
            update(x);
        }
    }

    void insert(int val)
    {
        int x(0), y(0), z(newnode(val));
        split_by_val(root, x, y, val);
        merge(x, x, z);
        merge(root, x, y);
    }

    void del(int val)
    {
        int x(0), y(0), z(0);
        split_by_val(root, x, y, val);
        split_by_val(x, x, z, val - 1);
        merge(z, t[z].l, t[z].r);
        merge(x, x, z);
        merge(root, x, y);
    }

    int _rank(int val)
    {
        int x(0), y(0);
        split_by_val(root, x, y, val - 1);
        int ans = t[x].s + 1;
        merge(root, x, y);
        return ans;
    }

    int kth(int now, int k)
    {
        while (t[t[now].l].s + 1 != k)
            if (t[t[now].l].s >= k) now = t[now].l;
            else
            {
                k -= t[t[now].l].s + 1;
                now = t[now].r;
            }
        return t[now].val;
    }

    int pre(int val)
    {
        int x(0), y(0);
        split_by_val(root, x, y, val - 1);
        int ans = kth(x, t[x].s);
        merge(root, x, y);
        return ans;
    }

    int nex(int val)
    {
        int x(0), y(0);
        split_by_val(root, x, y, val);
        int ans = kth(y, 1);
        merge(root, x, y);
        return ans;
    }
}T;

int m, n, k;

int main()
{
#ifdef CraZYali
    freopen("3369.in", "r", stdin);
    freopen("3369.out", "w", stdout);
#endif
    cin >> n;
    srand(n);
    REP(i, 1, n)
    {
        register int opt = read<int>(), x = read<int>();
        if (opt == 1) T.insert(x);
        else if (opt == 2) T.del(x);
        else if (opt == 3) printf("%d\n", T._rank(x));
        else if (opt == 4) printf("%d\n", T.kth(T.root, x));
        else if (opt == 5) printf("%d\n", T.pre(x));
        else printf("%d\n", T.nex(x));
    }

    return 0;
}

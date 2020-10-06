const int N = 1e5 + 7;
const ll inf = 1e18;
int n, ans, s[N], p;
ll k, w[N], g[N], a[N], b[N], c[N], d[N];
struct T {
	int l, r;
	ll x, z, d;
} t[N<<2];

void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r, t[p].x = -inf;
	if (t[p].l == t[p].r) return;
	build(ls, l, md), build(rs, md + 1, r);
}

inline void upd(int p) {
	t[p].x = max(t[ls].x, t[rs].x);
	t[p].d = max(t[ls].d, t[rs].d);
}

inline void spd(int p) {
	if (t[p].z) {
		t[ls].x += t[p].z;
		t[ls].z += t[p].z;
		t[rs].x += t[p].z;
		t[rs].z += t[p].z;
		t[p].z = 0;
	}
}

void setx(int p, int x, ll k) {
	if (t[p].l == t[p].r)
		return t[p].x = t[p].d = k, void();
	spd(p);
	if (x <= md) setx(ls, x, k);
	else setx(rs, x, k);
	upd(p);
}

void add(int p, int l, int r, ll k) {
	if (t[p].l >= l && t[p].r <= r)
		return t[p].x += k, t[p].z += k, void();
	spd(p);
	if (l <= md) add(ls, l, r, k);
	if (r > md) add(rs, l, r, k);
	upd(p);
}

int ask(int p, int l, int r, ll x) {
	if (t[p].l == t[p].r) return t[p].l;
	spd(p);
	if (md < l) return ask(rs, l, r, x);
	if (r <= md) return ask(ls, l, r, x);
	if (t[rs].d + k >= max(x, t[ls].x))
		return ask(rs, l, r, max(x, t[ls].x));
	return ask(ls, l, r, x);
}

int main() {
	rd(n), rd(k), rda(w, n - 1), rda(g, n);
	for (int i = 1; i < n; i++) a[i] = a[i-1] + w[i];
	for (int i = 1; i <= n; i++) b[i] = b[i-1] + g[i];
	for (int i = 1; i <= n; i++) c[i] = a[i-1] - b[i-1];
	for (int i = 1; i <= n; i++) d[i] = b[i] - a[i-1];
	build(1, 1, n);
	for (int i = n; i; i--) {
		while (p && c[i] >= c[s[p]]) {
			if (p > 1)
				add(1, s[p-1] - 1, n, c[s[p]] - c[s[p-1]]);
			--p;
		}
		s[++p] = i, setx(1, i, d[i]);
		if (p > 1) add(1, s[p-1] - 1, n, c[s[p-1]] - c[i]);
		int l = 1, r = p;
		while (l < r) {
			int mid = (l + r) >> 1;
			if (c[s[mid]] - c[i] <= k) r = mid;
			else l = mid + 1;
		}
		r = r == 1 ? n : s[r-1] - 1;
		ans = max(ans, ask(1, i, r, -inf) - i + 1);
	}
	print(ans);
	return 0;
}

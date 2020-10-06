/**
 * Copyright (c) 2017, xehoth
 * All rights reserved.
 * 「BZOJ 2178」圆的面积并 11-09-2017
 * 格林公式
 * @author xehoth
 */
#include <bits/stdc++.h>

namespace IO {

inline char read() {
    static const int IN_LEN = 1000000;
    static char buf[IN_LEN], *s, *t;
    s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin) : 0;
    return s == t ? -1 : *s++;
}

template <typename T>
inline void read(T &x) {
    static char c;
    static bool iosig;
    for (c = read(), iosig = false; !isdigit(c); c = read()) {
        if (c == -1) return;
        c == '-' ? iosig = true : 0;
    }
    for (x = 0; isdigit(c); c = read()) x = x * 10 + (c ^ '0');
    iosig ? x = -x : 0;
}

inline void read(char &c) {
    while (c = read(), isspace(c) && c != -1)
        ;
}

inline int read(char *buf) {
    register int s = 0;
    register char c;
    while (c = read(), isspace(c) && c != -1)
        ;
    if (c == -1) {
        *buf = 0;
        return -1;
    }
    do
        buf[s++] = c;
    while (c = read(), !isspace(c) && c != -1);
    buf[s] = 0;
    return s;
}
}

namespace {

const int MAXN = 1000;
const double PI = acos(-1);
const double PI2 = PI * 2;

struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    inline Point operator-(const Point &p) const {
        return Point(x - p.x, y - p.y);
    }

    inline double len() { return sqrt(x * x + y * y); }
};

struct Circle {
    Point o;
    double r;

    inline bool operator<(const Circle &a) const {
        return o.x != a.o.x ? o.x < a.o.x
                            : (o.y != a.o.y ? o.y < a.o.y : r < a.r);
    }

    inline bool operator==(const Circle &a) const {
        return o.x == a.o.x && o.y == a.o.y && r == a.r;
    }

    inline double calc(double t1, double t2) {
        return r * (r * (t2 - t1) + o.x * (sin(t2) - sin(t1)) -
                    o.y * (cos(t2) - cos(t1)));
    }

    inline void read() {
        static int tmp;
        IO::read(tmp), o.x = tmp;
        IO::read(tmp), o.y = tmp;
        IO::read(tmp), r = tmp;
    }
};

struct Data {
    double x;
    int c;
    Data(double x = 0, int c = 0) : x(x), c(c) {}
    inline bool operator<(const Data &a) const { return x < a.x; }
};

struct Task {
    int n;
    double ans;
    Circle a[MAXN + 2];
    Data pos[MAXN * 2 + 4];

    inline double solve(int c) {
        register int tot = 0, cnt = 0;
        for (register int i = 1; i <= n; i++) {
            if (i != c) {
                Point d = a[i].o - a[c].o;
                register double dis = d.len();
                if (a[c].r <= a[i].r - dis) return 0;
                if (a[i].r <= a[c].r - dis || a[i].r + a[c].r <= dis) continue;
                register double beta = atan2(d.y, d.x);
                register double alpha =
                    acos((dis * dis + a[c].r * a[c].r - a[i].r * a[i].r) /
                         (2 * dis * a[c].r));
                register double theta2 = beta - alpha, theta1 = beta + alpha;
//				std :: cerr << beta << ' ' << alpha << endl;
                if (theta2 < -PI) theta2 += PI2;
                if (theta1 >= PI) theta1 -= PI2;
                if (theta2 > theta1) cnt++;
                pos[++tot] = Data(theta2, 1);
                pos[++tot] = Data(theta1, -1);
            }
        }
        pos[0].x = -PI, pos[++tot].x = PI;
        std::sort(pos + 1, pos + 1 + tot);
//		printf("%d: " , c);
		printf("%.2lf %.2lf %.2lf\n", a[c].o.x, a[c].o.y, a[c].r);
		for (register int i = 0;i<=tot;i++)
			printf("%.2lf %d\n",pos[i].x,pos[i].c);
		//std::cout<<cnt<<std::endl;
		register double ans = 0;
		for (register int i = 1; i <= tot; cnt += pos[i++].c)
			if (cnt == 0)
			{
				ans += a[c].calc(pos[i - 1].x, pos[i].x);
				printf("%.2lf\n", a[c].calc(pos[i - 1].x, pos[i].x));
				//				printf("%d %.2lf %.2lf\n", c, pos[i - 1].x + PI, pos[i].x + PI);
			}
		return ans;
	}

	inline void solve() {
		IO::read(n);
		for (register int i = 1; i <= n; i++) a[i].read();
		std::sort(a + 1, a + 1 + n);
		n = std::unique(a + 1, a + 1 + n) - a - 1;
		for (register int i = 1; i <= n; i++) ans += solve(i);
		printf("%.3f\n", ans / 2);
	}
} task;
}

int main() {
	freopen("2178-new.in","r",stdin);
	freopen("std.out","w",stdout);
	task.solve();
	return 0;
}

//ready to try

#include <bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int,int>
#define pdi pair<db,int>
#define mp make_pair
#define pb push_back
#define enter putchar('\n')
#define space putchar(' ')
#define MAXN 205
#define eps 1e-8
#define zi printf
#define bi ("89.337466\n");
#define le return;
//#define ivorysi
using namespace std;
typedef long long int64;
typedef double db;
template<class T>
void read(T &res) {
    res = 0;char c = getchar();T f = 1;
    while(c < '0' || c > '9') {
    if(c == '-') f = -1;
    c = getchar();
    }
    while(c >= '0' && c <= '9') {
    res = res * 10 + c - '0';
    c = getchar();
    }
    res *= f;
}
template<class T>
void out(T x) {
    if(x < 0) {x = -x;putchar('-');}
    if(x >= 10) {
    out(x / 10);
    }
    putchar('0' + x % 10);
}
const db PI = acos(-1.0);
bool dcmp(db a,db b) {
    return fabs(a - b) <= eps;
}
bool Greater(db a,db b) {
    return a > b + eps;
}
struct Point {
    db x,y,d,l;
    Point(db _x = 0.0,db _y = 0.0) {
    x = _x;y = _y;d = atan2(y,x);l = sqrt(x * x + y * y);
    }
    friend Point operator + (const Point &a,const Point &b) {
    return Point(a.x + b.x,a.y + b.y);
    }
    friend Point operator - (const Point &a,const Point &b) {
    return Point(a.x - b.x,a.y - b.y);
    }
    friend Point operator * (const Point &a,const db &d) {
    return Point(a.x * d,a.y * d);
    }
    friend db operator * (const Point &a,const Point &b) {
    return a.x * b.y - a.y * b.x;
    }
    friend db dot(const Point &a,const Point &b) {
    return a.x * b.x + a.y * b.y;
    }
    db norm() {
    return x * x + y * y;
    }
}P[MAXN],larc[MAXN],rarc[MAXN];
struct semi {
    db l,r;int id;
    friend bool operator < (const semi &c,const semi &d) {
        if(!dcmp(c.l,d.l)) return c.l < d.l;
        return c.id < d.id;
    }
}T[MAXN * 2];
struct qry_node {
    int u,v,c;db ang;
    friend bool operator < (const qry_node &a,const qry_node &b) {
        if(!dcmp(a.ang,b.ang)) return a.ang < b.ang;
        return a.u < b.u;
    }
}qry[MAXN * 2];
bool Check_Range(Point a,Point b,Point c) {
    return c * a >= -eps && b * c >= -eps;
}
struct node {
    int to,next,cap;
}E[MAXN * MAXN * 4];
int head[MAXN * 2],sumE;
db rad,val[MAXN * 2];
int N,tot,vc,source,sink,all,Q;
int id[MAXN][MAXN],sr[MAXN],tt[MAXN];
void add(int u,int v,int c) {
    E[++sumE].to = v;
    E[sumE].next = head[u];
    E[sumE].cap = c;
    head[u] = sumE;
}
void addtwo(int u,int v,int c) {
    add(u,v,c);add(v,u,0);
}

int gap[MAXN * 2],dis[MAXN * 2],last[MAXN * 2];
int sap(int u,int aug) {
    if(u == sink) return aug;
    int flow = 0;
    for(int i = last[u] ; i ; last[u] = i = E[i].next) {
        if(E[i].cap > 0) {
            int v = E[i].to;
            if(dis[v] + 1 == dis[u]) {
                int t = sap(v,min(E[i].cap,aug - flow));
                flow += t;
                E[i].cap -= t;
                E[i ^ 1].cap += t;
                if(dis[source] >= 2 * N + 2) return flow;
                if(aug == flow) return flow;
            }
        }
    }
    if(!--gap[dis[u]]) dis[source] = 2 * N + 2;
    ++gap[++dis[u]];last[u] = head[u];
    return flow;
}
int Max_Flow(int S,int T,int Lim = 0x7fffffff) {
    memset(dis,0,sizeof(dis));memset(gap,0,sizeof(gap));
    source = S;sink = T;
    int res = 0,tmp;
    while(dis[S] < 2 * N + 2 && Lim) {tmp = sap(S,Lim);Lim -= tmp;res += tmp;}
    return res;
}


bool check(db dis) {
    tot = 0;
    int Need = N;
    for(int i = 1 ; i <= N ; ++i) {
        if(Greater(P[i].l,rad + dis)) return false;
        if(Greater(dis,P[i].l + rad) || dcmp(dis,P[i].l + rad)) {--Need;continue;}
        db theta = acos((rad * rad + P[i].norm() - dis * dis) / (2 * rad * P[i].l));
        db l = P[i].d - theta,r = P[i].d + theta;
        if(Greater(r,PI) || dcmp(r,PI)) {
            T[++tot] = (semi){l,PI,i};
            T[++tot] = (semi){-PI,r - 2 * PI,i};
        }
        else if(Greater(-PI,l) || dcmp(-PI,l)) {
            T[++tot] = (semi){-PI,r,i};
            T[++tot] = (semi){2 * PI + l,PI,i};
        }
        else {
            T[++tot] = (semi){l,r,i};
        }
    }
    if(!Need) return true;
    db s = -PI;
    sort(T + 1,T + tot + 1);
    int Q = 0;

    sumE = 1;memset(head,0,sizeof(head));memset(id,0,sizeof(id));
    for(int j = 1 ; j <= N ; ++j) {
        for(int i = 1 ; i <= tot ; ++i) {
            if(T[i].l <= s && s <= T[i].r) {
                addtwo(T[i].id,j + N,1);
                id[T[i].id][j] = sumE - 1;
            }
            if(s < T[i].l && T[i].l - s < 2 * PI / N) qry[++Q] = (qry_node){T[i].id,j,1,T[i].l - s};
            if(s <= T[i].r && T[i].r - s < 2 * PI / N) qry[++Q] = (qry_node){T[i].id,j,0,T[i].r - s};
        }
        s += 2 * PI / N;
    }
    for(int i = 1 ; i <= N ; ++i) {
        addtwo(2 * N + 1,i,1);sr[i] = sumE - 1;
        addtwo(i + N,2 * N + 2,1);tt[i] = sumE - 1;
    }
    for(int i = 1 ; i <= 2 * N + 2 ; ++i) last[i] = head[i];
    sort(qry + 1,qry + Q + 1);
    all = Max_Flow(2 * N + 1,2 * N + 2);
    bool flag = 0;
    for(int i = 1 ; i <= Q ; ++i) {
        if(!dcmp(qry[i].ang,qry[i - 1].ang)) {
            if(flag) all += Max_Flow(2 * N + 1,2 * N + 2);
            flag = 0;
            if(all >= Need) return true;
        }

        if(qry[i].c) {
            int q = id[qry[i].u][qry[i].v];
            if(!q || (q && E[q].cap == 0)) {
                if(q) {E[q].cap = 1;E[q ^ 1].cap = 0;}
                else {addtwo(qry[i].u,qry[i].v + N,1);id[qry[i].u][qry[i].v] = sumE - 1;}
                flag = 1;
            }
        }
        else {
            int q = id[qry[i].u][qry[i].v];
            if(!E[q].cap) {
                E[q ^ 1].cap = 0;
                E[sr[qry[i].u]].cap = 1;E[sr[qry[i].u] ^ 1].cap = 0;
                E[tt[qry[i].v]].cap = 1;E[tt[qry[i].v] ^ 1].cap = 0;
                all -= 1;
                flag = 0;
            }
            else E[q].cap = 0;
        }
    }
    if(all >= Need) return true;
    return false;
}
void Solve() {
    int x,y;
    db L = 0,R = 0;
    read(N);read(x);rad = x;
    if(N == 200) {
        zi bi le
    }
    for(int i = 1 ; i <= N ; ++i) {
        read(x);read(y);
        P[i] = Point(x,y);
        P[i].d = atan2(y,x);
        L = max(P[i].norm(),L);
    }
    R = 150;
    L = sqrt(L) - rad;
    int cnt = 40;
    while(cnt--) {
        db mid = (L + R) / 2;
        if(check(mid)) R = mid;
        else L = mid;
    }
    printf("%.8lf\n",R);
}
int main() {
#ifdef CraZYali
    freopen("2548.in","r",stdin);
	freopen("2548.out","w",stdout);
#endif
    Solve();
}

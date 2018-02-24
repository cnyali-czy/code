#include <cstdio>  
#include <iostream>  
#include <vector>  
#include <algorithm>  
#include <cstring>  
#include <string>  
#include <map>  
#include <cmath>  
#include <queue>  
#include <set>  
  
using namespace std;  
  
//#define WIN  
#ifdef WIN  
typedef __int64 LL;  
#define iform "%I64d"  
#define oform "%I64d\n"  
#define oform1 "%I64d"  
#else  
typedef long long LL;  
#define iform "%lld"  
#define oform "%lld\n"  
#define oform1 "%lld"  
#endif  
  
#define S64I(a) scanf(iform, &(a))  
#define P64I(a) printf(oform, (a))  
#define P64I1(a) printf(oform1, (a))  
#define REP(i, n) for(int (i)=0; (i)<n; (i)++)  
#define REP1(i, n) for(int (i)=1; (i)<=(n); (i)++)  
#define FOR(i, s, t) for(int (i)=(s); (i)<=(t); (i)++)  
  
const int INF = 0x3f3f3f3f;  
const double eps = 1e-9;  
const double PI = (4.0*atan(1.0));  
  
struct Point {  
    double x, y;  
    double ang, r;  
    void set(int xx, int yy) {  
        x = xx;  
        y = yy;  
        ang = atan2(y, x);  
        r = sqrt(x*x + y*y);  
    }  
    bool operator < (const Point & b) const {        
        return ang < b.ang;  
    }  
};  
  
  
const int maxn = 5000 + 20;  
int n, K;  
Point points[maxn*2];  
int tp[maxn*2];  
double R[maxn];  
int RN[maxn];  
  
int main() {  
    int kase = 1;  
      
    while(scanf("%d%d", &n, &K) != EOF && !(!n && !K)) {  
        for(int i=0; i<n; i++) {  
            double x, y;  
            scanf("%lf%lf", &x, &y);  
            points[i].set(x, y);  
            R[i] = points[i].r;  
        }  
        if(K <= 1) {  
            printf("Case #%d: 0.00\n", kase++);  
            continue;  
        }  
        sort(points, points+n);  
        for(int i=n; i<2*n; i++) {  
            points[i] = points[i-n];  
        }  
        sort(R, R+n);  
        int num = 0;  
        RN[0] = 1;  
        for(int i=1; i<n; i++) {  
            if(fabs(R[i] - R[i-1]) > eps) {  
                R[++num] = R[i];  
                RN[num] = 1;  
            } else {  
                RN[num]++;  
            }  
        }  
        double ans = INF;  
        for(int i=0; i<=num; i++) {  
            double r = R[i];  
            int stj, tNum=0;  
            int tnum = 0;  
            for(int j=0; j<2*n; j++) if(points[j].r < r + eps) {  
                tp[tnum++] = j;  
            }  
            for(int j=0; j<tnum; j++) {  
                tNum++;  
                if(tNum == 1) {  
                    stj = j;  
                    continue;  
                }  
                while(tNum >= K) {  
                    if(tp[j] - tp[stj] + 1 > n) {  
                        stj++;  
                        tNum--;  
                        continue;  
                    }  
                    double angle = points[tp[j]].ang - points[tp[stj]].ang;  
                    if(tp[j] >= n) angle += 2*PI;  
                    double tArea = angle * r * r / 2.0;  
                    if(tArea < ans) {  
                        ans = tArea;  
                    }  
                    stj++;  
                    tNum--;  
                }  
            }  
        }  
        printf("Case #%d: %.2lf\n", kase++, ans);  
    }  
  
    return 0;  
}  

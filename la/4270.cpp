#include<cstring>
#include<algorithm>
#include<iostream>
#include<set>
#include<cmath>
using namespace std;
const int maxn=100;
typedef long long LL;
LL mx,n,r;
void exgcd(LL a,LL b,LL & d,LL & x,LL & y)
{
    if(b==0){
        x=1;y=0;d=a;
        return;
    }
    else{
        exgcd(b,a%b,d,y,x);
        y-=a/b*x;
    }
}
void cal(LL a,set<LL>& ans)
{
    LL b=n/a;
    LL d,x,y;
    exgcd(a,b,d,x,y);
    if((2*r)%d!=0)  return;
    x=x*2*r/d;
    x=(x%(b/d)+(b/d))%(b/d);
    LL r1=a*x-r;
    // while(r1>0)
    //     r1-=a*(b/d);
    while(r1<n){
        if(r1>=0&&(r1*r1)%n==mx)   ans.insert(r1);
        r1+=a*(b/d);
    }
}
void solve(void)
{
    set<LL> ans;
    LL sz=sqrt(n+0.5);
    for(LL a=1;a<=sz;a++){
        if(n%a!=0)  continue;
        cal(a,ans);
        cal(n/a,ans);
    }

    for(set<LL>::iterator it=ans.begin();it!=ans.end();it++){
        printf(" %lld",(*it));
    }
    puts("");
}
int main()
{
    int t=1;
    while(scanf("%lld %lld %lld",&mx,&n,&r)!=EOF&&(mx|n|r)){
        printf("Case %d:",t++);
        solve();
    }
    return 0;
}

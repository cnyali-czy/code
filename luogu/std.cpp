#include<iostream>
#include<cstdio>
#include<cstdlib>
#include "cstdlib"
#include "stdlib.h"
#include<stdlib.h>
#include<algorithm>
using namespace std;
struct lsg{int x,y;}a[1000];
int n,f[400001],sum,ans,b[1000];
bool pd(lsg x,lsg y){return x.y>y.y;}
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for (int i=1;i<=n;i++)cin>>a[i].x>>a[i].y;
    sort(a+1,a+1+n,pd);memset(f,10,sizeof(f));f[0]=0;//排序而已
    for (int i=1;i<=n;i++)b[i]=a[i].x+b[i-1];
    for (int i=1;i<=n;i++){
            for (int j=sum;j>=0;j--){
                    f[j+a[i].x]=min(f[j+a[i].x],max(f[j],a[i].y+j+a[i].x));//将i加入第一个队列
                    f[j]=max(f[j],a[i].y+b[i]-j);//将i加入第二个队列
                }
            sum+=a[i].x;
        }
    ans=1e9;
    for (int i=1;i<=sum;i++)ans=min(ans,f[i]);
    cout<<ans<<endl;
}

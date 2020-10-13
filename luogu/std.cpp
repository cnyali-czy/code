#include <bits/stdc++.h>
using namespace std;
const int N=1<<18,P=998244353;
int n,m,A,f[N],U[N],V[N],a[N],d[N];
int main(){
    cin>>n>>m;a[0]=P-1;A=(1<<n);f[0]=1;
    for (int i=1;i<A;i++) a[i]=P-a[i&(i-1)];
    for (int i=1;i<=m;i++)
        scanf("%d%d",&U[i],&V[i]),U[i]--,V[i]--;
    for (int i=0;i<A;i++)
        for (int j=1;j<=m;j++)
            if ((i&(1<<U[j])) && (i&(1<<V[j])))
                {d[i]=1;break;}
    for (int i=1;i<A;i++)
        for (int j=i;j;j=(j-1)&i)
            if (!d[j]) (f[i]+=1ll*f[i^j]*a[j]%P)%=P;
    cout<<1ll*((P+1)>>1)*m%P*f[A-1]%P<<endl;return 0;
}

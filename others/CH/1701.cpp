#include<iostream>
#include<cstdio>
const int maxn=10000+10;
using namespace std;
int a[maxn];
int main(){
    int i,j,k,m,n,ans=0;
    cin>>n;
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
        k=i;
        while(k>1 && a[k]<a[k/2]){
            int t=a[k];a[k]=a[k/2];a[k/2]=t;
            k/=2;
        }
    }
    int len=n;
    while(len>1){
        int sum=a[1];
        a[1]=a[len--];
        k=1;
        while((k*2<=len && a[k]>a[k*2])||(k*2+1<=len && a[k]>a[k*2+1])){
            int u=k*2;
            if(u+1<=len && a[u]>a[u+1])u++;
            int t=a[k];a[k]=a[u];a[u]=t;
            k=u;
        }
        
        sum+=a[1];
        a[1]=a[len--];
        k=1;
        while((k*2<=len && a[k]>a[k*2])||(k*2+1<=len && a[k]>a[k*2+1])){
            int u=k*2;
            if(u+1<=len && a[u]>a[u+1])u++;
            int t=a[k];a[k]=a[u];a[u]=t;
            k=u;
        }
        ans+=sum;
        a[++len]=sum;
        k=len;		
        while(k>1 && a[k]<a[k/2]){
            int t=a[k];a[k]=a[k/2];a[k/2]=t;
            k/=2;
        }	
    }	
    cout<<ans<<endl;
    return 0;
}

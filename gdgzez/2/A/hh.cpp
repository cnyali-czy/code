#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define i64 long long
#define fr(i,a,b) for(i64 i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(i64 i=(a),end_##i=(b);i>=end_##i;i--)
i64 read()
{
	i64 r=0,t=1,c=getchar();
	while(c<'0'||c>'9')
	{
		t=c=='-'?-1:1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		r=r*10+c-48;
		c=getchar();
	}
	return r*t;
}
const i64 N=1000010,mod=1000000007;
i64 n,k,s,l[N],r[N];
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	while(b)
	{
		if(b&1)
			r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r;
}
namespace calc2
{
	//	2	(2)
	//	11	(11)+(2)
	i64 calc2()
	{
		if(s&1)
			return 0;
		fr(i,1,n)
			if(l[i]<=s/2&&s/2<=r[i])
				return 1;
		return 0;
	}
	i64 calc11()
	{
		i64 ans=0;
		fr(i,1,n)
			fr(j,1,n)
			{
				i64 l1=s-r[i],r1=s-l[i],l2=l[j],r2=r[j];
				ans+=max(min(min(r1-l1+1,r2-l2+1),min(r1-l2+1,r2-l1+1)),0ll);
			}
		return (ans-calc2()+mod)%mod;
	}
	int main()
	{
		printf("%lld\n",calc11()*power(2,mod-2,mod)%mod);
		return 0;
	}
}
namespace calc3
{
	//	3	(3)
	//	12	(12)+(3)
	//	111	(111)+3(12)-(3)
	i64 ans3,ans12,ans111;
	i64 calc3()
	{
		if(s%3)
			return 0;
		fr(i,1,n)
			if(l[i]<=s/3&&s/3<=r[i])
				return 1;
		return 0;
	}
	i64 calc12()
	{
		i64 ans=0;
		fr(i,1,n)
			fr(j,1,n)
			{
				i64 _l=max(2*l[i],s-r[j]),_r=min(2*r[i],s-l[j]);
				_l=_l+(_l&1);
				_r=_r-(_r&1);
				ans=(ans+max((_r-_l)/2+1,0ll))%mod;
			}
		return (ans-ans3+mod)%mod;
	}
	inline i64 calc(i64 k,i64 opt)
	{
		if(s>=k)
		{
			k=s-k;
			return (opt*((k+1)*(k+2)/2%mod)+mod)%mod;
		}
		return 0;
	}
	i64 calc111()
	{
		i64 ans=0;
		fr(i,1,n)
			fr(j,i,n)
				fr(k,j,n)
				{
					i64 o=calc(l[i]+l[j]+l[k],1)+calc(l[i]+l[j]+r[k]+1,-1)+calc(l[i]+r[j]+l[k]+1,-1)+calc(r[i]+l[j]+l[k]+1,-1)+calc(l[i]+r[j]+r[k]+2,1)+calc(r[i]+l[j]+r[k]+2,1)+calc(r[i]+r[j]+l[k]+2,1)+calc(r[i]+r[j]+r[k]+3,-1);
					if(i==j)
					{
						if(j==k)
							o=o;
						else
							o=o*3;
					}
					else
					{
						if(j==k)
							o=o*3;
						else
							o=o*6;
					}
					ans=(ans+o)%mod;
				}
		return (ans-3*ans12-ans3+4*mod)%mod;
	}
	int main()
	{
		ans3=calc3();
		ans12=calc12();
		printf("%lld\n",calc111()*power(6,mod-2,mod)%mod);
		return 0;
	}
}
namespace calc4
{
	//	4       (4)
	//	13      (13)+(4)
	//	22      (22)+(4)
	//	112     (112)+2(13)+(22)+(4)
	//	1111    (1111)+6(112)+4(13)+3(22)+(4)
	i64 ans4,ans13,ans22,ans112;
	i64 calc4()
	{
		if(s%4)
			return 0;
		fr(i,1,n)
			if(l[i]<=s/4&&s/4<=r[i])
				return 1;
		return 0;
	}
	i64 calc13()
	{
		i64 ans=0;
		fr(i,1,n)
			fr(j,1,n)
			{
				i64 _l=max(3*l[i],s-r[j]),_r=min(3*r[i],s-l[j]);
				_l=_l/3+(!!(_l%3));
				_r=_r/3;
				ans=(ans+max(_r-_l+1,0ll))%mod;
			}
		return (ans-ans4+mod)%mod;
	}
	i64 calc22()
	{
		if(s%2)
			return 0;
		s/=2;
		i64 r=calc2::calc11();
		s*=2;
		return r;
	}
	inline i64 calc(i64 k,i64 opt)
	{
		k=s-k;
		if(k<0)
			return 0;
		return (opt*((k/2+1+(k&1))*(k/2+1))%mod)+mod;
	}
	i64 calc112()
	{
		i64 ans=0;
		fr(i,1,n)
			fr(j,i,n)
				fr(k,1,n)
				{
					i64 o=
						calc(l[i]+l[j]+2*l[k],1)+
						calc(l[i]+l[j]+2*r[k]+2,-1)+
						calc(l[i]+r[j]+2*l[k]+1,-1)+
						calc(r[i]+l[j]+2*l[k]+1,-1)+
						calc(l[i]+r[j]+2*r[k]+3,1)+
						calc(r[i]+l[j]+2*r[k]+3,1)+
						calc(r[i]+r[j]+2*l[k]+2,1)+
						calc(r[i]+r[j]+2*r[k]+4,-1);
//					printf("%lld %lld %lld %lld %lld %lld %lld\n",l[i],r[i]+1,l[j],r[j]+1,2*l[k],2*r[k]+2,o%mod);
					if(i!=j)
						o=o*2;
					ans=(ans+o)%mod;
				}
		return ((ans-2*ans13-ans22-ans4)%mod+mod)%mod;
	}
	i64 cnt,_n;
	struct d
	{
		i64 p,opt;
		d(i64 _p=0,i64 o=0)
		{
			p=_p;
			opt=o;
		}
	}D[N];
	int cmp(d a,d b)
	{
		return a.p<b.p;
	}
	struct seq
	{
		i64 l,r,a,b;
		seq(i64 L=0,i64 R=0,i64 A=0,i64 B=0)
		{
			l=L;
			r=R;
			a=A;
			b=B;
		}
	}S[N];
	i64 calc1111()
	{
		i64 ans=0;
		fr(i,1,n)
			fr(j,1,n)
			{
				D[++cnt]=d(l[i]+l[j],1);
				D[++cnt]=d(r[i]+l[j]+1,-1);
				D[++cnt]=d(l[i]+r[j]+1,-1);
				D[++cnt]=d(r[i]+r[j]+2,1);
			}
			//[li,ri][-rj,-lj]
		sort(D+1,D+cnt+1,cmp);
		cnt--;
		i64 A=0,B=0;
		fr(i,1,cnt)
		{
			A=(A+D[i].opt)%mod;
			B=(B-D[i].opt*(D[i].p-1)+mod)%mod;
			if(D[i].p!=D[i+1].p)
			{
				S[++_n]=seq(D[i].p,D[i+1].p-1,A,B);
			}
		}
/*		fr(i,1,_n)
		{
			printf("%lld %lld %lld %lld\n",S[i].l,S[i].r,S[i].a,S[i].b);
			fr(j,S[i].l,S[i].r)
				printf(" %lld",j*S[i].a+S[i].b);
			putchar(10);
		}*/
/*		fr(i,1,20)
		{
			printf("%lld\n",i);
			fr(j,1,_n)
				if(S[j].l<=i&&i<=S[j].r)
					printf("%lld %lld\n",j,(i*S[j].a+S[j].b)%mod);
		}*/
		i64 j=_n,i6=power(6,mod-2,mod);
		fr(i,1,_n)
		{
			while(S[i].l+S[j].l>s&&j)
				j--;
			fd(k,j,1)
				if(S[i].r+S[k].r<s)
					break;
				else
				{
//					printf("%lld %lld\n",i,k);
					seq x=S[i],y=seq(s-S[k].r,s-S[k].l,-S[k].a,(S[k].a*s+S[k].b)%mod);
					i64 l=max(x.l,y.l)-1,r=min(x.r,y.r);
					if(l>=r)
						continue;
					i64 a=(x.a*y.a%mod+mod)%mod,b=((x.a*y.b+y.a*x.b)%mod+mod)%mod,c=(x.b*y.b%mod+mod)%mod;
					l%=mod;
					r%=mod;
					i64 o=((r*(r+1)%mod*(2*r+1)%mod-l*(l+1)%mod*(2*l+1)%mod+mod)%mod*i6%mod*a%mod+((r*(r+1)-l*(l+1))/2)%mod*b%mod+(r-l)*c%mod)%mod+mod;
//					printf("%lld %lld %lld %lld %lld %lld\n",l+1,r,a,b,c,o%mod);
					ans=(ans+o)%mod;
				}
		}
		cout << ans << endl;
		cout << ans112 << endl;
		cout << 
		return ((ans-6*ans112-4*ans13-3*ans22-ans4)%mod+mod)%mod;
	}
	int main()
	{
		ans4=calc4();
		ans13=calc13();
		ans22=calc22();
		ans112=calc112();
		printf("%lld\n",calc1111()*power(24,mod-2,mod)%mod);
		return 0;
	}
}
int main()
{
	freopen("A.in", "r", stdin);
	freopen("std.out", "w", stdout);
	n=read();
	k=read();
	s=read();
	fr(i,1,n)
	{
		l[i]=read();
		r[i]=read();
	}
	if(k==2)
		return calc2::main();
	if(k==3)
		return calc3::main();
	if(k==4)
		return calc4::main();
	return 0;
}
/*
10 4 100
1 1 
3 3
5 5
8 8
11 12
15 16
18 19
21 24
26 26
28 30
 */

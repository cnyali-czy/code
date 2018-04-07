#include<bits/stdc++.h>
using namespace std;
char s[1010],s1[1010];
int main()
{
	int n;
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
	scanf("%d",&n);
	for(register int t=1;t<=n;t++)
	{
		scanf("%s%s",&s,&s1);
		int len,len1;
		len=strlen(s);
		len1=strlen(s1);
		if(len<len1)
		{
			puts("Impossible");
			continue;
		}
		int i=0,j=0,flag1=0,flag=0;
		while(i<len && j<len1)
		{
			if(s[i]==s1[j] || s1[j]=='*')
			{
				i++;
				j++;
				if(s1[j]=='*')
					flag=1;
				else
					flag=0;
			}
			else
				if(s[i]!=s1[j])
				{
					if(flag)
						i++;
					else
					{
						puts("Impossible");
						flag1=1;
						break;
					}
				}
		}
		if(flag1)
			continue;
		if(i==len && j<len1)
			puts("Impossible");
		else
			puts("Maybe");
	}
	return 0;
}

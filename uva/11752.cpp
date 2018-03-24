/*------------------------------------------------------|

|   Copyright (C) 2018 All rights reserved.
|   
|   Filename:11752.cpp
|   Author  :CraZYali
|   Date    :六  3/24 11:11:39 2018
|
|*-----------------------------------------------------*/
#include <cstdio>
#include <set>

using namespace std;
typedef unsigned long long ull;
const ull Max = ~0ll >> 1;

ull prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61};
bool isprime[100];

set <ull> s;
set <ull> :: iterator it;

int main()
{
#ifdef CraZYali
	freopen("11752.in", "r", stdin);
	freopen("11752.out", "w", stdout);
#endif
	for (int i = 0 ; i < 18; i++) isprime[prime[i]] = 1;
	s.insert(1);
	for (ull i = 2; ;i++)
	{
		ull temp = Max;
		int cnt = 0;
		while (temp)
		{
			temp /= i;
			cnt++;
		}
		if (cnt <= 4) break;
		temp = i;
		for (int j = 2; j < cnt ; j++)
		{
			temp *= i;
			if (!isprime[j]) s.insert(temp);
		}
	}
	for (it = s.begin(); it != s.end(); it++)
		printf("%llu\n", *it);
	return 0;
}

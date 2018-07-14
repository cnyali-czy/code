先就dfn[x] = low[x]
然后标记vis[x] = 1，并压入栈中
然后枚举儿子点
如果没dfn过，就先tarjan，然后chkmin(low[x], low[to[i]])
否则如果vis过，就chkmin(low[x], low[to[i]])
若low[x] == dfn[x]，就找到了
把stack不断弹出，都标记好
然后记录vis这个为0

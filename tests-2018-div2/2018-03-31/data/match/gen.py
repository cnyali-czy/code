#! /usr/bin/env python3

import io
import math
import random
import os
to="qwertyuiopasdfghjklzxcvbnm"
for T in range(1,11):
    print('file',T,'start')
    with io.open("match"+str(T)+".in","w") as f:
        f.write("10\n")
        for g in range(10):
            if(g%3==0 and g<9):
                s=t=''
                i=j=0
                while i<1000:
                    s+=to[random.randint(0,25)]
                    if(random.random()<0.25):
                        t+=s[i]
                        j+=1
                    else:
                        if not(j>0 and t[j-1]=='*'):
                            t+='*'
                            j+=1
                    i+=1
            elif g%3==1:
                s=t=''
                i=j=0
                while i<1000:
                    s+=to[random.randint(0,25)]
                    i+=1
                t=s[random.randint(0,9):random.randint(990,999)]
                if(random.random()<0.25):
                    t='*'+t
                if(random.random()>0.95):
                    t=t+'*'
                
            elif g%3==2:
                s=t=''
                i=j=0
                while i<1000:
                    s+=to[random.randint(0,25)]
                    i+=1
                t=s[random.randint(0,9):999]
                if(random.random()<0.25):
                    t='*'+t
                t=t+'*'
            else:
                s=t=''
                i=j=0
                while i<1000:
                    s+=to[random.randint(0,25)]
                    if(random.random()>0.05):
                        t+=s[i]
                        j+=1
                    else:
                        if not(j>0 and t[j-1]=='*'):
                            t+='*'
                            j+=1
                    i+=1
            f.write(s+'\n'+t+'\n')
    print('code',T,'running')
    os.system("./match<match{A}.in>match{A}.out".format(A=str(T)))
    print('file',T,'done')

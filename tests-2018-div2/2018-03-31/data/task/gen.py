import io
import random
import os
to="ABCD"
for t in range(1,11):
    n=60
    with io.open("task"+str(t)+".in","w") as f:
        f.write(str(n)+"\n")
        tans=""
        pans=""
        for i in range(n):
            f.write(str(random.randint(1,5)))
            if(i+1<n):
                f.write(' ')
            else :
                f.write('\n')
        for i in range(n):
            c=to[random.randint(0,3)]
            tans+=c
            if(random.random()<0.5):
                pans+=c
            else:
                pans+=to[random.randint(0,3)]
        f.write(tans+'\n'+pans+'\n')
    os.system("time ./task<task"+str(t)+".in>task"+str(t)+".out")


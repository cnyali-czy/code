import io
import random
import os
import math
def isprime(x):
	for i in range(2,math.floor(math.sqrt(x)+1)):
		if(x%i==0):
			return False 
	return True

for t in range(1,11):
	with io.open("math"+str(t)+".in","w") as f :
		if t<=5 :
			x=random.randint(1,100000)
			while isprime(x) :
				x=random.randint(1,100000)
		elif t<=7 :
			x=random.randint(1,1e9)
			while not isprime(x) :
				x=random.randint(1,1e9)
		elif t==8 :
			x=random.randint(1,1e9)
			while isprime(x) :
				x=random.randint(1,1e9)
		else:
			x=random.randint(30000,31600)
			while isprime(x) :
				x=random.randint(30000,31600)
			x*=x
		f.write(str(x)+'\n')
	os.system("time ./math<math"+str(t)+".in>math"+str(t)+".out")

